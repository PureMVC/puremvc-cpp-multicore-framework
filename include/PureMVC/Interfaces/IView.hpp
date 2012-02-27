//  IView.hpp
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__PUREMVC_INTERFACES_IVIEW_HPP__)
#define __PUREMVC_INTERFACES_IVIEW_HPP__

// STL include
#include <string>
// PureMVC include
#if !defined(__PUREMVC_HPP__)
#define __PUREMVC_INCLUDE__
#include "../PureMVC.hpp"
#endif /* __PUREMVC_HPP__ */

#include "INotification.hpp"
#include "IObserver.hpp"
#include "IMediator.hpp"
#include "IAggregate.hpp"

namespace PureMVC
{
    namespace Interfaces
    {
        /**
         * The interface definition for a PureMVC View.
         *
         * <P>
         * In PureMVC, <code>IView</code> implementors assume these responsibilities:</P>
         *
         * <P>
         * In PureMVC, the <code>View</code> class assumes these responsibilities:
         * <UL>
         * <LI>Maintain a cache of <code>IMediator</code> instances.</LI>
         * <LI>Provide methods for registering, retrieving, and removing <code>IMediators</code>.</LI>
         * <LI>Managing the observer lists for each <code>INotification</code> in the application.</LI>
         * <LI>Providing a method for attaching <code>IObservers</code> to an <code>INotification</code>'s observer list.</LI>
         * <LI>Providing a method for broadcasting an <code>INotification</code>.</LI>
         * <LI>Notifying the <code>IObservers</code> of a given <code>INotification</code> when it broadcast.</LI>
         * </UL>
         *
         * @see Interfaces/IMediator.hpp PureMVC::Interfaces::IMediator
         * @see Interfaces/IObserver.hpp PureMVC::Interfaces::IObserver
         * @see Interfaces/INotification.hpp PureMVC::Interfaces::INotification
         * @see Interfaces/IIterator.hpp PureMVC::Interfaces::IIterator
         * @see Interfaces/IAggregate.hpp PureMVC::Interfaces::IAggregate
         */
        struct PUREMVC_API IView
        {
#if defined(PUREMVC_USES_TR1)
            typedef std::unique_ptr<IAggregate<std::string> > MediatorNames;
#else
            typedef std::auto_ptr<IAggregate<std::string> > MediatorNames;
#endif

            /**
             * Register an <code>IObserver</code> to be notified
             * of <code>INotifications</code> with a given name.
             *
             * @param notification_name the name of the <code>INotifications</code> to notify this <code>IObserver</code> of
             * @param observer the <code>IObserver</code> to register
             */
            virtual void registerObserver(std::string const& notification_name, IObserver* observer) = 0;

            /**
             * Remove a group of observers from the observer list for a given Notification name.
             * <P>
             * @param notification_name which observer list to remove from
             * @param notify_context removed the observers with this object as their notify_context
             */
            virtual void removeObserver(std::string const& notification_name, void const* notify_context) = 0;

            /**
             * Notify the <code>IObservers</code> for a particular <code>INotification</code>.
             *
             * <P>
             * All previously attached <code>IObservers</code> for this <code>INotification</code>'s
             * list are notified and are passed a reference to the <code>INotification</code> in
             * the order in which they were registered.</P>
             *
             * @param notification the <code>INotification</code> to notify <code>IObservers</code> of.
             */
            virtual void notifyObservers(INotification const& notification) = 0;

            /**
             * Register an <code>IMediator</code> instance with the <code>View</code>.
             *
             * <P>
             * Registers the <code>IMediator</code> so that it can be retrieved by name,
             * and further interrogates the <code>IMediator</code> for its
             * <code>INotification</code> interests.</P>
             * <P>
             * If the <code>IMediator</code> returns any <code>INotification</code>
             * names to be notified about, an <code>Observer</code> is created encapsulating
             * the <code>IMediator</code> instance's <code>handleNotification</code> method
             * and registering it as an <code>Observer</code> for all <code>INotifications</code> the
             * <code>IMediator</code> is interested in.</p>
             *
             * @param mediator a reference to the <code>IMediator</code> instance
             */
            virtual void registerMediator(IMediator* mediator) = 0;

            /**
             * Retrieve an <code>IMediator</code> from the <code>View</code>.
             *
             * @param mediator_name the name of the <code>IMediator</code> instance to retrieve.
             * @return the <code>IMediator</code> instance previously registered with the given <code>mediator_name</code>.
             */
            virtual IMediator const& retrieveMediator(std::string const& mediator_name) const = 0;

            /**
             * Retrieve an <code>IMediator</code> from the <code>View</code>.
             *
             * @param mediator_name the name of the <code>IMediator</code> instance to retrieve.
             * @return the <code>IMediator</code> instance previously registered with the given <code>mediator_name</code>.
             */
            virtual IMediator& retrieveMediator(std::string const& mediator_name) = 0;

            /**
             * Remove an <code>IMediator</code> from the <code>View</code>.
             *
             * @param mediator_name name of the <code>IMediator</code> instance to be removed.
             * @return the <code>IMediator</code> that was removed from the <code>View</code>
             */
            virtual IMediator* removeMediator(std::string const& mediator_name) = 0;

            /**
             * Check if a Mediator is registered or not
             *
             * @param mediator_name
             * @return whether a Mediator is registered with the given <code>mediator_name</code>.
             */
            virtual bool hasMediator(std::string const& mediator_name) const = 0;

            /**
             * Fetch all names of mediator
             *
             * @return the aggregate container of <code>mediator_name</code>.
             */
            virtual MediatorNames listMediatorNames(void) const = 0;

            /**
             * Virtual destructor.
             */
            virtual ~IView(void);
        };
    }
}

#endif /* __PUREMVC_INTERFACES_IVIEW_HPP__ */
