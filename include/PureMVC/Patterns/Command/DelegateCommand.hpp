//  SimpleCommand.hpp
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__PUREMVC_PATTERNS_COMMAND_DELEGATE_COMMAND_HPP__)
#define __PUREMVC_PATTERNS_COMMAND_DELEGATE_COMMAND_HPP__

// STL include
#include <string>
// PureMVC include
#if !defined(__PUREMVC_HPP__)
#define __PUREMVC_INCLUDE__
#include "../../PureMVC.hpp"
#endif /* __PUREMVC_HPP__ */

#include "../../Interfaces/ICommand.hpp"
#include "../Observer/Notifier.hpp"

namespace PureMVC
{
    namespace Patterns
    {
        using Interfaces::ICommand;
        using Interfaces::INotifier;

        template<typename _Action>
        class DelegateCommand 
            : public virtual ICommand
            , public virtual INotifier
            , public Notifier
        {
        protected:
            _Action _action;
        public:
            /** 
             * Constructor.
             */
            explicit DelegateCommand(_Action action)
                : INotifier()
                , ICommand()
                , Notifier()
                , _action(action)
            { }

            /**
             * Copy constructor.
             */
            explicit DelegateCommand(DelegateCommand const& arg)
                : INotifier()
                , ICommand()
                , Notifier(arg)
                , _action(arg._action)
            { }

#if defined(PUREMVC_USES_RVALUE)
            /**
             * Move constructor.
             *
             * @param arg The iterator.
             */
            explicit DelegateCommand(DelegateCommand&& arg)
                : INotifier()
                , ICommand()
                , Notifier(arg)
                , _action(std::move(arg._action))
            { }
#endif
        public:
            /**
             * Fulfill the use-case initiated by the given <code>INotification</code>.
             *
             * <P>
             * In the Command Pattern, an application use-case typically
             * begins with some user action, which results in an <code>INotification</code> being broadcast, which
             * is handled by business logic in the <code>execute</code> method of an
             * <code>ICommand</code>.</P>
             *
             * @param notification the <code>INotification</code> to handle.
             */
            virtual void execute(INotification const& notification)
            {
                _action(notification);
            }

            /**
             * Copy operator.
             */
            DelegateCommand& operator=(DelegateCommand const& arg)
            {
                _action = arg._action;
                return *this;
            }

#if defined(PUREMVC_USES_RVALUE)
            /**
             * Move operator.
             */
            DelegateCommand& operator=(DelegateCommand&& arg)
            {
                _action = std::move(arg._action);
                return *this;
            }
#endif
            /**
             * Virtual destructor.
             */
            virtual ~DelegateCommand(void)
            { }
        };

        /**
         * Create new command.
         */
        template<typename _Action>
        inline ICommand* createCommand(_Action action)
        {
            return new DelegateCommand<_Action>(action);
        }

        /**
         * Make a command.
         */
        template<typename _Action>
        inline DelegateCommand<_Action> makeCommand(_Action action)
        {
            return DelegateCommand<_Action>(action);
        }
    }
}

#endif /* __PUREMVC_PATTERNS_COMMAND_DELEGATE_COMMAND_HPP__ */
