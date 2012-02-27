//  MacroCommandTestCommand.hpp
//  PureMVC_C++ Test suite
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__MACRO_COMMAND_TEST_COMMAND_HPP__)
#define __MACRO_COMMAND_TEST_COMMAND_HPP__

#include <PureMVC/PureMVC.hpp>
#include "MacroCommandTestSub1Command.hpp"
#include "MacroCommandTestSub2Command.hpp"

namespace data
{
    using PureMVC::Patterns::MacroCommand;
    /**
     * A MacroCommand subclass used by MacroCommandTest.
     */
    class MacroCommandTestCommand : public MacroCommand
    {
    public:
        /**
         * Constructor.
         */
        MacroCommandTestCommand(void)
            :MacroCommand()
        {
            initializeMacroCommand();
        }
       
    protected:
        /**
         * Initialize the MacroCommandTestCommand by adding
         * its 2 SubCommands.
         */
        void initializeMacroCommand(void)
        {
            addSubCommand(new MacroCommandTestSub1Command());
            addSubCommand(new MacroCommandTestSub2Command() );
        }
    };
}

#endif /* __MACRO_COMMAND_TEST_COMMAND_HPP__ */
