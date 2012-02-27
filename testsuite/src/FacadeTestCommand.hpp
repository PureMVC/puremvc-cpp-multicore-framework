//  FacadeTestCommand.hpp
//  PureMVC_C++ Test suite
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__FACADE_TEST_COMMAND_HPP__)
#define __FACADE_TEST_COMMAND_HPP__

#include <PureMVC/PureMVC.hpp>
#include "FacadeTestVO.hpp"

namespace data
{
    using PureMVC::Interfaces::INotification;
    using PureMVC::Patterns::SimpleCommand;

    /**
     * A SimpleCommand subclass used by FacadeTest.
     *
     * @see org.puremvc.as3.multicore.patterns.facade.FacadeTest FacadeTest
     * @see org.puremvc.as3.multicore.patterns.facade.FacadeTestVO FacadeTestVO
     */
    struct FacadeTestCommand : public SimpleCommand
    {
        void execute(INotification const& notification)
        {
            FacadeTestVO& vo =  *(FacadeTestVO*) notification.getBody();
            vo.result = vo.input * 2;
        }
    };
}

#endif /* __FACADE_TEST_COMMAND_HPP__ */
