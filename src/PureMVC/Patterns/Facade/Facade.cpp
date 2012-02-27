//  Facade.cpp
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#include "../../Common.hpp"

char const* const Facade::MULTITON_MSG =
"Facade instance for this Multiton key already constructed!";

char const* const Facade::DEFAULT_KEY = "PureMVC";

IFacade* Facade::find(std::string const& key)
{
    return puremvc_facade_instance_map.find(key);
}

void Facade::insert(std::string const& key, IFacade* facade)
{
    puremvc_facade_instance_map.insert(key, facade);
}

Facade::Facade(std::string const& key)
    : _controller(NULL)
    , _model(NULL)
    , _view(NULL)
{
    if (puremvc_facade_instance_map.find(key))
        throw std::runtime_error(MULTITON_MSG);
    initializeNotifier(key);
    puremvc_facade_instance_map.insert(key, this);
    initializeFacade();
}

void Facade::initializeFacade(void)
{
    initializeModel();
    initializeController();
    initializeView();
}

IFacade& Facade::getInstance(std::string const& key)
{
    IFacade* result = puremvc_facade_instance_map.find(key);
    if (result  == NULL)
    {
        result = new Facade(key);
        puremvc_facade_instance_map.insert(std::make_pair(key, result));
    }
    return *result;
}

inline void Facade::initializeController(void)
{
    if (_controller != NULL)
        return;
    _controller = &Controller::getInstance(_multiton_key);
}

void Facade::initializeModel(void)
{
    if (_model != NULL)
        return;
    _model = &Model::getInstance(_multiton_key);
}

void Facade::initializeView(void)
{
    if (_view != NULL)
        return;
    _view = &View::getInstance(_multiton_key);
}

inline void Facade::registerCommand(std::string const& notification_name,ICommand* command)
{
    if (_controller == NULL)
        throwException<std::runtime_error>("Cannot register command [%s]. Controller is null.", notification_name.c_str());
    _controller->registerCommand(notification_name, command);
}

inline ICommand const& Facade::retrieveCommand(std::string const& notification_name) const
{
    if (_controller == NULL)
        throwException<std::runtime_error>("Cannot retrieve command [%s]. Controller is null.", notification_name.c_str());
    return _controller->retrieveCommand(notification_name);
}

inline ICommand& Facade::retrieveCommand(std::string const& notification_name)
{
    if (_controller == NULL)
        throwException<std::runtime_error>("Cannot retrieve command [%s]. Controller is null.", notification_name.c_str());
    return _controller->retrieveCommand(notification_name);
}

inline ICommand* Facade::removeCommand(std::string const& notification_name)
{
    if (_controller == NULL)
        throwException<std::runtime_error>("Cannot remove command [%s]. Controller is null.", notification_name.c_str());
    return _controller->removeCommand( notification_name );
}

inline bool Facade::hasCommand(std::string const& notification_name) const
{
    if (_controller == NULL)
        throwException<std::runtime_error>("Cannot find command [%s]. Controller is null.", notification_name.c_str());
    return _controller->hasCommand(notification_name);
}

inline void Facade::registerProxy(IProxy* proxy)
{
    if (_model == NULL)
        throwException<std::runtime_error>("Cannot register proxy [%s]. Model is null.", proxy == NULL ? "NULL" : proxy->getProxyName().c_str());
    _model->registerProxy(proxy);
}

inline IProxy const& Facade::retrieveProxy(std::string const& proxy_name) const
{
    if (_model == NULL)
        throwException<std::runtime_error>("Cannot retrieve proxy [%s]. Model is null.", proxy_name.c_str());
    return _model->retrieveProxy(proxy_name);
}

inline IProxy& Facade::retrieveProxy(std::string const& proxy_name)
{
    if (_model == NULL)
        throwException<std::runtime_error>("Cannot retrieve proxy [%s]. Model is null.", proxy_name.c_str());
    return _model->retrieveProxy(proxy_name);
}

