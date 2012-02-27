//  ViewTest.cpp
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

#include "ViewTest.hpp"
#include "ViewTestNote.hpp"
#include "ViewTestInheritance.hpp"
#include "ViewTestMediator.hpp"
#include "ViewTestMediator2.hpp"
#include "ViewTestMediator3.hpp"
#include "ViewTestMediator4.hpp"
#include "ViewTestMediator5.hpp"
#include "ViewTestMediator6.hpp"

namespace data
{
    char const* const ViewTest::NOTE1 = "Notification1";
    char const* const ViewTest::NOTE2 = "Notification2";
    char const* const ViewTest::NOTE3 = "Notification3";
    char const* const ViewTest::NOTE4 = "Notification4";
    char const* const ViewTest::NOTE5 = "Notification5";
    char const* const ViewTest::NOTE6 = "Notification6";

    using PureMVC::Thread;
    using PureMVC::Interfaces::INotification;

    ViewTest::ViewTest(void)
        :onRegisterCalled(false)
        ,onRemoveCalled(false)
        ,counter(0)
    { }

    void ViewTest::viewTestMethod(INotification const& notification)
    {
        // set the local viewTestVar to the number on the event payload
        std::string name = Thread::getCurrentThreadId();

        PureMVC::Mutex::ScopedLock _(viewTestVarsLock);

        viewTestVars.erase(name);
        viewTestVars.insert(std::make_pair(name, *(int*)notification.getBody()));
    }
}

namespace testgroup
{
    typedef tut::test_group<data::ViewTest> view_test_t;
    typedef view_test_t::object object;
    view_test_t view_test("ViewTest");
}

namespace tut
{
    using namespace testgroup;

    using PureMVC::Thread;
    using PureMVC::Interfaces::IView;
    using PureMVC::Interfaces::INotification;
    using PureMVC::Interfaces::IObserver;
    using PureMVC::Interfaces::IMediator;
    using PureMVC::Interfaces::IIterator;
    using PureMVC::Interfaces::IAggregate;
    using PureMVC::Patterns::Mediator;
    using PureMVC::Patterns::Notification;
    using PureMVC::Patterns::Observer;
    using PureMVC::Patterns::Notification;
    using PureMVC::Patterns::Notification;
    using PureMVC::Patterns::DelegateCommand;
    using PureMVC::Patterns::createCommand;
    using PureMVC::Patterns::createObserver;
    using PureMVC::Core::View;

    template<> template<>
    void object::test<1>(void)
    {
        set_test_name("testGetInstance");
        // Test Factory Method
        IView& model = View::getInstance("ViewTestKey1");

        // test assertions
        ensure("Expecting instance not null", &model != NULL );
        // Because C++ doesn't provide operator cast 'as' 
        // so that I use dynamic_cast to make sure that mode is Modle
        ensure( "Expecting instance implements IModel",  dynamic_cast<View*>(&model) != NULL);
    }

    template<> template<>
    void object::test<2>(void)
    {
        do
        {
            PureMVC::Mutex::ScopedLock _(viewTestVarsLock);
            set_test_name("testRegisterAndNotifyObserver");
        } while(false);

        // Get the Multiton View instance
        IView& view = View::getInstance("ViewTestKey2");

        // Create observer, passing in notification method and context
        IObserver* observer = createObserver(&data::ViewTest::viewTestMethod, this );

        std::string name = Thread::getCurrentThreadId();

        do
        {
            PureMVC::Mutex::ScopedLock _(viewTestVarsLock);
            viewTestVars.erase(name);
        }while (false);

        std::string temp = data::ViewTestNote::NAME;
        temp += name;
        // Register Observer's interest in a particulate Notification with the View 
        view.registerObserver(temp, observer);

        // Create a ViewTestNote, setting 
        // a body value, and tell the View to notify 
        // Observers. Since the Observer is this class 
        // and the notification method is viewTestMethod,
        // successful notification will result in our local 
        // viewTestVar being set to the value we pass in 
        // on the note body.
        int value = 10;
        INotification* note = data::ViewTestNote::create(temp, &value);
        view.notifyObservers(*note);

        do
        {
            PureMVC::Mutex::ScopedLock _(viewTestVarsLock);
            // test assertions
            ensure_equals("Expecting viewTestVar = 10", viewTestVars[name], 10);
        }while (false);

        view.removeObserver(temp, this);

        delete note;
    }

