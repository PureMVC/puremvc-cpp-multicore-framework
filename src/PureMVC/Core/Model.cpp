//  Model.cpp
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#include "../Common.hpp"

char const* const Model::MULTITON_MSG =
"Model instance for this Multiton key already constructed!";

char const* const Model::DEFAULT_KEY = "PureMVC";

inline Model::ProxyMap::key_type const& 
Model::IteratorConverter::operator()
(Model::ProxyMap::const_iterator const& iterator) const
{
    return iterator->first;
}

inline Model::ProxyMap::const_iterator 
Model::IteratorRange::begin(Model::ProxyMap const* const& iterator) const
{
    return iterator->begin();
}

inline Model::ProxyMap::const_iterator 
Model::IteratorRange::end(Model::ProxyMap const* const& iterator) const
{
    return iterator->end();
}

IModel* Model::find(std::string const& key)
{
    return puremvc_model_instance_map.find(key);
}

void Model::insert(std::string const& key, IModel* model)
{
    puremvc_model_instance_map.insert(key, model);
}

Model::Model(std::string const& key)
    : _multiton_key(key)
{
    if (puremvc_model_instance_map.find(_multiton_key))
        throw std::runtime_error(MULTITON_MSG);
    puremvc_model_instance_map.insert(_multiton_key, this);
    initializeModel();
}

inline void Model::initializeModel(void)
{ }

IModel& Model::getInstance(std::string const& key)
{
    IModel* result = puremvc_model_instance_map.find(key) ;
    if (result == NULL)
    {
        result = new Model(key);
        puremvc_model_instance_map.insert(std::make_pair(key, result));
    }
    return *result;
}

void Model::registerProxy(IProxy* proxy)
{
    proxy->initializeNotifier(_multiton_key);
    do
    {
        PureMVC::FastMutex::ScopedLock lock(_synchronous_access);
        ProxyMap::iterator result = _proxy_map.find(proxy->getProxyName());
        _proxy_map.insert(std::make_pair(proxy->getProxyName(), (proxy)));
    }while (false);
    proxy->onRegister();
}

IProxy const& Model::retrieveProxy(std::string const& proxy_name) const
{
    PureMVC::FastMutex::ScopedLock lock(_synchronous_access);

    ProxyMap::const_iterator result = _proxy_map.find(proxy_name);
    if (result == _proxy_map.end())
        throwException<std::runtime_error>("Cannot find any proxy with name: [%s].", proxy_name.c_str());

    return *result->second;
}

inline IProxy& Model::retrieveProxy(std::string const& proxy_name)
{
    return const_cast<IProxy&>(static_cast<Model const&>(*this).retrieveProxy(proxy_name));
}

inline bool Model::hasProxy(std::string const& proxy_name) const
{
    PureMVC::FastMutex::ScopedLock lock(_synchronous_access);
    return _proxy_map.find(proxy_name) != _proxy_map.end();
}

IProxy* Model::removeProxy(std::string const& proxy_name)
{
    ProxyMap::value_type::second_type proxy = NULL;

    do
    {
        PureMVC::FastMutex::ScopedLock lock(_synchronous_access);
        // Retrieve the named mediator
        ProxyMap::iterator result = _proxy_map.find(proxy_name);

        if (result == _proxy_map.end() )
            break;

        // get mediator
        proxy = result->second;
        // remove the mediator from the map
        _proxy_map.erase(result);
    }while (false);

    if (proxy != NULL) proxy->onRemove();
    return proxy;
}

void Model::removeModel(std::string const& key)
{
    puremvc_model_instance_map.remove(key);
}

Model::ProxyNames Model::listProxyNames(void) const
{
    typedef StdContainerAggregate<ProxyMap const*,
                                  ProxyMap::key_type,
                                  ProxyMap::const_iterator,
                                  IteratorConverter,
                                  IteratorRange> result_t;
#if defined(PUREMVC_USES_TR1)
    return std::unique_ptr<IAggregate<ProxyMap::key_type> >(new result_t(&_proxy_map));
#else
    return std::auto_ptr<IAggregate<ProxyMap::key_type> >(new result_t(&_proxy_map));
#endif
}

Model::~Model(void)
{
    removeModel(_multiton_key);
    _proxy_map.clear();
}
