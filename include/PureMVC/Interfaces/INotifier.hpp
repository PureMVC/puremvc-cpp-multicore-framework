//  INotifier.hpp
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__PUREMVC_INTERFACES_INOTIFIER_HPP__)
#define __PUREMVC_INTERFACES_INOTIFIER_HPP__

// STL include
#include <string>
// PureMVC include
#if !defined(__PUREMVC_HPP__)
#define __PUREMVC_INCLUDE__
#include "../PureMVC.hpp"
#endif /* __PUREMVC_HPP__ */

namespace PureMVC
{
    namespace Interfaces
    {
        /**
         * The interface definition for a PureMVC Notifier.
         *
         * <P>
         * <code>MacroCommand, Command, Mediator</code> and <code>Proxy</code>
         * all have a need to send <code>Notifications</code>. </P>
         *
         * <P>
         * The <code>INotifier</code> interface provides a common method called
         * <code>sendNotification</code> that relieves implementation code of
         * the necessity to actually construct <code>Notifications</code>.</P>
         *
         * <P>
         * The <code>Notifier</code> class, which all of the above mentioned classes
         * extend, also provides an initialized reference to the <code>Facade</code>
         * Singleton, which is required for the convienience method
         * for sending <code>Notifications</code>, but also eases implementation as these
         * classes have frequent <code>Facade</code> interactions and usually require
         * access to the facade anyway.</P>
         *
         * @see Interfaces/IFacade.hpp PureMVC::Interfaces::IFacade
         * @see Interfaces/INotification.hpp PureMVC::Interfaces::INotification
         */
        struct PUREMVC_API INotifier
        {
            /**
             * Send a <code>INotification</code>.
             *
             * <P>
             * Convenience method to prevent having to construct new
             * notification instances in our implementation code.</P>
             *
             * @param notification_name the name of the notification to send
             * @param body the body of the notification (optional)
             * @param type the type of the notification (optional)
             */
            virtual void sendNotification(std::string const& notification_name, void const* body = NULL, std::string const& type = "") = 0;

            /**
             * Initialize this INotifier instance.
             * <P>
             * This is how a Notifier gets its multitonKey.
             * Calls to sendNotification or to access the
             * facade will fail until after this method
             * has been called.</P>
             *
             * @param key the multitonKey for this INotifier to use
             */
            virtual void initializeNotifier(std::string const& key) = 0;

            /**
             * Get multiton key.
             *
             * @return the key of notifier.
             */
            virtual std::string const& getMultitonKey(void) const = 0;

            /**
             * Virtual destructor.
             */
            virtual ~INotifier(void);
        };
    }
}

#endif /* __PUREMVC_INTERFACES_INOTIFIER_HPP__ */