inline IProxy* Facade::removeProxy (std::string const& proxy_name)
{
    if (_model == NULL)
        throwException<std::runtime_error>("Cannot remove proxy [%s]. Model is null.", proxy_name.c_str());
    return _model->removeProxy(proxy_name);
}

inline bool Facade::hasProxy(std::string const& proxy_name) const
{
    if (_model == NULL)
        throwException<std::runtime_error>("Cannot find proxy [%s]. Model is null.", proxy_name.c_str());
    return _model->hasProxy(proxy_name);
}

inline void Facade::registerMediator(IMediator* mediator)
{
    if (_view == NULL)
        throwException<std::runtime_error>("Cannot register mediator [%s]. View is null.",
        mediator == NULL ? "NULL" : mediator->getMediatorName().c_str());
    _view->registerMediator(mediator);
}

inline IMediator const& Facade::retrieveMediator(std::string const& mediator_name) const
{
    if (_view == NULL)
        throwException<std::runtime_error>("Cannot retrieve mediator [%s]. View is null.", mediator_name.c_str());
    return _view->retrieveMediator(mediator_name);
}

inline IMediator& Facade::retrieveMediator(std::string const& mediator_name)
{
    if (_view == NULL)
        throwException<std::runtime_error>("Cannot retrieve mediator [%s]. View is null.", mediator_name.c_str());
    return _view->retrieveMediator(mediator_name);
}

inline IMediator* Facade::removeMediator(std::string const& mediator_name)
{
    if (_view == NULL)
        throwException<std::runtime_error>("Cannot remove mediator [%s]. View is null.", mediator_name.c_str());
    return _view->removeMediator(mediator_name);
}

inline bool Facade::hasMediator(std::string const& mediator_name) const
{
    if (_view == NULL)
        throwException<std::runtime_error>("Cannot find mediator [%s]. View is null.", mediator_name.c_str());
    return _view->hasMediator(mediator_name);
}

inline void Facade::sendNotification(std::string const& notification_name, void const* body, std::string const& type)
{
    Notification notification(notification_name, body, type);
    notifyObservers(notification);
}

inline void Facade::notifyObservers(INotification const& notification)
{
    if (_view != NULL )
        _view->notifyObservers(notification);
}

bool Facade::hasCore(std::string const& key)
{
    return puremvc_facade_instance_map.find(key) != NULL;
}

Facade::CoreNames Facade::listCores(void)
{
    return puremvc_facade_instance_map.getKeyAggregate();
}

void Facade::removeCore(std::string const& key)
{
    if (puremvc_facade_instance_map.find(key) == NULL)
        return;
    Model::removeModel( key );
    Controller::removeController( key );
    View::removeView( key );
    puremvc_facade_instance_map.remove(key);
}

namespace PureMVC
{
    namespace Patterns
    {
        class FacadeNotifier
        {
        private:
            INotification const& _notification;
            FacadeNotifier& operator=(FacadeNotifier const&);
        public:
            FacadeNotifier(INotification const& notification)
                : _notification(notification)
            { }
        public:
            inline void operator()(IFacade& facade)
            {
                facade.notifyObservers(_notification);
            }
        };
    }
}

void Facade::broadcastNotification(INotification const& notification)
{
    PureMVC::Patterns::FacadeNotifier notifier(notification); 
    puremvc_facade_instance_map.forEachValue(notifier);
}

void Facade::broadcastNotification(
    std::string const& notification_name,
    void const* body,
    std::string const& type)
{
    Notification notification(notification_name, body, type);
    broadcastNotification(notification);
}

Facade::~Facade(void)
{
    if (_view != NULL)
        delete _view;
    if (_model != NULL)
        delete _model;
    if (_controller != NULL)
        delete _controller;

    _view = NULL;
    _model = NULL;
    _controller = NULL;
    puremvc_facade_instance_map.remove(_multiton_key);
}