    template<> template<>
    void object::test<3>(void)
    {
        do
        {
            PureMVC::Mutex::ScopedLock _(viewTestVarsLock);
            set_test_name("testRegisterAndRetrieveMediator");
        } while(false);

        // Get the Multiton View instance
        IView& view = View::getInstance("ViewTestKey3");

        // Create and register the test mediator
        data::ViewTestMediator viewTestMediator(Thread::getCurrentThreadId(), this);
        view.registerMediator(&viewTestMediator );

        // Retrieve the component
        IMediator* mediator = &view.retrieveMediator(Thread::getCurrentThreadId());

        // test assertions
        ensure( "Expecting comp is ViewTestMediator", dynamic_cast<data::ViewTestMediator*>(mediator) != NULL );
    }

    template<> template<>
    void object::test<4>(void)
    {
        do
        {
            PureMVC::Mutex::ScopedLock _(viewTestVarsLock);
            set_test_name("testHasMediator");
        } while(false);

        // register a Mediator
        IView& view = View::getInstance("ViewTestKey4");

        std::string name = "hasMediatorTest";
        name += Thread::getCurrentThreadId();

        // Create and register the test mediator
        Mediator mediator(name, this);
        view.registerMediator(&mediator);

        // assert that the view.hasMediator method returns true
        // for that mediator name
        ensure_equals("Expecting view.hasMediator('hasMediatorTest') == true", 
                      view.hasMediator(name), true);

        view.removeMediator(name);

        // assert that the view.hasMediator method returns false
        // for that mediator name
        ensure_equals( "Expecting view.hasMediator('hasMediatorTest') == false", 
                     view.hasMediator(name), false);
    }

    template<> template<>
    void object::test<5>(void)
    {
        do
        {
            PureMVC::Mutex::ScopedLock _(viewTestVarsLock);
            set_test_name("testRegisterAndRemoveMediator");
        } while(false);

        // Get the Multiton View instance
        IView& view = View::getInstance("ViewTestKey5");

        std::string name = "testing";
        name += Thread::getCurrentThreadId();

        // Create and register the test mediator
        Mediator mediator(name, this);
        view.registerMediator(&mediator);

        // Remove the component
        IMediator* removedMediator = view.removeMediator(name);

        // assert that we have removed the appropriate mediator
        ensure_equals("Expecting removedMediator.getMediatorName() == 'testing'", 
                      removedMediator->getMediatorName(), name);

        IMediator* temp = NULL;
        try
        {
            // make sure we can no longer retrieve the proxy from the model
            temp = &view.retrieveMediator(name);
        }
        catch(...)
        { }
        // assert that the mediator is no longer retrievable
        ensure("Expecting view.retrieveMediator( 'testing' ) == null )", 
                temp == NULL );
    }

    template<> template<>
    void object::test<6>(void)
    {
        set_test_name("testOnRegisterAndOnRemove");

        // Get the Multiton View instance
        IView& view = View::getInstance("ViewTestKey6");

        // Create and register the test mediator
        data::ViewTestMediator4 mediator(this);
        view.registerMediator(&mediator);

        // assert that onRegsiter was called, and the mediator responded by setting our boolean
        ensure("Expecting onRegisterCalled == true", onRegisterCalled);

        // Remove the component
        view.removeMediator(data::ViewTestMediator4::NAME);

        // assert that the mediator is no longer retrievable
        ensure( "Expecting onRemoveCalled == true", onRegisterCalled );
    }

