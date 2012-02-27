//  IController.hpp
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__PUREMVC_INTERFACES_ICONTROLLER_HPP__)
#define __PUREMVC_INTERFACES_ICONTROLLER_HPP__

// STL include
#include <string>
// PureMVC include
#if !defined(__PUREMVC_HPP__)
#define __PUREMVC_INCLUDE__
#include "../PureMVC.hpp"
#endif /* __PUREMVC_HPP__ */

#include "INotification.hpp"
#include "ICommand.hpp"
#include "IAggregate.hpp"

namespace PureMVC
{
    namespace Interfaces
    {
        /**
         * The interface definition for a PureMVC Controller.
         *
         * <P>
         * In PureMVC, an <code>IController</code> implementor
         * follows the 'Command and Controller' strategy, and
         * assumes these responsibilities:
         * <UL>
         * <LI> Remembering which <code>ICommand</code>s
         * are intended to handle which <code>INotifications</code>.</LI>
         * <LI> Registering itself as an <code>IObserver</code> with
         * the <code>View</code> for each <code>INotification</code>
         * that it has an <code>ICommand</code> mapping for.</LI>
         * <LI> Creating a new instance of the proper <code>ICommand</code>
         * to handle a given <code>INotification</code> when notified by the <code>View</code>.</LI>
         * <LI> Calling the <code>ICommand</code>'s <code>execute</code>
         * method, passing in the <code>INotification</code>.</LI>
         * </UL>
         *
         * @see Interfaces/INotification.hpp PureMVC::Interfaces::INotification
         * @see Interfaces/INotification.hpp PureMVC::Interfaces::ICommand
         * @see Interfaces/IIterator.hpp PureMVC::Interfaces::IIterator
         * @see Interfaces/IAggregate.hpp PureMVC::Interfaces::IAggregate
         */
        struct PUREMVC_API IController
        {
#if defined(PUREMVC_USES_TR1)
            typedef std::unique_ptr<IAggregate<std::string> > NotificationNames;
#else
            typedef std::auto_ptr<IAggregate<std::string> > NotificationNames;
#endif

            /**
             * Register a particular <code>ICommand</code> class as the handler
             * for a particular <code>INotification</code>.
             *
             * @param notification_name the name of the <code>INotification</code>
             * @param command the command of the <code>ICommand</code>
             */
            virtual void registerCommand(std::string const& notification_name, ICommand* command) = 0;

            /**
             * Execute the <code>ICommand</code> previously registered as the
             * handler for <code>INotification</code>s with the given notification name.
             *
             * @param notification the <code>INotification</code> to execute the associated <code>ICommand</code> for
             */
            virtual void executeCommand(INotification const& notification) = 0;

            /**
             * Retrieve an <code>ICommand</code> instance from the Controller.
             *
             * @param notification_name the name of the <code>INotification</code>
             * @return the <code>ICommand</code> instance previously registered with the given <code>notification</code>.
             */
            virtual ICommand const& retrieveCommand(std::string const& notification_name) const = 0;

            /**
             * Retrieve an <code>ICommand</code> instance from the Controller.
             *
             * @param notification_name the name of the <code>INotification</code>
             * @return the <code>ICommand</code> instance previously registered with the given <code>notification</code>.
             */
            virtual ICommand& retrieveCommand(std::string const& notification_name) = 0;

            /**
             * Remove a previously registered <code>ICommand</code> to <code>INotification</code> mapping.
             *
             * @param notification_name the name of the <code>INotification</code> to remove the <code>ICommand</code> mapping for
             * @return the <code>ICommand</code> that was removed from the <code>Controller</code>
             */
            virtual ICommand* removeCommand(std::string const& notification_name) = 0;

            /**
             * Check if a Command is registered for a given Notification
             *
             * @param notification_name
             * @return whether a Command is currently registered for the given <code>notification_name</code>.
             */
            virtual bool hasCommand(std::string const& notification_name) const = 0;

            /**
             * List all notification name
             *
             * @return the aggregate container of <code>notification_name</code>.
             */
            virtual NotificationNames listNotificationNames(void) const = 0;

            /**
             * Virtual destructor.
             */
            virtual ~IController(void);
        };
    }
}

#endif /* __PUREMVC_INTERFACES_ICONTROLLER_HPP__ */
