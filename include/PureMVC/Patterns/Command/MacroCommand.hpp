//  MacroCommand.hpp
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__PUREMVC_PATTERNS_COMMAND_MACRO_COMMAND_HPP__)
#define __PUREMVC_PATTERNS_COMMAND_MACRO_COMMAND_HPP__

// STL include
#include <string>
#include <list>
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
        using Interfaces::INotification;

        /**
         * A base <code>ICommand</code> implementation that executes other <code>ICommand</code>s.
         *
         * <P>
         * A <code>MacroCommand</code> maintains an list of
         * <code>ICommand</code> Class references called <i>SubCommands</i>.</P>
         *
         * <P>
         * When <code>execute</code> is called, the <code>MacroCommand</code>
         * instantiates and calls <code>execute</code> on each of its <i>SubCommands</i> turn.
         * Each <i>SubCommand</i> will be passed a reference to the original
         * <code>INotification</code> that was passed to the <code>MacroCommand</code>'s
         * <code>execute</code> method.</P>
         *
         * <P>
         * Unlike <code>SimpleCommand</code>, your subclass
         * should not override <code>execute</code>, but instead, should
         * override the <code>initializeMacroCommand</code> method,
         * calling <code>addSubCommand</code> once for each <i>SubCommand</i>
         * to be executed.</P>
         *
         * <P>
         *
         * @see Core/Controller.hpp PureMVC::Core::Controller
         * @see Patterns/Observer/Notification.hpp PureMVC::Patterns::Notification
         * @see Patterns/Command/SimpleCommand.hpp PureMVC::Patterns::SimpleCommand
         */
        class PUREMVC_API MacroCommand
            : public virtual ICommand
            , public virtual INotifier
            , public Notifier
        {
        public:
            /**
             * Constructor.
             *
             * <P>
             * You should not need to define a constructor,
             * instead, override the <code>initializeMacroCommand</code>
             * method.</P>
             *
             * <P>
             * If your subclass does define a constructor, be
             * sure to call <code>super()</code>.</P>
             */
            explicit MacroCommand(void);

            /**
             * Constructor.
             *
             * @param command_list a reference to the list of command.
             */
            explicit MacroCommand(std::list<ICommand*> const& command_list);

            /**
             * Constructor.
             *
             * @param begin the begin of iterator
             * @param end the end of iterator
             */
            template<typename _Iterator>
            explicit MacroCommand(_Iterator begin, _Iterator end)
                : INotifier()
                , ICommand()
                , Notifier()
            {
                initializeMacroCommand();
                for(; begin != end; ++begin)
                    addSubCommand(*begin);
            }

            /**
             * Copy constructor.
             */
            explicit MacroCommand(MacroCommand const& arg);

        protected:
            /**
             * Initialize the <code>MacroCommand</code>.
             *
             * <P>
             * In your subclass, override this method to
             * initialize the <code>MacroCommand</code>'s <i>SubCommand</i>
             * list with <code>ICommand</code> class references.
             *
             * <P>
             * Note that <i>SubCommand</i>s may be any <code>ICommand</code> implementor,
             * <code>MacroCommand</code>s or <code>SimpleCommands</code> are both acceptable.
             */
             virtual void initializeMacroCommand(void);

            /**
             * Add a <i>SubCommand</i>.
             *
             * <P>
             * The <i>SubCommands</i> will be called in First In/First Out (FIFO)
             * order.</P>
             *
             * @param command a reference to the <code>ICommand</code> of the <code>ICommand</code>.
             */
            virtual void addSubCommand(ICommand* command);

        public:
            /**
             * Execute this <code>MacroCommand</code>'s <i>SubCommands</i>.
             *
             * <P>
             * The <i>SubCommands</i> will be called in First In/First Out (FIFO)
             * order.
             *
             * @param notification the <code>INotification</code> object to be passsed to each <i>SubCommand</i>.
             */
            virtual void execute(INotification const& notification);

            /**
             * Copy operator.
             */
            MacroCommand& operator=(MacroCommand const& arg);

            /**
             * Virtual destructor.
             */
            virtual ~MacroCommand(void);
        private:
            typedef std::list<ICommand*> CommandList;
            CommandList _sub_commands;
        };
    }
}

#endif /* __PUREMVC_PATTERNS_COMMAND_MACRO_COMMAND_HPP__ */
