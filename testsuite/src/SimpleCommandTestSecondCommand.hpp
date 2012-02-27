//  SimpleCommandTestCommand.hpp
//  PureMVC_C++ Test suite
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__SIMPLE_COMMAND_TEST_SECOND_COMMAND_HPP__)
#define __SIMPLE_COMMAND_TEST_SECOND_COMMAND_HPP__

#include <PureMVC/PureMVC.hpp>
#include "SimpleCommandTestVO.hpp"

namespace data
{
    using PureMVC::Patterns::SimpleCommand;
    using PureMVC::Interfaces::INotification;
    /**
     * A SimpleCommand subclass used by SimpleCommandTest.
     */
    struct SimpleCommandTestSecondCommand: SimpleCommand
    {

        /**
         * Constructor.
         */
        SimpleCommandTestSecondCommand()
            :SimpleCommand()
        { }
        
        /**
         * OUtput
         * 
         * @param event the <code>INotification</code> carrying the <code>SimpleCommandTestVO</code>
         */
        virtual void execute(INotification const& note)
        {
            SimpleCommandTestVO& vo= *(SimpleCommandTestVO*)note.getBody();
            // Fabricate a result
            vo.result += 3 * vo.input;
        }
    };
}

#endif /* __SIMPLE_COMMAND_TEST_SECOND_COMMAND_HPP__ */
