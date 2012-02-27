//  ControllerTestCommand.hpp
//  PureMVC_C++ Test suite
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__CONTROLLER_TEST_COMMAND_HPP__)
#define __CONTROLLER_TEST_COMMAND_HPP__

#include <PureMVC/PureMVC.hpp>
#include "ControllerTestVO.hpp"

namespace data
{
    using PureMVC::Patterns::SimpleCommand;
    using PureMVC::Interfaces::INotification;
    using PureMVC::Interfaces::ICommand;
    /**
     * A SimpleCommand subclass used by ControllerTest.
     */
    struct ControllerTestCommand
        : public virtual ICommand
        , public SimpleCommand
    {
        /**
         * Constructor.
         */
        ControllerTestCommand(void)
            :SimpleCommand()
        { }
        
        /**
         * Fabricate a result by multiplying the input by 2
         * 
         * @param note the note carrying the ControllerTestVO
         */
        virtual void execute(INotification const& note)
        {
            ControllerTestVO& vo= *(ControllerTestVO*)note.getBody();
            // Fabricate a result
            vo.result = 2 * vo.input;
        }
    };
}

#endif /* __CONTROLLER_TEST_COMMAND_HPP__ */ 
