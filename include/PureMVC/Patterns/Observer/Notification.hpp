//  Notification.hpp
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__PUREMVC_PATTERNS_OBSERVER_NOTIFICATION_HPP__)
#define __PUREMVC_PATTERNS_OBSERVER_NOTIFICATION_HPP__

// STL include
#include <string>
// PureMVC include
#if !defined(__PUREMVC_HPP__)
#define __PUREMVC_INCLUDE__
#include "../../PureMVC.hpp"
#endif /* __PUREMVC_HPP__ */

#include "../../Interfaces/INotification.hpp"

namespace PureMVC
{
    namespace Patterns
    {
        using Interfaces::INotification;

        /**
         * A base <code>INotification</code> implementation.
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
         * in Flex/Flash/Apollo. Generally, <code>IMediator</code> implementors
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
         * @see Patterns/Observer/Observer.hpp PureMVC::Patterns::Observer
         *
         */
        class PUREMVC_API Notification : public virtual INotification
        {
        public:
            /**
             * Copy constructor.
             */
            explicit Notification(Notification const& arg);

            /**
             * Constructor.
             *
             * @param name name of the <code>Notification</code> instance. (required)
             * @param body the <code>Notification</code> body. (optional)
             * @param type the type of the <code>Notification</code> (optional)
             */
            Notification(std::string const& name, void const* body = NULL, std::string const& type = "");
            
            /**
             * Get the name of the <code>Notification</code> instance.
             *
             * @return the name of the <code>Notification</code> instance.
             */
            virtual std::string const& getName(void) const;

            /**
             * Set the body of the <code>Notification</code> instance.
             */
            virtual void setBody(void const* body);

            /**
             * Get the body of the <code>Notification</code> instance.
             *
             * @return the body object.
             */
            virtual void const* getBody(void) const;

            /**
             * Set the type of the <code>Notification</code> instance.
             */
            virtual void setType(std::string const& type);

            /**
             * Get the type of the <code>Notification</code> instance.
             *
             * @return the type
             */
            virtual std::string const& getType(void) const;

            /**
             * Get the string representation of the <code>Notification</code> instance.
             *
             * @return the string representation of the <code>Notification</code> instance.
             */
            virtual std::string toString(void) const;
              
            /**
             * Get the string representation of the <code>INotification</code> instance.
             */
            virtual void toString(std::string& arg) const;

            /**
             * Copy operator.
             */
            Notification& operator=(Notification const& arg);

            /**
             * Virtual destructor.
             */
            virtual ~Notification(void);
        private:
            // the name of the notification instance
            std::string _name;
            // the body of the notification instance
            void const* _body;
            // the type of the notification instance
            std::string _type;
        };
    }
}

#endif /* __PUREMVC_PATTERNS_OBSERVER_NOTIFICATION_HPP__ */
