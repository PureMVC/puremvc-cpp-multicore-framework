//  Controller.hpp
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__PUREMVC_CORE_CONTROLLER_HPP__)
#define __PUREMVC_CORE_CONTROLLER_HPP__

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
#if defined(PUREMVC_USES_TR1)
#if defined(__GNUC__) || defined(__MINGW32__)
#include <tr1/unordered_map>
#else
#include <unordered_map>
#endif
#else
#include <map>
#endif

#include "../Interfaces/IModel.hpp"
#include "../Interfaces/ICommand.hpp"
#include "../Interfaces/IObserver.hpp"
#include "../Patterns/Iterator/Iterator.hpp"

namespace PureMVC
{
    namespace Core
    {
        using Interfaces::IModel;
        using Interfaces::IController;
        using Interfaces::ICommand;
        using Interfaces::IObserver;
        using Interfaces::IAggregate;
        using Interfaces::IIterator;

        /**
         * A Multiton <code>IController</code> implementation.
         *
         * <P>
         * In PureMVC, the <code>Controller</code> class follows the
         * 'Command and Controller' strategy, and assumes these
         * responsibilities:
         * <UL>
         * <LI> Remembering which <code>ICommand</code>s
         * are intended to handle which <code>INotifications</code>.</LI>
         * <LI> Registering itself as an <code>IObserver</code> wiPUREMVC_NO_IMPORT         * the <code>View</code> for each <code>INotification</code>
         * that it has an <code>ICommand</code> mapping for.</LI>
         * <LI> Creating a new instance of the proper <code>ICommand</code>
         * to handle a given <code>INotification</code> when notified by the <code>View</code>.</LI>
         * <LI> Calling the <code>ICommand</code>'s <code>execute</code>
         * method, passing in the <code>INotification</code>.</LI>
         * </UL>
         *
         * <P>
         * Your application must register <code>ICommands</code> with the
         * Controller.
         * <P>
          * The simplest way is to subclass <code>Facade</code>,
         * and use its <code>initializeController</code> method to add your
         * registrations.
         *
         * @see Core/View.hpp PureMVC::Core::View
         * @see Patterns/Observer/Observer.hpp PureMVC::Patterns::Observer
         * @see Patterns/Observer/Notification.hpp PureMVC::Patterns::Notification
         * @see Patterns/Command/SimpleCommand.hpp PureMVC::Patterns::SimpleCommand
         * @see Patterns/Command/MacroCommand.hpp PureMVC::Patterns::MacroCommand
         */
        class PUREMVC_API Controller : public virtual IController
        {
        protected:
#if defined(PUREMVC_USES_TR1)
            typedef std::tr1::unordered_map<std::string, ICommand*> CommandMap;
#else
            typedef std::map<std::string, ICommand*> CommandMap;
#endif
        protected:
            /**
             * Define iterator converter for getting notification name only.
             */
            struct IteratorConverter
#if !defined(__DMC__) // The C++ compiler of Digital Mars cannot resolve this case
            : public std::unary_function<CommandMap::const_iterator, CommandMap::key_type>
#endif
            {
                /**
                 * Converting operator.
                 *
                 * @param iterator the iterator of internal container.
                 * @return the name of notification inside iterator.
                 */
                CommandMap::key_type const& operator()(CommandMap::const_iterator const& iterator) const;
            };
            /**
             * Define iterator range of internal container.
             */
            struct IteratorRange {
                /**
                 * Get begin point.
                 *
                 * @return the begin of iterator.
                 */
                CommandMap::const_iterator begin(CommandMap const* const& iterator) const;
                /*
                 * Get end point.
                 *
                 * @return the end of iterator.
                 */
                CommandMap::const_iterator end(CommandMap const* const& iterator) const;
            };
        public:
            static char const* const DEFAULT_KEY;
        protected:
            // Message Constants
            static char const* const MULTITON_MSG;
        protected:
            // The Multiton Key for this Core
            std::string const _multiton_key;
            // Local reference to View
            IView* _view;
            // Mapping of Notification names to Command Class references
            CommandMap _command_map;
            // Synchronous access
            mutable FastMutex _synchronous_access;
        private:
            Controller(Controller const&);
            Controller(IController const&);
            Controller& operator=(Controller const&);
            Controller& operator=(IController const&);
        protected:
            static IController* find(std::string const& key);
            static void insert(std::string const& key, IController* controller);
        public:
            /**
             * Constructor.
             *
             * <P>
             * This <code>IController</code> implementation is a Multiton,
             * so you should not call the constructor
             * directly, but instead call the static Factory method,
             * passing the unique key for this instance
             * <code>Controller::getInstance( key )</code>
             *
             * @throws Error Error if instance for this Multiton key has already been constructed
             *
             */
            explicit Controller(std::string const& key = Controller::DEFAULT_KEY);

