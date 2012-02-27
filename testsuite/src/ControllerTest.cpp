//  ControllerTest.cpp
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

#include "ControllerTestInheritance.hpp"
#include "ControllerTestCommand.hpp"
#include "ControllerTestCommand2.hpp"
#include "ControllerTestVO.hpp"

namespace data
{
    struct ControllerTest
    {
        PureMVC::FastMutex _mutex;
    };
}

namespace testgroup
{
    typedef tut::test_group<data::ControllerTest> controller_test_t;
    typedef controller_test_t::object object;
    controller_test_t controller_test("ControllerTest");
}

namespace tut
{
    using namespace testgroup;

    using PureMVC::Thread;
    using PureMVC::Interfaces::IController;
    using PureMVC::Interfaces::INotification;
    using PureMVC::Interfaces::IView;
    using PureMVC::Interfaces::IIterator;
    using PureMVC::Interfaces::IAggregate;
    using PureMVC::Core::Controller;
    using PureMVC::Core::View;
    using PureMVC::Patterns::Notification;
    using PureMVC::Patterns::Notification;
    using PureMVC::Patterns::DelegateCommand;
    using PureMVC::Patterns::createCommand;

    template<> template<>
    void object::test<1>(void)
    {
        set_test_name("testGetInstance");

        // Test Factory Method
        IController& controller = Controller::getInstance("ControllerTestKey1");

        ensure( "Expecting instance not null", &controller != NULL );
        // test assertions
        // Because C++ doesn't provide operator cast 'as' 
        // so that I use dynamic_cast to make sure that controller is Controller
        ensure( "Expecting instance implements IFacade", dynamic_cast<Controller*>(&controller) != NULL);
    }

    template<> template<>
    void object::test<2>(void)
    {
        do
        {
            PureMVC::FastMutex::ScopedLock _(_mutex);
            set_test_name("testRegisterAndExecuteCommand");
        }while (false);

        static data::ControllerTestCommand command;
        // Create the controller, register the ControllerTestCommand to handle 'ControllerTest' notes
        IController& controller = Controller::getInstance("ControllerTestKey2");
        controller.registerCommand("ControllerTest", &command);

        // Create a 'ControllerTest' note
        data::ControllerTestVO vo( 12 );
        Notification note("ControllerTest", &vo);

        // Tell the controller to execute the Command associated with the note
        // the ControllerTestCommand invoked will multiply the vo.input value
        // by 2 and set the result on vo.result
        controller.executeCommand(note);

        // test assertions 
        ensure_equals( "Expecting vo.result == 24", vo.result, 24);
    }

    template<> template<>
    void object::test<3>(void)
    {
        do
        {
            PureMVC::FastMutex::ScopedLock _(_mutex);
            set_test_name("testRegisterAndRemoveCommand");
        }while (false);

        static data::ControllerTestCommand command;
        // Create the controller, register the ControllerTestCommand to handle 'ControllerTest' notes
        IController& controller = Controller::getInstance("ControllerTestKey3");

        std::string notification_name = "ControllerRemoveTest";
        notification_name += Thread::getCurrentThreadId();
        controller.registerCommand(notification_name, &command);

        // Create a 'ControllerTest' note
        data::ControllerTestVO vo( 14 );
        Notification note(notification_name, &vo);

        // Tell the controller to execute the Command associated with the note
        // the ControllerTestCommand invoked will multiply the vo.input value
        // by 2 and set the result on vo.result
        controller.executeCommand(note);

        // test assertions 
        ensure_equals( "Expecting vo.result == 28", vo.result, 28);

        // Reset result
        vo.result = 0;

        // Remove the Command from the Controller
        controller.removeCommand(notification_name);

        // Tell the controller to execute the Command associated with the
        // note. This time, it should not be registered, and our vo result
        // will not change
        controller.executeCommand(note);

        // test assertions 
        ensure_equals("Expecting vo.result == 0", vo.result, 0);
    }

