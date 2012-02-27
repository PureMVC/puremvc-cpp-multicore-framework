//  SimpleCommandTestCommand.hpp
//  PureMVC_C++ Test suite
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__SIMPLE_COMMAND_TEST_FIRST_COMMAND_HPP__)
#define __SIMPLE_COMMAND_TEST_FIRST_COMMAND_HPP__

#include <PureMVC/PureMVC.hpp>
#include "SimpleCommandTestVO.hpp"
#include "SimpleCommandTestSecondCommand.hpp"

namespace data
{
    using PureMVC::Patterns::SimpleCommand;
    using PureMVC::Interfaces::INotification;
    /**
     * A SimpleCommandTestFirstCommand subclass used by SimpleCommandTest.
     */
    struct SimpleCommandTestFirstCommand: SimpleCommand
    {

        /**
         * Constructor.
         */
        SimpleCommandTestFirstCommand()
            :SimpleCommand()
        { }
        
        /**
         * It just register SimpleCommandTestSecondCommand
         * 
         * @param event the <code>INotification</code> carrying the <code>SimpleCommandTestVO</code>
         */
        virtual void execute(INotification const& note)
        {
            // Combine test. Remove itself.
            getFacade().removeCommand("simpleCommandTestFirstCommand");

            // Send itself again.
            sendNotification("simpleCommandTestFirstCommand", note.getBody(), note.getType());

            SimpleCommandTestVO& vo= *(SimpleCommandTestVO*)note.getBody();
            // Fabricate a result
            vo.result += 2 * vo.input;

            // Register second command.
            static SimpleCommandTestSecondCommand command;
            getFacade().registerCommand("simpleCommandTestSecondCommand", &command);

            // Then sending notification.
            sendNotification("simpleCommandTestSecondCommand", note.getBody(), note.getType());
        }
    };
}

#endif /* __SIMPLE_COMMAND_TEST_FIRST_COMMAND_HPP__ */
