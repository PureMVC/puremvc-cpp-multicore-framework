//  NotificationTest.cpp
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

namespace data
{
    struct NotificationTest
    { };
}

namespace testgroup
{
    typedef tut::test_group<data::NotificationTest> notification_test_t;
    typedef notification_test_t::object object;
    notification_test_t notification_test("NotificationTest");
}

namespace tut
{
    using namespace testgroup;

    using PureMVC::Interfaces::INotification;
    using PureMVC::Patterns::Notification;

    template<> template<> 
    void object::test<1>(void)
    {
        set_test_name("testNameAccessors");

        INotification* note = new Notification("TestNote");

        // test assertions
        ensure_equals("Expecting note.getName() == 'TestNote'", note->getName(), "TestNote");

        delete note;
    }

    template<> template<> 
    void object::test<2>(void)
    {
        set_test_name("testBodyAccessors");

        int value = 5;
        INotification* note = new Notification("");

        note->setBody(&value);

        // test assertions
        ensure_equals("Expecting note.getBody()as Number == 5", *(int*)note->getBody(), 5);
        
        delete note;
    }

    template<> template<> 
    void object::test<3>(void)
    {
        set_test_name("testConstructor");

        int value = 5;
        INotification* note = new Notification("TestNote", &value, "TestNoteType");

        // test assertions
        ensure_equals( "Expecting note.getName() == 'TestNote'", note->getName(), "TestNote");
        ensure_equals( "Expecting note.getBody()as Number == 5",  *(int*)note->getBody(), 5);
        ensure_equals( "Expecting note.getType() == 'TestNoteType'", note->getType(), "TestNoteType");

        delete note;
    }

    template<> template<> 
    void object::test<4>(void)
    {
        set_test_name("testToString");

        int value[] = {1 ,3 ,5};
        INotification* note = new Notification("TestNote", value, "TestType");

        std::string ts = "Notification Name: TestNote\nBody: ";
        ts += typeid(void const*).name();
        ts += "\nType: TestType";

        std::string temp("Expecting note.testToString() == '");
        (temp += ts) += "'";
        std::string to_string = note->toString();
        //// test assertions
        ensure_equals(temp, to_string, ts );
            
        delete note;
    }
}