    template<> template<>
    void object::test<4>(void)
    {
        do
        {
            PureMVC::FastMutex::ScopedLock _(_mutex);
            set_test_name("testHasCommand");
        }while (false);

        static data::ControllerTestCommand command;
        // register the ControllerTestCommand to handle 'hasCommandTest' notes
        IController& controller = Controller::getInstance("ControllerTestKey4");

        std::string notification_name = "hasCommandTest";
        notification_name += Thread::getCurrentThreadId();

        controller.registerCommand(notification_name, &command);

        // test that hasCommand returns true for hasCommandTest notifications 
        ensure_equals("Expecting controller.hasCommand('hasCommandTest') == true", controller.hasCommand(notification_name), true);

        // Remove the Command from the Controller
        controller.removeCommand(notification_name);

        // test that hasCommand returns false for hasCommandTest notifications 
        ensure_equals("Expecting controller.hasCommand('hasCommandTest') == false", controller.hasCommand(notification_name), false);
    }

    template<> template<>
    void object::test<5>(void)
    {
        do
        {
            PureMVC::FastMutex::ScopedLock _(_mutex);
            set_test_name("testReregisterAndExecuteCommand");
        }while (false);

        static data::ControllerTestCommand2 command;
        // Fetch the controller, register the ControllerTestCommand2 to handle 'ControllerTest2' notes
        IController& controller = Controller::getInstance("ControllerTestKey5");

        std::string notification_name = "ControllerTest2";
        notification_name += Thread::getCurrentThreadId();

        controller.registerCommand(notification_name, &command);

        // Remove the Command from the Controller
        controller.removeCommand(notification_name);

        // Re-register the Command with the Controller
        controller.registerCommand(notification_name, &command);

        // Create a 'ControllerTest2' note
        data::ControllerTestVO vo(15);
        Notification note(notification_name, &vo);

        // retrieve a reference to the View from the same core.
        IView& view = View::getInstance("ControllerTestKey5");

        // send the Notification
        view.notifyObservers(note);

        // test assertions 
        // if the command is executed once the value will be 30
        ensure_equals( "Expecting vo.result == 30", vo.result, 30);

        // Prove that accumulation works in the VO by sending the notification again
        view.notifyObservers(note);

        // if the command is executed twice the value will be 60
        ensure_equals( "Expecting vo.result == 60", vo.result, 60);
    }


    template<> template<>
    void object::test<6>(void)
    {
        set_test_name("testControllerInheritance");

        // get Facade
        data::ControllerTestInheritance& controller = data::ControllerTestInheritance::getInstance();

        ensure_equals("Expecting controller.initializeControllerCalled = Called!!!", *(controller.initializeControllerCalled), "Called!!!");

    }

