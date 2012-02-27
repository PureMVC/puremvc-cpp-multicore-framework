//  MacroCommandTest.cpp
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

#include "MacroCommandTestCommand.hpp"
#include "MacroCommandTestVO.hpp"
#include "MacroCommandTestSub1Command.hpp"
#include "MacroCommandTestSub2Command.hpp"

namespace data 
{
    struct MacroCommandTest
    { };
}

namespace testgroup
{
    typedef tut::test_group<data::MacroCommandTest> macro_command_test_t;
    typedef macro_command_test_t::object object;
    macro_command_test_t macro_command_test("MacroCommandTest");
}

namespace tut
{
    using namespace testgroup;

    using PureMVC::Interfaces::INotification;
    using PureMVC::Interfaces::ICommand;
    using PureMVC::Patterns::MacroCommand;
    using PureMVC::Patterns::Notification;

    template<> template<> 
    void object::test<1>(void)
    {
        set_test_name("testMacroCommandExecute");

        data::MacroCommandTestVO vo(5);
        Notification note("MacroCommandTest", &vo);
        data::MacroCommandTestCommand command;

        command.execute((INotification&)note);

        ensure_equals( "Expecting vo.result1 == 10", vo.result1, 10);
        ensure_equals( "Expecting vo.result2 == 25", vo.result2, 25);
    }

    template<> template<> 
    void object::test<2>(void)
    {
        set_test_name("testMacroCommandListCommandExecute");

        data::MacroCommandTestVO vo(7);
        Notification note("MacroCommandListTest", &vo);


        std::list<ICommand*> command_list;
        command_list.push_back(new data::MacroCommandTestSub1Command());
        command_list.push_back(new data::MacroCommandTestSub2Command());

        MacroCommand command(command_list);

        command.execute((INotification&)note);

        ensure_equals( "Expecting vo.result1 == 10", vo.result1, 14);
        ensure_equals( "Expecting vo.result2 == 49", vo.result2, 49);
    }

    template<typename _Type, std::size_t _Size>
    inline std::size_t getSize(_Type(&)[_Size]) { return _Size; }

    template<> template<> 
    void object::test<3>(void)
    {
        set_test_name("testMacroCommandListCommandExecute");

        data::MacroCommandTestVO vo(8);
        Notification note("MacroCommandListTest", &vo);


        ICommand* command_array[] = {
            new data::MacroCommandTestSub1Command(),
            new data::MacroCommandTestSub2Command()
        };

        MacroCommand command(command_array, command_array + getSize(command_array));

        command.execute((INotification&)note);

        ensure_equals( "Expecting vo.result1 == 10", vo.result1, 16);
        ensure_equals( "Expecting vo.result2 == 49", vo.result2, 64);
    }
}
