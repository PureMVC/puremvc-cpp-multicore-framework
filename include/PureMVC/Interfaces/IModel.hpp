//  IModel.hpp
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__PUREMVC_INTERFACES_IMODEL_HPP__)
#define __PUREMVC_INTERFACES_IMODEL_HPP__

// STL include
#include <string>
// PureMVC include
#if !defined(__PUREMVC_HPP__)
#define __PUREMVC_INCLUDE__
#include "../PureMVC.hpp"
#endif /* __PUREMVC_HPP__ */

#include "IProxy.hpp"
#include "IAggregate.hpp"

namespace PureMVC
{
    namespace Interfaces
    {
        /**
         * The interface definition for a PureMVC Model.
         *
         * <P>
         * In PureMVC, <code>IModel</code> implementors provide
         * access to <code>IProxy</code> objects by named lookup. </P>
         *
         * <P>
         * An <code>IModel</code> assumes these responsibilities:</P>
         *
         * <UL>
         * <LI>Maintain a cache of <code>IProxy</code> instances</LI>
         * <LI>Provide methods for registering, retrieving, and removing <code>IProxy</code> instances</LI>
         * </UL>
         *
         * @see Interfaces/IIterator.hpp PureMVC::Interfaces::IIterator
         * @see Interfaces/IAggregate.hpp PureMVC::Interfaces::IAggregate
         */
        struct PUREMVC_API IModel
        {
#if defined(PUREMVC_USES_TR1)
            typedef std::unique_ptr<IAggregate<std::string> > ProxyNames;
#else
            typedef std::auto_ptr<IAggregate<std::string> > ProxyNames;
#endif

            /**
             * Register an <code>IProxy</code> instance with the <code>Model</code>.
             *
             * @param proxy an object reference to be held by the <code>Model</code>.
             */
            virtual void registerProxy(IProxy* proxy) = 0;

            /**
             * Retrieve an <code>IProxy</code> instance from the Model.
             *
             * @param proxy_name
             * @return the <code>IProxy</code> instance previously registered with the given <code>proxy_name</code>.
             */
            virtual IProxy const& retrieveProxy(std::string const& proxy_name) const = 0;

            /**
             * Retrieve an <code>IProxy</code> instance from the Model.
             *
             * @param proxy_name
             * @return the <code>IProxy</code> instance previously registered with the given <code>proxy_name</code>.
             */
            virtual IProxy& retrieveProxy(std::string const& proxy_name) = 0;

            /**
             * Remove an <code>IProxy</code> instance from the Model.
             *
             * @param proxy_name name of the <code>IProxy</code> instance to be removed.
             * @return the <code>IProxy</code> that was removed from the <code>Model</code>
             */
            virtual IProxy* removeProxy(std::string const& proxy_name) = 0;

            /**
             * Check if a Proxy is registered
             *
             * @param proxy_name
             * @return whether a Proxy is currently registered with the given <code>proxy_name</code>.
             */
            virtual bool hasProxy(std::string const& proxy_name) const = 0;

            /**
             * Fetch all names of proxy
             *
             * @return the aggregate container of <code>proxy_name</code>.
             */
            virtual ProxyNames listProxyNames(void) const = 0;

            /**
             * Virtual destructor.
             */
            virtual ~IModel(void);
        };
    }
}

#endif /* __PUREMVC_INTERFACES_IMODEL_HPP__ */
