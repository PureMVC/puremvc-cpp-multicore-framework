//  MacroCommandTestSub1Command.hpp
//  PureMVC_C++ Test suite
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__MACRO_COMMAND_TEST_SUB1_COMMAND_HPP__)
#define __MACRO_COMMAND_TEST_SUB1_COMMAND_HPP__

#include "MacroCommandTestVO.hpp"

namespace data
{
    using PureMVC::Patterns::SimpleCommand;
    using PureMVC::Patterns::INotification;
    /**
     * A SimpleCommand subclass used by MacroCommandTestCommand.
     */
    struct MacroCommandTestSub1Command: public SimpleCommand
    {
        MacroCommandTestSub1Command(void)
            :SimpleCommand()
        { }

        /**
         * Fabricate a result by multiplying the input by 2
         * 
         * @param event the <code>IEvent</code> carrying the <code>MacroCommandTestVO</code>
         */
        void execute(INotification const& note)
        {
            MacroCommandTestVO& vo = *(MacroCommandTestVO*)note.getBody(); 
            // Fabricate a result
            vo.result1 = 2 * vo.input;
        }
    };
}

#endif /* __MACRO_COMMAND_TEST_SUB1_COMMAND_HPP__ */
