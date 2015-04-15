//  SimpleCommand.hpp
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__PUREMVC_PATTERNS_COMMAND_SIMPLE_COMMAND_HPP__)
#define __PUREMVC_PATTERNS_COMMAND_SIMPLE_COMMAND_HPP__

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

        class PUREMVC_API SimpleCommand 
            : public virtual ICommand
            , public virtual INotifier
            , public Notifier
        {
        public:
            /** 
             * Constructor.
             */
            explicit SimpleCommand(void);

            /**
             * Copy constructor.
             */
            explicit SimpleCommand(SimpleCommand const& arg);

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
            virtual void execute(INotification const& notification);

            /**
             * Copy operator.
             */
            SimpleCommand& operator=(SimpleCommand const& arg);

            /**
             * Virtual destructor.
             */
            virtual ~SimpleCommand(void);
        };
    }
}

#endif /* __PUREMVC_PATTERNS_COMMAND_SIMPLE_COMMAND_HPP__ */