    template<> template<>
    void object::test<7>(void)
    {
        set_test_name("testSuccessiveRegisterAndRemoveMediator");

        // Get the Multiton View instance
        IView& view = View::getInstance("ViewTestKey7");

        // Create and register the test mediator, 
        // but not so we have a reference to it
        data::ViewTestMediator viewTestMediator(Thread::getCurrentThreadId(), this);
        view.registerMediator(&viewTestMediator );

        IMediator *mediator = NULL;
        try
        {
            mediator = &view.retrieveMediator(Thread::getCurrentThreadId());
        }
        catch(...)
        { }
        // test that we can retrieve it
        ensure("Expecting view.retrieveMediator( ViewTestMediator.NAME ) is ViewTestMediator", 
               dynamic_cast<data::ViewTestMediator*>(mediator) != NULL);

        // Remove the Mediator
        view.removeMediator(Thread::getCurrentThreadId());

        try
        {
            mediator = &view.retrieveMediator(Thread::getCurrentThreadId());
        }
        catch(...)
        {
            mediator = NULL;
        }
        // test that retrieving it now returns null            
        ensure("Expecting view.retrieveMediator( ViewTestMediator.NAME ) == null", 
               mediator == NULL);

        mediator = view.removeMediator(Thread::getCurrentThreadId());
        // test that removing the mediator again once its gone doesn't cause crash         
        ensure("Expecting view.removeMediator( ViewTestMediator.NAME ) doesn't crash", 
               mediator == NULL);

        data::ViewTestMediator temp(Thread::getCurrentThreadId(), this);
        // Create and register another instance of the test mediator, 
        view.registerMediator(&temp);

        mediator = NULL;
        try
        {
            mediator = &view.retrieveMediator(Thread::getCurrentThreadId());
        }
        catch(...)
        { }
        ensure("Expecting view.retrieveMediator( ViewTestMediator.NAME ) is ViewTestMediator", 
               dynamic_cast<data::ViewTestMediator*>(mediator) != NULL);

        // Remove the Mediator
        view.removeMediator(Thread::getCurrentThreadId());

        try
        {
            mediator = &view.retrieveMediator(Thread::getCurrentThreadId());
        }
        catch(...)
        {
            mediator = NULL;
        }

        // test that retrieving it now returns null            
        ensure("Expecting view.retrieveMediator( ViewTestMediator.NAME ) == null", 
               mediator == NULL );
    }

    template<> template<>
    void object::test<8>(void)
    {
        set_test_name("testRemoveMediatorAndSubsequentNotify");

        // Get the Multiton View instance
        IView& view = View::getInstance("ViewTestKey8");

        // Create and register the test mediator, 
        // but not so we have a reference to it
        data::ViewTestMediator2 viewTestMediator(this);
        view.registerMediator(&viewTestMediator );

        // test that notifications work
        Notification note1(NOTE1);
        view.notifyObservers(note1);
        ensure_equals("Expecting lastNotification == NOTE1", 
                      lastNotification, NOTE1);

        Notification note2(NOTE2);
        view.notifyObservers(note2);
        ensure_equals("Expecting lastNotification == NOTE2", 
                      lastNotification, NOTE2);

        // Remove the Mediator
        view.removeMediator(data::ViewTestMediator2::NAME);

        IMediator *mediator = NULL;
        try
        {
            mediator = &view.retrieveMediator(data::ViewTestMediator2::NAME);
        }
        catch(...)
        { }
        // test that retrieving it now returns null            
        ensure("Expecting view.retrieveMediator( ViewTestMediator2.NAME ) == null", 
               mediator == NULL);

        // test that notifications no longer work
        // (ViewTestMediator2 is the one that sets lastNotification
        // on this component, and ViewTestMediator)
        lastNotification = "";

        view.notifyObservers(note1);
        ensure("Expecting lastNotification != NOTE1", 
               lastNotification != NOTE1);

        view.notifyObservers(note2);
        ensure("Expecting lastNotification != NOTE2", 
               lastNotification != NOTE2);
    }

