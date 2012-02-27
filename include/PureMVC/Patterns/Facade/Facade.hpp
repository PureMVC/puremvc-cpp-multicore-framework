//  Facade.hpp
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__PUREMVC_PATTERNS_FACADE_FACADE_HPP__)
#define __PUREMVC_PATTERNS_FACADE_FACADE_HPP__

// STL include
#include <string>
#include <exception>
#include <stdexcept>
#include <cassert>
// PureMVC include
#if !defined(__PUREMVC_HPP__)
#define __PUREMVC_INCLUDE__
#include "../PureMVC.hpp"
#endif /* __PUREMVC_HPP__ */

#include "../../Interfaces/IFacade.hpp"
#include "../../Interfaces/ICommand.hpp"
#include "../../Interfaces/IModel.hpp"
#include "../../Interfaces/IView.hpp"
#include "../../Interfaces/IController.hpp"
#include "../../Interfaces/IMediator.hpp"
#include "../../Interfaces/IAggregate.hpp"
#include "../../Interfaces/IProxy.hpp"
#include "../../Patterns/Observer/Notifier.hpp"

namespace PureMVC
{
    namespace Patterns
    {
        using Interfaces::IFacade;
        using Interfaces::ICommand;
        using Interfaces::IModel;
        using Interfaces::IView;
        using Interfaces::IController;
        using Interfaces::IMediator;
        using Interfaces::IProxy;
        using Interfaces::IAggregate;

        /**
         * A base Multiton <code>IFacade</code> implementation.
         *
         * @see Core/Model.hpp PureMVC::Core::Model
         * @see Core/View.hpp PureMVC::Core::View
         * @see Core/Controller.hpp PureMVC::Core::Controller
         */
        class PUREMVC_API Facade : public virtual IFacade, public Notifier
        {
        public:
#if defined(PUREMVC_USES_TR1)
            typedef std::unique_ptr<IAggregate<std::string> > CoreNames;
#else
            typedef std::auto_ptr<IAggregate<std::string> > CoreNames;
#endif
        public:
            static char const* const DEFAULT_KEY;
        private:
            Facade(Facade const&);
            Facade(IFacade const&);
            Facade& operator=(Facade const&);
            Facade& operator=(IFacade const&);
        protected:
            static IFacade* find(std::string const& key);
            static void insert(std::string const& key, IFacade* facade);
        public:
            /**
             * Constructor.
             *
             * <P>
             * This <code>IFacade</code> implementation is a Multiton,
             * so you should not call the constructor
             * directly, but instead call the static Factory method,
             * passing the unique key for this instance
             * <code>Facade.getInstance( multitonKey )</code>
             *
             * @throws Error Error if instance for this Multiton key has already been constructed
             *
             */
            explicit Facade(std::string const& key = Facade::DEFAULT_KEY);

        protected:
            /**
             * Constructor.
             *
             * <P>
             * Support call virtual method in constructor of base class (<code>Facade</code>).
             *
             * Condition: Derived class (class inherit from <code>Facade</code>) 
             * must implement method: initializeNotifier, initializeFacade
             *
             * Please use int constructor:
             * <code>
             * 
             * ConcreateFacade::ConcreateFacade(void)
             * :Facade(this)
             * {
             *     // Your code here
             * }
             * </code>
             *
             * Factory method <code>Facade::getInstance( key )</code>
             *
             * @throws Error Error if instance for this Multiton key has already been constructed
             *
             */
            template<typename _DerivedType>
            explicit Facade(_DerivedType* instance, std::string const& key = Facade::DEFAULT_KEY)
                : _controller(NULL)
                , _model(NULL)
                , _view(NULL)
            {
                if (find(key))
                    throw std::runtime_error(MULTITON_MSG);
                instance->_DerivedType::initializeNotifier(key);
                insert(key, this);
                instance->_DerivedType::initializeFacade();
            }

            /**
             * Initialize the Multiton <code>Facade</code> instance.
             *
             * <P>
             * Called automatically by the constructor. Override in your
             * subclass to doany subclass specific initializations. Be
             * sure to call <code>super.initializeFacade()</code>, though.</P>
             */
            virtual void initializeFacade(void);

        public:
            /**
             * Facade Multiton Factory method
             *
             * @return the Multiton instance of the Facade
             */
            static IFacade& getInstance(std::string const& key = Facade::DEFAULT_KEY);

