//  common.hpp
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__PUREMVC_COMMON_HPP__)
#define __PUREMVC_COMMON_HPP__
#define PUREMVC_API_EXPORT

#if defined(_MSC_VER)
#pragma warning(disable:4250) // Disable: 'class1' : inherits 'class2::member' via dominance
#pragma warning(disable:4251) // Disable: 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
#pragma warning(disable:4127) // Disable: conditional expression is constant
#endif

// STL include
#include <exception>
#include <stdexcept>
#if defined(PUREMVC_USES_TR1)
#if defined(__GNUC__) || defined(__MINGW32__)
#include <tr1/unordered_set>
#include <tr1/unordered_map>
else
#include <unordered_set>
#include <unordered_map>
#endif
#else
#include <set>
#include <map>
#endif
#include <list>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstdlib>
#include <typeinfo>
#include <new>
#include <sstream>
#include <cstdio>
#include <cassert>
// C library include
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
// PureMVC include
#include "PureMVC/PureMVC.hpp"

#if defined(_MSC_VER) || defined(__CODEGEARC__) || defined(__BORLANDC__) || defined(__INTEL_COMPILER)
#endif

namespace PureMVC
{
    template<typename _Exception>
    void throwException(char const* format, ...)
    {
        va_list arglist;

        va_start(arglist, format);

        char buff[1024] = { 0 };

        vsprintf(buff, format, arglist);

        va_end(arglist);

        throw _Exception(buff);
    }

