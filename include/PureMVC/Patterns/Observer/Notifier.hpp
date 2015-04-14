//  Notifier.hpp
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__PUREMVC_PATTERNS_OBSERVER_NOTIFIER_HPP__)
#define __PUREMVC_PATTERNS_OBSERVER_NOTIFIER_HPP__

// STL include
#include <string>
// PureMVC include
#if !defined(__PUREMVC_HPP__)
#define __PUREMVC_INCLUDE__
#include "../../PureMVC.hpp"
#endif /* __PUREMVC_HPP__ */

#include "../../Interfaces/INotifier.hpp"
#include "../../Interfaces/IFacade.hpp"

namespace PureMVC
{
    namespace Patterns
    {
        using Interfaces::INotifier;
        using Interfaces::IFacade;

        /**
         * A Base <code>INotifier</code> implementation.
         *
         * <P>
         * <code>MacroCommand, Command, Mediator</code> and <code>Proxy</code>
         * all have a need to send <code>Notifications</code>. <P>
         * <P>
         * The <code>INotifier</code> interface provides a common method called
         * <code>sendNotification</code> that relieves implementation code of
         * the necessity to actually construct <code>Notifications</code>.</P>
         *
         * <P>
         * The <code>Notifier</code> class, which all of the above mentioned classes
         * extend, provides an initialized reference to the <code>Facade</code>
         * Multiton, which is required for the convienience method
         * for sending <code>Notifications</code>, but also eases implementation as these
         * classes have frequent <code>Facade</code> interactions and usually require
         * access to the facade anyway.</P>
         *
         * <P>
         * NOTE: In the MultiCore version of the framework, there is one caveat to
         * notifiers, they cannot send notifications or reach the facade until they
         * have a valid multitonKey.
         *
         * The multitonKey is set:
         *   * on a Command when it is executed by the Controller
         *   * on a Mediator is registered with the View
         *   * on a Proxy is registered with the Model.
         *
         * @see Patterns/Proxy/Proxy.hpp PureMVC::Patterns::Proxy
         * @see Patterns/Facade/Facade.hpp PureMVC::Patterns::Facade
         * @see Patterns/Mediator/Mediator.hpp PureMVC::Patterns::Mediator
         * @see Patterns/Command/MacroCommand.hpp PureMVC::Patterns::MacroCommand
         * @see Patterns/Command/SimpleCommand.hpp PureMVC::Patterns::SimpleCommand
         */
        class PUREMVC_API Notifier : public virtual INotifier
        {
        public:
            /**
             * Constructor.
             */
            explicit Notifier(void);

            /**
             * Copy constructor.
             */
            explicit Notifier(Notifier const& arg);
        public:
            /**
             * Create and send an <code>INotification</code>.
             *
             * <P>
             * Keeps us from having to construct new INotification
             * instances in our implementation code.
             * @param notification_name the name of the notiification to send.
             * @param body the body of the notification (optional).
             * @param type the type of the notification (optional).
             */
            virtual void sendNotification(std::string const& notification_name, void const* body = NULL, std::string const& type = "");

            /**
             * Initialize this INotifier instance.
             * <P>
             * This is how a Notifier gets its multitonKey.
             * Calls to sendNotification or to access the
             * facade will fail until after this method
             * has been called.</P>
             *
             * <P>
             * Mediators, Commands or Proxies may override
             * this method in order to send notifications
             * or access the Multiton Facade instance as
             * soon as possible. They CANNOT access the facade
             * in their constructors, since this method will not
             * yet have been called.</P>
             *
             * @param key the multitonKey for this INotifier to use.
             */
            virtual void initializeNotifier(std::string const& key);

            /**
             * Get multi ton key.
             *
             * @return the key of notifier.
             */
             virtual std::string const& getMultitonKey(void) const;

            /**
             * Copy operator.
             */
            Notifier& operator=(Notifier const& arg);

            /**
             * Virtual destructor.
             */
            virtual ~Notifier(void);
        protected:
            // Return the Multiton Facade instance
            IFacade& getFacade();
        protected:
            // The Multiton Key for this app
            std::string _multiton_key;
            // Message Constants
            static char const* const MULTITON_MSG;
        };
    }
}

#endif /* __PUREMVC_PATTERNS_OBSERVER_NOTIFIER_HPP__ */