        protected:
            /**
             * Initialize the <code>Controller</code>.
             *
             * <P>
             * Called by the <code>initializeFacade</code> method.
             * Override this method in your subclass of <code>Facade</code>
             * if one or both of the following are true:
             * <UL>
             * <LI> You wish to initialize a different <code>IController</code>.</LI>
             * <LI> You have <code>Commands</code> to register with the <code>Controller</code> at startup. </LI>
             * </UL>
             * If you don't want to initialize a different <code>IController</code>,
             * call <code>super.initializeController()</code> at the beginning of your
             * method, then register <code>Command</code>s.
             * </P>
             */
            virtual void initializeController(void);

            /**
             * Initialize the <code>Model</code>.
             *
             * <P>
             * Called by the <code>initializeFacade</code> method.
             * Override this method in your subclass of <code>Facade</code>
             * if one or both of the following are true:
             * <UL>
             * <LI> You wish to initialize a different <code>IModel</code>.</LI>
             * <LI> You have <code>Proxy</code>s to register with the Model that donot
             * retrieve a reference to the Facade at construction time.</LI>
             * </UL>
             * If you don't want to initialize a different <code>IModel</code>,
             * call <code>super.initializeModel()</code> at the beginning of your
             * method, then register <code>Proxy</code>s.
             * <P>
             * Note: This method is <i>rarely</i> overridden; in practice you are more
             * likely to use a <code>Command</code> to create and register <code>Proxy</code>s
             * with the <code>Model</code>, since <code>Proxy</code>s with mutable data will likely
             * need to send <code>INotification</code>s and thus will likely want to fetch a reference to
             * the <code>Facade</code> during their construction.
             * </P>
             */
            virtual void initializeModel(void);

            /**
             * Initialize the <code>View</code>.
             *
             * <P>
             * Called by the <code>initializeFacade</code> method.
             * Override this method in your subclass of <code>Facade</code>
             * if one or both of the following are true:
             * <UL>
             * <LI> You wish to initialize a different <code>IView</code>.</LI>
             * <LI> You have <code>Observers</code> to register with the <code>View</code></LI>
             * </UL>
             * If you don't want to initialize a different <code>IView</code>,
             * call <code>super.initializeView()</code> at the beginning of your
             * method, then register <code>IMediator</code> instances.
             * <P>
             * Note: This method is <i>rarely</i> overridden; in practice you are more
             * likely to use a <code>Command</code> to create and register <code>Mediator</code>s
             * with the <code>View</code>, since <code>IMediator</code> instances will need to send
             * <code>INotification</code>s and thus will likely want to fetch a reference
             * to the <code>Facade</code> during their construction.
             * </P>
             */
            virtual void initializeView(void);

        public:
            /**
             * Register an <code>ICommand</code> with the <code>Controller</code> by Notification name.
             *
             * @param notification_name the name of the <code>INotification</code> to associate the <code>ICommand</code> with
             * @param command a reference to the instance of the <code>ICommand</code>
             */
            virtual void registerCommand(std::string const& notification_name, ICommand* command);

            /**
             * Remove a previously registered <code>ICommand</code> to <code>INotification</code> mapping from the Controller.
             *
             * @param notification_name the name of the <code>INotification</code> to remove the <code>ICommand</code> mapping for
             * @return the <code>ICommand</code> that was removed from the <code>Controller</code>
             */
            virtual ICommand* removeCommand(std::string const& notification_name);

            /**
             * Retrieve an <code>ICommand</code> instance from the Controller.
             *
             * @param notification_name the notification of the <code>INotification</code>
             * @return the <code>ICommand</code> instance previously registered with the given <code>notification</code>.
             */
            virtual ICommand const& retrieveCommand(std::string const& notification_name) const;

            /**
             * Retrieve an <code>ICommand</code> instance from the Controller.
             *
             * @param notification_name the name of the <code>INotification</code>
             * @return the <code>ICommand</code> instance previously registered with the given <code>notification</code>.
             */
            virtual ICommand& retrieveCommand(std::string const& notification_name);

            /**
             * Check if a Command is registered for a given Notification
             *
             * @param notification_name
             * @return whether a Command is currently registered for the given <code>notificationName</code>.
             */
            virtual bool hasCommand(std::string const& notification_name) const;

            /**
             * Register an <code>IProxy</code> with the <code>Model</code> by name.
             *
             * @param proxy the name of the <code>IProxy</code>.
             * @param proxy the <code>IProxy</code> instance to be registered with the <code>Model</code>.
             */
            virtual void registerProxy (IProxy* proxy);

