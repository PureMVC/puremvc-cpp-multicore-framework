//  INotification.hpp
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__PUREMVC_INTERFACES_INOTIFICATION_HPP__)
#define __PUREMVC_INTERFACES_INOTIFICATION_HPP__

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
         * The interface definition for a PureMVC Notification.
         *
         * <P>
         * PureMVC does not rely upon underlying event models such
         * as the one provided with Flash, and ActionScript 3 does
         * not have an inherent event model.</P>
         *
         * <P>
         * The Observer Pattern as implemented within PureMVC exists
         * to support event-driven communication between the
         * application and the actors of the MVC triad.</P>
         *
         * <P>
         * Notifications are not meant to be a replacement for Events
         * in Flex/Flash/AIR. Generally, <code>IMediator</code> implementors
         * place event listeners on their view components, which they
         * then handle in the usual way. This may lead to the broadcast of <code>Notification</code>s to
         * trigger <code>ICommand</code>s or to communicate with other <code>IMediators</code>. <code>IProxy</code> and <code>ICommand</code>
         * instances communicate with each other and <code>IMediator</code>s
         * by broadcasting <code>INotification</code>s.</P>
         *
         * <P>
         * A key difference between Flash <code>Event</code>s and PureMVC
         * <code>Notification</code>s is that <code>Event</code>s follow the
         * 'Chain of Responsibility' pattern, 'bubbling' up the display hierarchy
         * until some parent component handles the <code>Event</code>, while
         * PureMVC <code>Notification</code>s follow a 'Publish/Subscribe'
         * pattern. PureMVC classes need not be related to each other in a
         * parent/child relationship in order to communicate with one another
         * using <code>Notification</code>s.
         *
         * @see Interfaces/IView.hpp PureMVC::Interfaces::IView
         * @see Interfaces/IObserver.hpp PureMVC::Interfaces::IObserver
         */

        struct PUREMVC_API INotification
        {
            /**
             * Get the name of the <code>INotification</code> instance.
             * No setter, should be set by constructor only
             */
            virtual std::string const& getName(void) const = 0;

            /**
             * Set the body of the <code>INotification</code> instance
             */
            virtual void setBody(void const* body) = 0;

            /**
             * Get the body of the <code>INotification</code> instance
             */
            virtual void const* getBody(void) const = 0;

            /**
             * Set the type of the <code>INotification</code> instance
             */
            virtual void setType(std::string const& type) = 0;

            /**
             * Get the type of the <code>INotification</code> instance
             */
            virtual std::string const& getType(void) const = 0;

            /**
             * Get the string representation of the <code>INotification</code> instance
             */
            virtual std::string toString(void) const = 0;

            /**
             * Get the string representation of the <code>INotification</code> instance
             */
            virtual void toString(std::string& arg) const = 0;

            /**
             * Virtual destructor.
             */
            virtual ~INotification(void);
        };
    }
}

#endif /* __PUREMVC_INTERFACES_INOTIFICATION_HPP__ */
