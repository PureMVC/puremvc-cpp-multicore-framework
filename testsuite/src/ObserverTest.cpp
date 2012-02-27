//  ObserverTest.cpp
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
    using PureMVC::Interfaces::INotification;

    struct IObserverTest
    {
        virtual void observerTestMethod(INotification const& note) = 0;
    };
    struct ObserverTest : virtual IObserverTest
    {
        int observerTestVar;
        // observerTestMethod must be virtual!!! 
        virtual void observerTestMethod(INotification const& note)
        {
            observerTestVar = *(int*)note.getBody();
        }
    };
}

namespace testgroup
{
    typedef tut::test_group<data::ObserverTest> observer_test_t;
    typedef observer_test_t::object object ;
    observer_test_t observer_test("ObserverTest");
}

namespace tut
{
    using namespace testgroup;

    using PureMVC::Patterns::Observer;
    using PureMVC::Patterns::Notification;
    using PureMVC::Interfaces::INotification;
    using PureMVC::Interfaces::IObserver;
    using PureMVC::Patterns::createObserver;

    template<> template<> 
    void object::test<1>(void)
    {
        set_test_name("testObserverConstructor");

        // Create observer passing in notification method and context
        IObserver* observer = createObserver(&data::ObserverTest::observerTestMethod, this);

        // create a test note, setting a body value and notify 
        // the observer with it. since the observer is this class 
        // and the notification method is observerTestMethod,
        // successful notification will result in our local 
        // observerTestVar being set to the value we pass in 
        // on the note body.
        int value = 5;
        Notification note("ObserverTestNote", &value);
        observer->notifyObserver(note);

        // test assertions
        ensure_equals( "Expecting observerTestVar = 5", observerTestVar, 5);

        delete observer;
    }

    template<> template<> 
    void object::test<3>(void)
    {
        set_test_name("testObserverCompareNotifyContext");

        IObserver* observer = createObserver(&data::ObserverTest::observerTestMethod, this);
        void* negTestObj = new std::string();

        // test assertions
        ensure_equals( "Expecting observer.compareNotifyContext(negTestObj) == false", observer->compareNotifyContext(negTestObj),false );
        ensure_equals( "Expecting observer.compareNotifyContext(this) == true", observer->compareNotifyContext(this), true );
        delete observer;
        delete (std::string*)negTestObj;
    }
}