            /**
             * Retrieve an <code>IProxy</code> from the <code>Model</code> by name.
             *
             * @param proxy_name the name of the proxy to be retrieved.
             * @return the <code>IProxy</code> instance previously registered with the given <code>proxyName</code>.
             */
            virtual IProxy const& retrieveProxy (std::string const& proxy_name) const;

            /**
             * Retrieve an <code>IProxy</code> from the <code>Model</code> by name.
             *
             * @param proxy_name the name of the proxy to be retrieved.
             * @return the <code>IProxy</code> instance previously registered with the given <code>proxyName</code>.
             */
            virtual IProxy& retrieveProxy (std::string const& proxy_name);

            /**
             * Remove an <code>IProxy</code> from the <code>Model</code> by name.
             *
             * @param proxy_name the <code>IProxy</code> to remove from the <code>Model</code>.
             * @return the <code>IProxy</code> that was removed from the <code>Model</code>
             */
            virtual IProxy* removeProxy (std::string const& proxy_name);

            /**
             * Check if a Proxy is registered
             *
             * @param proxy_name
             * @return whether a Proxy is currently registered with the given <code>proxyName</code>.
             */
            virtual bool hasProxy(std::string const& proxy_name) const;

            /**
             * Register a <code>IMediator</code> with the <code>View</code>.
             *
             * @param mediator a reference to the <code>IMediator</code>
             */
            virtual void registerMediator(IMediator* mediator);

            /**
             * Retrieve an <code>IMediator</code> from the <code>View</code>.
             *
             * @param mediator_name
             * @return the <code>IMediator</code> previously registered with the given <code>mediatorName</code>.
             */
            virtual IMediator const& retrieveMediator(std::string const& mediator_name) const;

            /**
             * Retrieve an <code>IMediator</code> from the <code>View</code>.
             *
             * @param mediator_name
             * @return the <code>IMediator</code> previously registered with the given <code>mediatorName</code>.
             */
            virtual IMediator& retrieveMediator(std::string const& mediator_name);

            /**
             * Remove an <code>IMediator</code> from the <code>View</code>.
             *
             * @param mediator_name name of the <code>IMediator</code> to be removed.
             * @return the <code>IMediator</code> that was removed from the <code>View</code>
             */
            virtual IMediator* removeMediator(std::string const& mediator_name);

            /**
             * Check if a Mediator is registered or not
             *
             * @param mediator_name
             * @return whether a Mediator is registered with the given <code>mediatorName</code>.
             */
            virtual bool hasMediator(std::string const& mediator_name) const;

            /**
             * Create and send an <code>INotification</code>.
             *
             * <P>
             * Keeps us from having to construct new notification
             * instances in our implementation code.
             * @param notification_name the name of the notification to send
             * @param body the body of the notification (optional)
             * @param type the type of the notification (optional)
             */
             virtual void sendNotification(std::string const& notification_name, void const* body = NULL, std::string const& type = "");

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
            virtual void notifyObservers(INotification const& notification);

            /**
             * Check if a Core is registered or not
             *
             * @param key the multiton key for the Core in question
             * @return whether a Core is registered with the given <code>key</code>.
             */
            static bool hasCore(std::string const& key);

            /**
             * Remove a Core.
             * <P>
             * Remove the Model, View, Controller and Facade
             * instances for the given key.</P>
             *
             * @param key of the Core to remove
             */
            static void removeCore(std::string const& key);

            /**
             * List all names of core
             *
             * @return the aggregate container of <code>facade name</code>.
             */
            static CoreNames listCores(void);

            /**
             * Broadcast notification for all Facade.
             *
             * @param notification the <code>INotification</code> to have the <code>View</code> notify <code>Observers</code> of.
             */
            static void broadcastNotification(INotification const& notification);

            /**
             * Broadcast notification for all Facade.
             *
             * @param notification_name the name of the notification to send
             * @param body the body of the notification (optional)
             * @param type the type of the notification (optional)
             */
            static void broadcastNotification(std::string const& notification_name, void const* body = NULL, std::string const& type = "");

            /**
             * Virtual destructor.
             */
            virtual ~Facade(void);

        protected:
            // References to Model, View and Controller
            IController* _controller;
            IModel* _model;
            IView* _view;
            // Message Constants
            static char const* const MULTITON_MSG;
        };
    }
}

#endif /* __PUREMVC_PATTERNS_FACADE_FACADE_HPP__ */