        protected:
            // Support call virtual method in constructor of base class (Controller).
            // Condition: Derived class (class inherit from Controller) must implement
            // method: initializeController
            /**
             * Constructor.
             *
             * <P>
             * Support call virtual method in constructor of base class (<code>Controller</code>).
             *
             * Condition: Derived class (class inherit from <code>Controller</code>) 
             * must implement method: initializeController
             *
             * Please use in this way:
             * <code>
             * 
             * ConcreateController::ConcreateController(void)
             * :Controller(this)
             * {
             *     // Your code here
             * }
             * </code>
             *
             * Factory method <code>Controller::getInstance( key )</code>
             *
             * @throws Error Error if instance for this Multiton key has already been constructed
             *
             */
            template<typename _DerivedType>
            explicit Controller(_DerivedType* instance, std::string const& key = Controller::DEFAULT_KEY)
                : _multiton_key(key)
                , _view(NULL)
            {
                if (find(_multiton_key))
                    throw std::runtime_error(MULTITON_MSG);
                insert(_multiton_key, this);
                instance->_DerivedType::initializeController();
            }

            /**
             * Initialize the Multiton <code>Controller</code> instance.
             *
             * <P>Called automatically by the constructor.</P>
             *
             * <P>Note that if you are using a subclass of <code>View</code>
             * in your application, you should <i>also</i> subclass <code>Controller</code>
             * and override the <code>initializeController</code> method in the
             * following way:</P>
             *
             * <code>
             *        // ensure that the Controller is talking to my IView implementation
             *        override public function initializeController(  ) : void
             *        {
             *            view = MyView.getInstance();
             *        }
             * </code>
             *
             * @return void
             */
            virtual void initializeController(void);

        public:
            /**
             * <code>Controller</code> Multiton Factory method.
             *
             * @return the Multiton instance of <code>Controller</code>
             */
            static IController& getInstance(std::string const& key = Controller::DEFAULT_KEY);

            /**
             * If an <code>ICommand</code> has previously been registered
             * to handle a the given <code>INotification</code>, then it is executed.
             *
             * @param notification an <code>INotification</code>
             */
            virtual void executeCommand(INotification const& notification);

            /**
             * Register a particular <code>ICommand</code> class as the handler
             * for a particular <code>INotification</code>.
             *
             * <P>
             * If an <code>ICommand</code> has already been registered to
             * handle <code>INotification</code>s with this name, it is no longer
             * used, the new <code>ICommand</code> is used instead.</P>
             *
             * The Observer for the new ICommand is only created if this the
             * first time an ICommand has been regisered for this Notification name.
             *
             * @param notification_name the name of the <code>INotification</code>
             * @param command the command of the <code>ICommand</code>
             */
            virtual void registerCommand(std::string const& notification_name, ICommand* command);

            /**
             * Check if a Command is registered for a given Notification
             *
             * @param notification_name
             * @return whether a Command is currently registered for the given <code>notification_name</code>.
             */
            virtual bool hasCommand(std::string const& notification_name) const;

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
             * Remove a previously registered <code>ICommand</code> to <code>INotification</code> mapping.
             *
             * @param notification_name the name of the <code>INotification</code> to remove the <code>ICommand</code> mapping for
             * @return the <code>ICommand</code> that was removed from the <code>Controller</code>
             */
            virtual ICommand* removeCommand(std::string const& notification_name);

            /**
             * List all notification name
             *
             * @return the aggregate container of <code>notification_name</code>.
             */
            virtual NotificationNames listNotificationNames(void) const;

            /**
             * Remove an IController instance
             *
             * @param key of IController instance to remove
             */
            static void removeController(std::string const& key);

            /**
             * Virtual destructor.
             */
            virtual ~Controller(void);
        };
    }
}

#endif /* __PUREMVC_CORE_CONTROLLER_HPP__ */