    extern char const __PURE_MVC_DEFAULT_NAME__[];
    template<typename _Type,
             char const _Name[] = __PURE_MVC_DEFAULT_NAME__>
    class InstanceMap
    {
    private:
#if defined(PUREMVC_USES_TR1)
        typedef std::tr1::unordered_map<std::string, _Type*> StringTypeMap;
#else
        typedef std::map<std::string, _Type*> StringTypeMap;
#endif
        StringTypeMap* _instance;
        mutable FastMutex _mutex;
    private:
        struct KeyConverter 
#if !defined(__DMC__) // The C++ compiler of Digital Mars cannot resolve this case
        : public std::unary_function<typename StringTypeMap::const_iterator, typename StringTypeMap::key_type>
#endif
        {
            inline typename StringTypeMap::key_type const& operator()(typename StringTypeMap::const_iterator const& iterator) const {
                return iterator->first;
            }
        };
        struct KeyRange {
            inline typename StringTypeMap::const_iterator begin(StringTypeMap* const& iterator) const {
                return iterator->begin();
            }
            inline typename StringTypeMap::const_iterator end(StringTypeMap* const& iterator) const {
                return iterator->end();
            }
        };
    public:
        InstanceMap(void)
            : _instance(NULL)
        { }
        void createCache(void)
        {
            if (_instance != NULL) return;
            FastMutex::ScopedLock _(_mutex);
            if (_instance != NULL) return;
#if defined(_DEBUG) || defined(DEBUG)
            std::cout << "Create instance map of " << _Name << std::endl;
#endif
            _instance = new StringTypeMap;
        }
        void insert(std::pair<std::string, _Type*> const& item)
        {
            createCache();
            FastMutex::ScopedLock _(_mutex);
            _instance->insert(item);
        }
        #if defined(PUREMVC_USES_RVALUE)
        void insert(std::pair<std::string, _Type*>&& item)
        {
            createCache();
            FastMutex::ScopedLock _(_mutex);
            _instance->insert(std::move(item));
        }
        #endif
        void insert(_Type* const& value)
        {
            createCache();
            char buff[20] = { 0 };
            sprintf(buff, "%lx", (unsigned long)value);
            std::pair<std::string, _Type*> item(buff, value);
            FastMutex::ScopedLock _(_mutex);
            _instance->insert(item);
        }
        void insert(std::string const& key, _Type* const& value)
        {
            createCache();
            std::pair<std::string, _Type*> item(key, value);
            FastMutex::ScopedLock _(_mutex);
            _instance->insert(item);
        }
        #if defined(PUREMVC_USES_RVALUE)
        void insert(std::string&& key, _Type*&& value)
        {
            createCache();
            std::pair<std::string, _Type*> item(std::move(key), std::move(value));
            value = NULL;
            FastMutex::ScopedLock _(_mutex);
            _instance->insert(item);
        }
        #endif
        _Type* remove(std::string const& key)
        {
            _Type * result = NULL;
            if (_instance == NULL) return result;
            FastMutex::ScopedLock _(_mutex);
            if (_instance == NULL) return result;
            typename StringTypeMap::iterator iter = _instance->find(key);
            if (iter != _instance->end())
            {
                result = iter->second;
                _instance->erase(iter);
            }
            return result;
        }
        _Type* remove(_Type* const& value)
        {
            char buff[20] = { 0 };
            sprintf(buff, "%lx", (unsigned long)value);
            return remove(buff);
        }
        _Type* find(std::string const& key) const
        {
            _Type * result = NULL;
            if (_instance == NULL) return result;
            FastMutex::ScopedLock _(_mutex);
            if (_instance == NULL) return result;
            typename StringTypeMap::const_iterator iter= _instance->find(key);
            if (iter != _instance->end())
                result = iter->second;
            return result;
        }
        _Type* find(_Type* const& value) const
        {
            char buff[20] = { 0 };
            sprintf(buff, "%lx", (unsigned long)value);
            return find(buff);
        }
        template<typename _InsertIterator>
        void getNames(_InsertIterator inserter) const
        {
            if (_instance == NULL) return;
            FastMutex::ScopedLock _(_mutex);
            if (_instance == NULL) return;
            typename StringTypeMap::const_iterator iter = _instance->begin();
            for(; iter != _instance->end(); ++iter, ++inserter)
                inserter = iter->first;
        }
        template<typename _Predicate>
        void forEachItem(_Predicate predicate) const
        {
            if (_instance == NULL) return;
            FastMutex::ScopedLock _(_mutex);
            if (_instance == NULL) return;
            typename StringTypeMap::const_iterator iter = _instance->begin();
            for(; iter != _instance->end(); ++iter)
                predicate(*iter);
        }
        template<typename _Predicate>
        void forEachItem(_Predicate predicate)
        {
            static_cast<InstanceMap const&>(*this).forEachItem(predicate);
        }
        template<typename _Predicate>
        void forEachKey(_Predicate predicate) const
        {
            if (_instance == NULL) return;
            FastMutex::ScopedLock _(_mutex);
            if (_instance == NULL) return;
            typename StringTypeMap::const_iterator iter = _instance->begin();
            for(; iter != _instance->end(); ++iter)
                predicate(iter->first);
        }
        template<typename _Predicate>
        void forEachKey(_Predicate predicate)
        {
            static_cast<InstanceMap const&>(*this).forEachKey(predicate);
        }
        template<typename _Predicate>
        void forEachValue(_Predicate predicate) const
        {
            if (_instance == NULL) return;
            FastMutex::ScopedLock _(_mutex);
            if (_instance == NULL) return;
            typename StringTypeMap::const_iterator iter = _instance->begin();
            for(; iter != _instance->end(); ++iter)
                predicate(*(iter->second));
        }
        template<typename _Predicate>
        void forEachValue(_Predicate predicate)
        {
            static_cast<InstanceMap const&>(*this).forEachValue(predicate);
        }
#if defined(_MSC_VER) && _MSC_VER < 1300
        std::auto_ptr<Interfaces::IAggregate<StringTypeMap::key_type> > getKeyAggregate()
        {
            createCache();
            FastMutex::ScopedLock _(_mutex);
            typedef Patterns::StdContainerAggregate<StringTypeMap*,
                                                    StringTypeMap::key_type,
                                                    StringTypeMap::const_iterator,
                                                    KeyConverter,
                                                    KeyRange> result_t;
            return std::auto_ptr<Interfaces::IAggregate<StringTypeMap::key_type> >(new result_t(_instance));
        }
#else
#if defined(PUREMVC_USES_TR1)
        std::unique_ptr<Interfaces::IAggregate<typename StringTypeMap::key_type> > getKeyAggregate()
#else
        std::auto_ptr<Interfaces::IAggregate<typename StringTypeMap::key_type> > getKeyAggregate()
#endif
        {
            createCache();
            FastMutex::ScopedLock _(_mutex);
            typedef Patterns::StdContainerAggregate<StringTypeMap*,
                                                    typename StringTypeMap::key_type,
                                                    typename StringTypeMap::const_iterator,
                                                    KeyConverter,
                                                    KeyRange> result_t;
#if defined(PUREMVC_USES_TR1)
            return std::unique_ptr<Interfaces::IAggregate<typename StringTypeMap::key_type> >(new result_t(_instance));
#else
            return std::auto_ptr<Interfaces::IAggregate<typename StringTypeMap::key_type> >(new result_t(_instance));
#endif
        }
#endif
        void cleanCache(void)
        {
            if (_instance == NULL) return;
            FastMutex::ScopedLock _(_mutex);
            if (_instance == NULL) return;
#if defined(_DEBUG) || defined(DEBUG)
            std::cout << "Clean instance map of " << _Name <<" - Number object: " << _instance->size() << std::endl;
#endif
            StringTypeMap * instance = _instance;
            _instance = NULL;
            typename StringTypeMap::iterator result = instance->begin();
            for(; result != instance->end(); ++result)
                delete result->second;
            instance->clear();
            delete instance;
        }
    public:
        ~InstanceMap(void)
        {
            cleanCache();
        }
    };
}

extern char const __OBSERVER_NAME__[];
typedef PureMVC::InstanceMap<PureMVC::Interfaces::IObserver, __OBSERVER_NAME__> InstanceMapObserver;
extern InstanceMapObserver puremvc_observer_instance_map;

extern char const __CONTROLLER_NAME__[];
typedef PureMVC::InstanceMap<PureMVC::Interfaces::IController, __CONTROLLER_NAME__> InstanceMapController;
extern InstanceMapController puremvc_controller_instance_map;

extern char const __MODEL_NAME__[];
typedef PureMVC::InstanceMap<PureMVC::Interfaces::IModel, __MODEL_NAME__> InstanceMapModel;
extern InstanceMapModel puremvc_model_instance_map;

extern char const __VIEW_NAME__[];
typedef PureMVC::InstanceMap<PureMVC::Interfaces::IView, __VIEW_NAME__> InstanceMapView;
extern InstanceMapView puremvc_view_instance_map;

extern char const __FACADE_NAME__[];
typedef PureMVC::InstanceMap<PureMVC::Interfaces::IFacade, __FACADE_NAME__> InstanceMapFacade;
extern InstanceMapFacade puremvc_facade_instance_map;

using namespace PureMVC;
using namespace PureMVC::Interfaces;
using namespace PureMVC::Patterns;
using namespace PureMVC::Core;

#endif /* __PUREMVC_COMMON_HPP__ */
