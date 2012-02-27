//  SimpleCommandTest.cpp
//  PureMVC_C++ Test suite
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if defined(_MSC_VER)
#pragma warning( disable : 4250 ) // Disable: 'class1' : inherits 'class2::member' via dominance
#pragma warning( disable : 4355 ) // The this pointer is valid only within nonstatic member functions. It cannot be used in the initializer list for a base class.ck(16)
#endif

#include <tut/tut.hpp>
#include <tut_reporter.h>
#include <PureMVC/PureMVC.hpp>

#include "SimpleCommandTestCommand.hpp"
#include "SimpleCommandTestVO.hpp"
#include "SimpleCommandTestFirstCommand.hpp"
#include "SimpleCommandTestSecondCommand.hpp"

namespace data
{
    struct SimpleCommandTest
    { };
}

namespace testgroup
{
    typedef tut::test_group<data::SimpleCommandTest> simple_command_test_t;
    typedef simple_command_test_t::object object;
    simple_command_test_t simple_command_test("SimpleCommandTest");
}

namespace tut
{
    using namespace testgroup;

    using PureMVC::Interfaces::INotification;
    using PureMVC::Interfaces::IFacade;
    using PureMVC::Patterns::Notification;
    using PureMVC::Patterns::Facade;

    template<> template<> 
    void simple_command_test_t::object::test<1>(void)
    {
        set_test_name("testSimpleCommandExecute");

        data::SimpleCommandTestVO vo(5);
        Notification note("SimpleCommandTestNote", &vo);
        data::SimpleCommandTestCommand command;

        command.execute((INotification&)note);

        ensure_equals( "Expecting vo.result == 10", vo.result, 10 );
    }

    template<> template<> 
    void simple_command_test_t::object::test<2>(void)
    {
        set_test_name("testRegisterCommandInCommand");

        // create dummy facade.
        IFacade &facade = Facade::getInstance();

        // create test value object
        // vo.input = 10;
        // v.result = 0;
        data::SimpleCommandTestVO vo(10);

        // Register simple test command first.
        data::SimpleCommandTestFirstCommand command;
        facade.registerCommand("simpleCommandTestFirstCommand", &command);

        // activating command first.
        facade.sendNotification("simpleCommandTestFirstCommand", &vo);

        // The result should be 50
        // vo.result += 2 * vo.input;
        // vo.result += 3 * vo.input;
        ensure_equals( "Expecting vo.result == 50", vo.result, 50 );

        // activating again command second.
        facade.sendNotification("simpleCommandTestSecondCommand", &vo);

        // result should be 80
        // vo.result += 3 * vo.input;
        ensure_equals( "Expecting vo.result == 80", vo.result, 80 );

        // activating command first.
        facade.sendNotification("simpleCommandTestFirstCommand", &vo);

        // The result does not change
        ensure_equals( "Expecting vo.result == 80", vo.result, 80 );
    }
}