    template<> template<>
    void object::test<9>(void)
    {
        set_test_name("testRemoveOneOfTwoMediatorsAndSubsequentNotify");

        // Get the Multiton View instance
        IView& view = View::getInstance("ViewTestKey9");

        // Create and register the test mediator, 
        // but not so we have a reference to it
        data::ViewTestMediator2 viewTestMediator2(this);
        view.registerMediator(&viewTestMediator2);
        // Create and register that responds to notifications 1 and 2

       // Create and register that responds to notification 3
        data::ViewTestMediator3 viewTestMediator3(this);
        view.registerMediator(&viewTestMediator3);
 
        // test that all notifications work
        Notification note1(NOTE1);
        view.notifyObservers(note1);
        ensure_equals("Expecting lastNotification == NOTE1",
                      lastNotification, NOTE1);

        Notification note2(NOTE2);
        view.notifyObservers(note2);
        ensure_equals("Expecting lastNotification == NOTE1",
                      lastNotification, NOTE2);

        Notification note3(NOTE3);
        view.notifyObservers(note3);
        ensure_equals("Expecting lastNotification == NOTE1",
                      lastNotification, NOTE3);

        // Remove the Mediator that responds to 1 and 2
        view.removeMediator(data::ViewTestMediator2::NAME);

        IMediator *mediator = NULL;
        try
        {
            mediator = &view.retrieveMediator(data::ViewTestMediator2::NAME);
        }
        catch(...)
        { }
        // test that retrieving it now returns null            
        ensure("Expecting view.retrieveMediator( ViewTestMediator2.NAME ) == null", 
               mediator == NULL);

        // test that notifications no longer work
        // for notifications 1 and 2, but still work for 3
        lastNotification = "";

        view.notifyObservers(note1);
        ensure("Expecting lastNotification != NOTE1", 
               lastNotification != NOTE1);

        view.notifyObservers(note2);
        ensure("Expecting lastNotification != NOTE2", 
               lastNotification != NOTE2);

        view.notifyObservers(note3);
        ensure("Expecting lastNotification == NOTE3", 
               lastNotification == NOTE3);
    }

    template<> template<>
    void object::test<10>(void)
    {
        set_test_name("testMediatorReregistration");

        // Get the Singleton View instance
        IView& view = View::getInstance("ViewTestKey10");

        // Create and register that responds to notification 5
        data::ViewTestMediator5 viewTestMediator5(this);
        view.registerMediator(&viewTestMediator5);

        // try to register another instance of that mediator (uses the same NAME constant).
        view.registerMediator(&viewTestMediator5);

        // test that the counter is only incremented once (mediator 5's response) 
        counter = 0;
        Notification note5(NOTE5);
        view.notifyObservers(note5);
        ensure_equals("Expecting counter == 1",  1, counter);

        // Remove the Mediator 
        view.removeMediator(data::ViewTestMediator5::NAME);

        IMediator *mediator = NULL;
        try
        {
            mediator = &view.retrieveMediator(data::ViewTestMediator5::NAME);
        }
        catch(...)
        { }
        // test that retrieving it now returns null            
        ensure("Expecting view.retrieveMediator( ViewTestMediator5.NAME ) == null", 
               mediator == NULL );

        // test that the counter is no longer incremented  
        counter = 0;
        view.notifyObservers(note5);
        ensure_equals( "Expecting counter == 0", 0, counter);
    }

    template<> template<>
    void object::test<11>(void)
    {
        set_test_name("testModifyObserverListDuringNotification");

        // Get the Singleton View instance
        IView& view = View::getInstance("ViewTestKey11");

        // Create and register several mediator instances that respond to notification 6 
        // by removing themselves, which will cause the observer list for that notification 
        // to change. versions prior to MultiCore Version 2.0.5 will see every other mediator
        // fails to be notified.
        data::ViewTestMediator6 viewTestMediator1("ViewTestMediator61", this);
        data::ViewTestMediator6 viewTestMediator2("ViewTestMediator62", this);
        data::ViewTestMediator6 viewTestMediator3("ViewTestMediator63", this);
        data::ViewTestMediator6 viewTestMediator4("ViewTestMediator64", this);
        data::ViewTestMediator6 viewTestMediator5("ViewTestMediator65", this);
        data::ViewTestMediator6 viewTestMediator6("ViewTestMediator66", this);
        data::ViewTestMediator6 viewTestMediator7("ViewTestMediator67", this);
        data::ViewTestMediator6 viewTestMediator8("ViewTestMediator68", this);

        view.registerMediator(&viewTestMediator1);
        view.registerMediator(&viewTestMediator2);
        view.registerMediator(&viewTestMediator3);
        view.registerMediator(&viewTestMediator4);
        view.registerMediator(&viewTestMediator5);
        view.registerMediator(&viewTestMediator6);
        view.registerMediator(&viewTestMediator7);
        view.registerMediator(&viewTestMediator8);

        // clear the counter
        counter = 0;
        // send the notification. each of the above mediators will respond by removing
        // themselves and incrementing the counter by 1. This should leave us with a
        // count of 8, since 8 mediators will respond.
        Notification note6(NOTE6);
        view.notifyObservers(note6);
        // verify the count is correct
        ensure_equals( "Expecting counter == 8", 8, counter);

        // clear the counter
        counter = 0;
        view.notifyObservers(note6);
        // verify the count is 0
        ensure_equals( "Expecting counter == 0", 0, counter);
    }