    template<> template<>
    void object::test<7>(void)
    {
        set_test_name("testListNotificationNames");

        data::ControllerTestCommand command[3];
        data::ControllerTestCommand2 command2[3];

        // Fetch the controller, register the ControllerTestCommand2 to handle 'ControllerTest2' notes
        IController& controller = Controller::getInstance("ControllerTestKey6");

        IController::NotificationNames aggregate = controller.listNotificationNames();
        do
        {
            IController::NotificationNames::element_type::Iterator iterator = aggregate->getIterator();
            std::size_t counter = 0;
            // Move next to counter item
            while(iterator->moveNext())
                ++counter;

            // test assertions 
            // Make sure that counter is 0
            ensure_equals( "Expecting counter == 0", counter, 0);

            controller.registerCommand("ControllerTestKey6_1", &command[0]);
            controller.registerCommand("ControllerTestKey6_2", &command[1]);
            controller.registerCommand("ControllerTestKey6_3", &command[2]);
            controller.registerCommand("ControllerTestKey6_4", &command2[0]);
            controller.registerCommand("ControllerTestKey6_5", &command2[1]);
            controller.registerCommand("ControllerTestKey6_6", &command2[2]);
        }while (false);

        do
        {
            IController::NotificationNames::element_type::Iterator iterator = aggregate->getIterator();

            bool bool_exception = false;
            try
            {
                iterator->getCurrent();
            }
            catch (std::exception const&)
            {
                bool_exception = true;
            }

            ensure("Expecting iterator->getCurrent() throw exception", bool_exception);

            std::size_t counter = 0;
            // Move next to counter item
            while(iterator->moveNext())
                ++counter;

            // test assertions 
            // Make sure that counter is 6
            ensure_equals( "Expecting counter == 6", counter, 6);

            controller.removeCommand("ControllerTestKey6_1");
            controller.removeCommand("ControllerTestKey6_3");
            controller.removeCommand("ControllerTestKey6_6");
        }while (false);

        do
        {
            IController::NotificationNames::element_type::Iterator iterator = aggregate->getIterator();

            std::size_t counter = 0;
            // Move next to counter item
            while(iterator->moveNext())
                ++counter;

            // test assertions 
            // Make sure that counter is 3
            ensure_equals( "Expecting counter == 3", counter,3);

            // Reset again iterator
            iterator->reset();
            // Move next to counter item
            ensure("Expecting iterator->moveNext() == true", iterator->moveNext());
#if !defined(PUREMVC_USES_TR1)
            ensure_equals("Expecting iterator->getCurrent() == ControllerTestKey6_2", iterator->getCurrent(), "ControllerTestKey6_2");
#endif
            ensure("Expecting iterator->moveNext() == true", iterator->moveNext());
#if !defined(PUREMVC_USES_TR1)
            ensure_equals( "Expecting iterator->getCurrent() == ControllerTestKey6_4", iterator->getCurrent(), "ControllerTestKey6_4");
#endif
            ensure("Expecting iterator->moveNext() == true", iterator->moveNext());
#if !defined(PUREMVC_USES_TR1)
            ensure_equals( "Expecting iterator->getCurrent() == ControllerTestKey6_5", iterator->getCurrent(), "ControllerTestKey6_5");
#endif
            ensure("Expecting iterator->moveNext() == false", iterator->moveNext() == false);
        
            bool bool_exception = false;

            try
            {
                iterator->getCurrent();
            }
            catch (std::exception const&)
            {
                bool_exception = true;
            }
            ensure("Expecting iterator->getCurrent() throw exception", bool_exception);
        }while (false);
    }

    template<> template<>
    void object::test<8>(void)
    {
        set_test_name("testMultiThreadedOperations");

        struct Action {
            static void execute(INotification const& notification) {

                void** data = (void**)notification.getBody();
                tut::test_group<data::ControllerTest>::object& test = *(tut::test_group<data::ControllerTest>::object*)data[0];
                std::size_t& count = *(std::size_t*)data[1];
                
                static const std::size_t ThreadIterationCount = 10000;

                for (std::size_t i = 0; i < ThreadIterationCount; ++i)
                {
                    // All we need to dois test the registration and removal of commands.
                    test.test<2>();
                    test.test<3>();
                    test.test<4>();
                    test.test<5>();
                }
                --count;
            }
        };

        typedef std::list<Thread*> thread_list_t;
        std::size_t count = 20;
        thread_list_t threads;

        for(std::size_t i = 0; i < count; ++i)
            threads.push_back(new Thread(createCommand(Action::execute)));

        void* data[] = { this, &count };

        Notification notification("tut::test_group<data::ControllerTest>::object,std::size_t", data);
        
        thread_list_t::iterator iter = threads.begin();
        for(; iter != threads.end(); ++iter)
            (*iter)->start(notification);


        while (true)
        {
            if (count <= 0) break;
            Thread::sleep(100);
        }

        iter = threads.begin();
        while(iter != threads.end())
        {
            (*iter)->join();
            delete *iter;
            threads.erase(iter);
            iter = threads.begin();
        }
    }
}
