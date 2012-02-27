//  IFacade.hpp
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__PUREMVC_INTERFACES_IFACADE_HPP__)
#define __PUREMVC_INTERFACES_IFACADE_HPP__

// STL include
#include <string>
// PureMVC include
#if !defined(__PUREMVC_HPP__)
#define __PUREMVC_INCLUDE__
#include "../PureMVC.hpp"
#endif /* __PUREMVC_HPP__ */

#include "INotifier.hpp"
#include "IProxy.hpp"
#include "ICommand.hpp"
#include "IMediator.hpp"

namespace PureMVC
{
    namespace Interfaces
    {
        /**
         * The interface definition for a PureMVC Facade.
         *
         * <P>
         * The Facade Pattern suggests providing a single
         * class to act as a central point of communication
         * for a subsystem. </P>
         *
         * <P>
         * In PureMVC, the Facade acts as an interface between
         * the core MVC actors (Model, View, Controller) and
         * the rest of your application.</P>
         *
         * @see Interfaces/IModel.hpp PureMVC::Interfaces::IModel
         * @see Interfaces/IView.hpp PureMVC::Interfaces::IView
         * @see Interfaces/IController.hpp PureMVC::Interfaces::IController
         * @see Interfaces/ICommand.hpp PureMVC::Interfaces::ICommand
         * @see Interfaces/INotification.hpp PureMVC::Interfaces::INotification
         */
        struct PUREMVC_API IFacade : public virtual INotifier
        {
            /**
             * Register an <code>IProxy</code> with the <code>Model</code> by name.
             *
             * @param proxy the <code>IProxy</code> to be registered with the <code>Model</code>.
             */
            virtual void registerProxy(IProxy* proxy) = 0;

            /**
             * Retrieve a <code>IProxy</code> from the <code>Model</code> by name.
             *
             * @param proxy_name the name of the <code>IProxy</code> instance to be retrieved.
             * @return the <code>IProxy</code> previously regisetered by <code>proxy_name</code> with the <code>Model</code>.
             */
            virtual IProxy const& retrieveProxy(std::string const& proxy_name) const = 0;

            /**
             * Retrieve a <code>IProxy</code> from the <code>Model</code> by name.
             *
             * @param proxy_name the name of the <code>IProxy</code> instance to be retrieved.
             * @return the <code>IProxy</code> previously regisetered by <code>proxy_name</code> with the <code>Model</code>.
             */
            virtual IProxy& retrieveProxy(std::string const& proxy_name) = 0;

            /**
             * Remove an <code>IProxy</code> instance from the <code>Model</code> by name.
             *
             * @param proxy_name the <code>IProxy</code> to remove from the <code>Model</code>.
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
             * Register an <code>ICommand</code> with the <code>Controller</code>.
             *
             * @param notification_name the name of the <code>INotification</code> to associate the <code>ICommand</code> with.
             * @param command a reference to the <code>ICommand</code>.
             */
            virtual void registerCommand(std::string const& notification_name, ICommand* command) = 0;

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
             * Remove a previously registered <code>ICommand</code> to <code>INotification</code> mapping from the Controller.
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
             * Register an <code>IMediator</code> instance with the <code>View</code>.
             *
             * @param mediator a reference to the <code>IMediator</code> instance
             */
            virtual void registerMediator(IMediator* mediator) = 0;

            /**
             * Retrieve an <code>IMediator</code> instance from the <code>View</code>.
             *
             * @param mediator_name the name of the <code>IMediator</code> instance to retrievve
             * @return the <code>IMediator</code> previously registered with the given <code>mediator_name</code>.
             */
            virtual IMediator const& retrieveMediator(std::string const& mediator_name) const = 0;

            /**
             * Retrieve an <code>IMediator</code> instance from the <code>View</code>.
             *
             * @param mediator_name the name of the <code>IMediator</code> instance to retrievve
             * @return the <code>IMediator</code> previously registered with the given <code>mediator_name</code>.
             */
            virtual IMediator& retrieveMediator(std::string const& mediator_name) = 0;

            /**
             * Remove a <code>IMediator</code> instance from the <code>View</code>.
             *
             * @param mediator_name name of the <code>IMediator</code> instance to be removed.
             * @return the <code>IMediator</code> instance previously registered with the given <code>mediator_name</code>.
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
             * Notify <code>Observer</code>s.
             * <P>
             * This method is left public mostly for backward
             * compatibility, and to allow you to send custom
             * notification classes using the facade.</P>
             *<P>
             * Usually you should just call sendNotification
             * and pass the parameters, never having to
             * construct the notification yourself.</P>
             *
             * @param notification the <code>INotification</code> to have the <code>View</code> notify <code>Observers</code> of.
             */
            virtual void notifyObservers(INotification const& notification) = 0;

            /**
             * Virtual destructor.
             */
            virtual ~IFacade(void);
        };
    }
}

#endif /* __PUREMVC_INTERFACES_IFACADE_HPP__ */