    template<> template<>
    void object::test<12>(void)
    {
        set_test_name("testViewInheritance");

        // get Facade
        data::ViewTestInheritance& view = data::ViewTestInheritance::getInstance();

        ensure_equals("Expecting view.initializeNotifierCalled = Called!!!", *(view.initializeViewCalled), "Called!!!");

    }

    template<> template<>
    void object::test<13>(void)
    {
        set_test_name("testListMediatorNames");

        data::ViewTestMediator  viewTestMediator1(Thread::getCurrentThreadId(), this);
        data::ViewTestMediator2 viewTestMediator2(this);
        data::ViewTestMediator3 viewTestMediator3(this);
        data::ViewTestMediator4 viewTestMediator4(this);
        data::ViewTestMediator5 viewTestMediator5(this);
        data::ViewTestMediator6 viewTestMediator6(data::ViewTestMediator6::NAME, this);

        // Fetch the view
        IView& view = View::getInstance("ViewTestKey12");

        IView::MediatorNames aggregate = view.listMediatorNames();

        do
        {
            IView::MediatorNames::element_type::Iterator iterator = aggregate->getIterator();
            std::size_t counter = 0;
            // Move next to counter item
            while(iterator->moveNext())
                ++counter;

            // test assertions 
            // Make sure that counter is 0
            ensure_equals( "Expecting counter == 0", counter, 0);

            view.registerMediator(&viewTestMediator1);
            view.registerMediator(&viewTestMediator2);
            view.registerMediator(&viewTestMediator3);
            view.registerMediator(&viewTestMediator4);
            view.registerMediator(&viewTestMediator5);
            view.registerMediator(&viewTestMediator6);
        }while (false);

        do
        {
            IView::MediatorNames::element_type::Iterator iterator = aggregate->getIterator();

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

            counter = 0;
            // Move next to counter item
            while(iterator->moveNext())
                ++counter;

            // test assertions 
            // Make sure that counter is 6
            ensure_equals( "Expecting counter == 6", counter, 6);

            view.removeMediator(Thread::getCurrentThreadId());
            view.removeMediator(data::ViewTestMediator3::NAME);
            view.removeMediator(data::ViewTestMediator5::NAME);
        }while(false);

        do
        {
            IView::MediatorNames::element_type::Iterator iterator = aggregate->getIterator();

            counter = 0;
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
            ensure_equals("Expecting iterator->getCurrent() == ViewTestMediator2", iterator->getCurrent(), data::ViewTestMediator2::NAME);
#endif
            ensure("Expecting iterator->moveNext() == true", iterator->moveNext());
#if !defined(PUREMVC_USES_TR1)
            ensure_equals( "Expecting iterator->getCurrent() == ViewTestMediator4", iterator->getCurrent(), data::ViewTestMediator4::NAME);
#endif
            ensure("Expecting iterator->moveNext() == true", iterator->moveNext());
#if !defined(PUREMVC_USES_TR1)
            ensure_equals( "Expecting iterator->getCurrent() == ViewTestMediator6", iterator->getCurrent(), data::ViewTestMediator6::NAME);
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
        }while(false);
    }


    template<> template<>
    void object::test<14>(void)
    {
        set_test_name("testMultiThreadedOperations");

        struct Action {
            static void execute(INotification const& notification) {

                void** data = (void**)notification.getBody();
                tut::test_group<data::ViewTest>::object& test = *(tut::test_group<data::ViewTest>::object*)data[0];
                std::size_t& count = *(std::size_t*)data[1];
                
                static const std::size_t ThreadIterationCount = 10000;

                for (std::size_t i = 0; i < ThreadIterationCount; ++i)
                {
                    // All we need to do is test the registration and removal of mediators and observers
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

        Notification notification("tut::test_group<data::ModelTest>::object,std::size_t", data);
        
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
