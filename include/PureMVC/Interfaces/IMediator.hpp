//  IMediator.hpp
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__PUREMVC_INTERFACES_IMEDIATOR_HPP__)
#define __PUREMVC_INTERFACES_IMEDIATOR_HPP__

// STL include
#include <string>
// PureMVC include
#if !defined(__PUREMVC_HPP__)
#define __PUREMVC_INCLUDE__
#include "../PureMVC.hpp"
#endif /* __PUREMVC_HPP__ */

#include "INotifier.hpp"
#include "IAggregate.hpp"

namespace PureMVC
{
    namespace Interfaces
    {
        /**
         * The interface definition for a PureMVC Mediator.
         *
         * <P>
         * In PureMVC, <code>IMediator</code> implementors assume these responsibilities:</P>
         * <UL>
         * <LI>Implement a common method which returns a list of all <code>INotification</code>s
         * the <code>IMediator</code> has interest in.</LI>
         * <LI>Implement a notification callback method.</LI>
         * <LI>Implement methods that are called when the IMediator is registered or removed from the View.</LI>
         * </UL>
         * <P>
         * Additionally, <code>IMediator</code>s typically:
         * <UL>
         * <LI>Act as an intermediary between one or more view components such as text boxes or
         * list controls, maintaining references and coordinating their behavior.</LI>
         * <LI>In Flash-based apps, this is often the place where event listeners are
         * added to view components, and their handlers implemented.</LI>
         * <LI>Respond to and generate <code>INotifications</code>, interacting with of
         * the rest of the PureMVC app.
         * </UL></P>
         * <P>
         * When an <code>IMediator</code> is registered with the <code>IView</code>,
         * the <code>IView</code> will call the <code>IMediator</code>'s
         * <code>listNotificationInterests</code> method. The <code>IMediator</code> will
         * return an <code>Array</code> of <code>INotification</code> names which
         * it wishes to be notified about.</P>
         *
         * <P>
         * The <code>IView</code> will then create an <code>Observer</code> object
         * encapsulating that <code>IMediator</code>'s (<code>handleNotification</code>) method
         * and register it as an Observer for each <code>INotification</code> name returned by
         * <code>listNotificationInterests</code>.</P>
         *
         * @see Interfaces/INotification.hpp PureMVC::Interfaces::INotification
         */
        struct PUREMVC_API IMediator : public virtual INotifier
        {
#if defined(PUREMVC_USES_TR1)
            typedef std::unique_ptr<IAggregate<std::string> > NotificationNames;
#else
            typedef std::auto_ptr<IAggregate<std::string> > NotificationNames;
#endif

            /**
             * Get the <code>IMediator</code> instance name
             *
             * @return the <code>IMediator</code> instance name
             */
            virtual std::string const& getMediatorName(void) const = 0;

            /**
             * Get the <code>IMediator</code>'s view component.
             *
             * @return the view component
             */
            virtual void const* getViewComponent(void) const = 0;

            /**
             * Set the <code>IMediator</code>'s view component.
             *
             * @param view_component the <code>void const*</code> view component
             */
            virtual void setViewComponent(void const* view_component) = 0;

            /**
             * List <code>INotification</code> interests.
             *
             * @return an <code>std::list<std::string></code> of the <code>INotification</code> names this <code>IMediator</code> has an interest in.
             */
            virtual NotificationNames listNotificationInterests(void) const = 0;

            /**
             * Handle an <code>INotification</code>.
             *
             * @param notification the <code>INotification</code> to be handled
             */
            virtual void handleNotification(INotification const& notification) = 0;

            /**
             * Called by the View when the Mediator is registered
             */
            virtual void onRegister(void) = 0;

            /**
             * Called by the View when the Mediator is removed
             */
            virtual void onRemove(void) = 0;

            /**
             * Virtual destructor.
             */
            virtual ~IMediator(void);
        };
    }
}

#endif /* __PUREMVC_INTERFACES_IMEDIATOR_HPP__ */
