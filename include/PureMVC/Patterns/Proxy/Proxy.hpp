//  Proxy.hpp
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__PUREMVC_PATTERNS_PROXY_PROXY_HPP__)
#define __PUREMVC_PATTERNS_PROXY_PROXY_HPP__

// STL include
#include <string>
// PureMVC include
#if !defined(__PUREMVC_HPP__)
#define __PUREMVC_INCLUDE__
#include "../../PureMVC.hpp"
#endif /* __PUREMVC_HPP__ */

#include "../../Interfaces/IProxy.hpp"
#include "../Observer/Notifier.hpp"

namespace PureMVC
{
    namespace Patterns
    {
        using Interfaces::IProxy;
        using Interfaces::INotifier;

        /**
         * A base <code>IProxy</code> implementation.
         *
         * <P>
         * In PureMVC, <code>Proxy</code> classes are used to manage parts of the
         * application's data model. </P>
         *
         * <P>
         * A <code>Proxy</code> might simply manage a reference to a local data object,
         * in which case interacting with it might involve setting and
         * getting of its data in synchronous fashion.</P>
         *
         * <P>
         * <code>Proxy</code> classes are also used to encapsulate the application's
         * interaction with remote services to save or retrieve data, in which case,
         * we adopt an asyncronous idiom; setting data (or calling a method) on the
         * <code>Proxy</code> and listening for a <code>Notification</code> to be sent
         * when the <code>Proxy</code> has retrieved the data from the service. </P>
         *
         * @see Core/Model.hpp PureMVC::Core::Model
         */
         class PUREMVC_API Proxy
             : public virtual IProxy
             , public virtual INotifier
             , public Notifier
         {
         public:
            /**
             * Copy constructor.
             */
            explicit Proxy(Proxy const& arg);

         public:
            /**
             * Constructor.
             */
             explicit Proxy(std::string const& proxy_name = Proxy::NAME, void const* data = NULL);

            /**
             * Get the proxy name.
             */
            virtual std::string const& getProxyName(void) const;

            /**
             * Set the data object.
             */
            virtual void setData(void const* data);

            /**
             * Get the data object.
             */
            virtual void const* getData(void) const;

            /**
             * Called by the Model when the Proxy is registered.
             */
            virtual void onRegister(void);

            /**
             * Called by the Model when the Proxy is removed.
             */
            virtual void onRemove(void);

            /**
             * Assignment operator.
             */
            Proxy& operator=(Proxy const& arg);

            /**
             * Virtual destructor.
             */
            virtual ~Proxy(void);
        protected:
            // the proxy name
            std::string _proxy_name;
            // the data object
            void const* _data;
        public:
            static char const* const NAME;
        };
    }
}

#endif /* __PUREMVC_PATTERNS_PROXY_PROXY_HPP__ */
