//  PureMVCThreadTest.cpp
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
    struct PureMVCThreadTest
    { };
}

namespace testgroup
{
    typedef tut::test_group<data::PureMVCThreadTest> puremvc_thread_test_t;
    typedef puremvc_thread_test_t::object object;
    puremvc_thread_test_t puremvc_thread_test("PureMVCThreadTest");
}

namespace tut
{
    using namespace testgroup;

    using PureMVC::Thread;
    using PureMVC::Interfaces::INotification;
    using PureMVC::Patterns::Notification;
    using PureMVC::Patterns::DelegateCommand;
    using PureMVC::Patterns::createCommand;

    template<> template<> 
    void puremvc_thread_test_t::object::test<1>(void)
    {
        set_test_name("testThreadInitiate");
        try
        {
            Thread thread(NULL);
            ensure("Expecting throw exception", false);
        }
        catch (std::runtime_error const&)
        {
        	ensure("Expecting throw exception", true);
        }

        struct Action {
            static void execute(INotification const&) { }
        };

        Thread thread(createCommand(Action::execute));

        try
        {
            thread.start(NULL);
            ensure("Expecting throw exception", false);
        }
        catch (std::runtime_error const&)
        {
        	ensure("Expecting throw exception", true);
        }
    }

    template<> template<> 
    void puremvc_thread_test_t::object::test<2>(void)
    {
        set_test_name("testStartAndJoinThread");
        struct Action {
            static void execute(INotification const& notification) {
                int* data = (int*)notification.getBody();
                (*data) *= 3;
            }
        };
 
        int value = 10;
        Thread thread(createCommand(Action::execute));
        thread.start(new Notification("", &value));
        thread.join();
        // Test if thread run successfully
        ensure_equals("Expecting value == 30", value, 30);
    }

    template<> template<> 
    void puremvc_thread_test_t::object::test<3>(void)
    {
        set_test_name("testStartAndKillThread");
        struct Action {
            static void execute(INotification const& notification) {
                int* data = (int*)notification.getBody();
                // Wait
                PureMVC::Thread::sleep(1000);
                (*data) *= 5;
            }
        };
        int value = 10;
        Notification notification("", &value);
        Thread thread(createCommand(Action::execute));
        thread.start(notification);
        // Test if thread is sleep
        ensure("Expecting value != 50", value != 50);
        try
        {
            // Start again.
            thread.start(notification);
            ensure("Expecting throw exception", false);
        }
        catch (std::exception const&)
        {
            ensure("Expecting throw exception", true);
        }
        // Waiting...
        thread.join();
        // Test if thread run successfully
        ensure_equals("Expecting value == 50", value, 50);
    }

    template<> template<> 
    void puremvc_thread_test_t::object::test<4>(void)
    {
        set_test_name("testStartSleepAndJoinThread");
        struct Action {
            static void execute(INotification const& notification) {
                int* data = (int*)notification.getBody();
                // Wait
                PureMVC::Thread::sleep(1000);
                (*data) *= 4;
            }
        };
        
        int value = 10;

        Thread thread(createCommand(Action::execute));
        ensure("Expecting thread thread.isRunning() == false", thread.isRunning() == false);
        thread.start(new Notification("", &value));
        ensure("Expecting thread thread.isRunning() == true", thread.isRunning() == true);
        // Test if thread is sleep
        ensure("Expecting value != 40", value != 40);
        thread.join();
        ensure("Expecting thread thread.isRunning() == false", thread.isRunning() == false);
        // Test if thread run successfully
        ensure_equals("Expecting value == 40", value, 40);
    }

    template<> template<> 
    void puremvc_thread_test_t::object::test<5>(void)
    {
        set_test_name("testStartThreadAndTryJoinAndJoinTimeOut");
        struct Action {
            static void execute(INotification const& notification) {
                int* data = (int*)notification.getBody();
                // Wait
                PureMVC::Thread::sleep(1000);
                (*data) *= 2;
            }
        };
        DelegateCommand<void(*)(INotification const&)> command(Action::execute);
        
        int value = 1;

        Notification notification("", &value);
        Thread thread(command);

        bool ret = thread.tryJoin(100);
        ensure("Expecting try join return true", ret == true);


        thread.start(notification);
        ret = thread.tryJoin(100);
        ensure("Expecting try join return false", ret == false);

        try
        {
            thread.start(notification);
            ensure("Expecting throw exception", false);
        }
        catch (std::exception const&)
        {
            ensure("Expecting throw exception", true);
            ret = thread.tryJoin(2000);
            ensure("Expecting try join return true", ret == true);
        }

        try
        {
            thread.start(notification);
            thread.join(100);
            ensure("Expecting throw exception", false);
        }
        catch (std::exception const&)
        {
            ensure("Expecting throw exception", true);
        }

        try
        {
            thread.start(notification);
            ensure("Expecting throw exception", false);
        }
        catch (std::exception const&)
        {
            ensure("Expecting throw exception", true);
            try
            {
                thread.join(2000);
                ensure("Expecting no throw exception", true);
            }
            catch (std::runtime_error const&)
            {
                ensure("Expecting no throw exception", false);
            }
        }

        ensure_equals("Expecting value == 4", value, 4);
    }
}
