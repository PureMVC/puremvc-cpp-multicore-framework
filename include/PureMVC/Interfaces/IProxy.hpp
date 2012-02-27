//  IProxy.hpp
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__PUREMVC_INTERFACES_IPROXY_HPP__)
#define __PUREMVC_INTERFACES_IPROXY_HPP__

// STL include
#include <string>
// PureMVC include
#if !defined(__PUREMVC_HPP__)
#define __PUREMVC_INCLUDE__
#include "../PureMVC.hpp"
#endif /* __PUREMVC_HPP__ */

#include "INotifier.hpp"

namespace PureMVC
{
    namespace Interfaces
    {
        struct PUREMVC_API IProxy : public virtual INotifier
        {
            /**
             * Get the Proxy name
             *
             * @return the Proxy instance name
             */
            virtual std::string const& getProxyName(void) const = 0;

            /**
             * Set the data object
             *
             * @param data the data object
             */
            virtual void setData(void const* data) = 0;

            /**
             * Get the data object
             *
             * @return the data as type void*
             */
            virtual void const* getData(void) const = 0;

            /**
             * Called by the Model when the Proxy is registered
             */
            virtual void onRegister(void) = 0;

            /**
             * Called by the Model when the Proxy is removed
             */
            virtual void onRemove(void) = 0;

            /**
             * Virtual destructor.
             */
            virtual ~IProxy(void);
        };
    }
}

#endif /* __PUREMVC_INTERFACES_IPROXY_HPP__ */
