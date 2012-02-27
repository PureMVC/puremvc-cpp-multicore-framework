//  ModelTest.cpp
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

#include "ModelTestProxy.hpp"
#include "ModelTestInheritance.hpp"

namespace data
{
    struct ModelTest
    {
        PureMVC::FastMutex _mutex;
    };
}

namespace testgroup
{
    typedef tut::test_group<data::ModelTest> model_test_t;
    typedef model_test_t::object object;
    model_test_t model_test("ModelTest");
}

namespace tut
{
    using namespace testgroup;

    using PureMVC::Thread;
    using PureMVC::Interfaces::IModel;
    using PureMVC::Interfaces::IProxy;
    using PureMVC::Interfaces::IIterator;
    using PureMVC::Interfaces::IAggregate;
    using PureMVC::Interfaces::INotification;
    using PureMVC::Core::Model;
    using PureMVC::Patterns::Proxy;
    using PureMVC::Patterns::Notification;
    using PureMVC::Patterns::DelegateCommand;
    using PureMVC::Patterns::createCommand;

    template<> template<> 
    void object::test<1>(void)
    {
        set_test_name("testGetInstance");
        // Test Factory Method
        IModel& model = Model::getInstance("ModelTestKey1");

        // test assertions
        ensure("Expecting instance not null", &model != NULL );
        // Because C++ doesn't provide operator cast 'as' 
        // so that I use dynamic_cast to make sure that mode is Modle
        ensure( "Expecting instance implements IModel",  dynamic_cast<Model*>(&model) != NULL);
    }

    template<> template<> 
    void object::test<2>(void)
    {
        do
        {
            PureMVC::FastMutex::ScopedLock _(_mutex);
            set_test_name("testRegisterAndRetrieveProxy");
        }while (false);

        // register a proxy and retrieve it.
        IModel& model = Model::getInstance("ModelTestKey2");

        std::string name("colors");
        name += Thread::getCurrentThreadId();

        Proxy proxy_local(name);
        std::vector<std::string> data_local;
        data_local.push_back("red");
        data_local.push_back("green");
        data_local.push_back("blue");
        proxy_local.setData(&data_local);

        model.registerProxy(&proxy_local);

        IProxy* proxy = NULL;
        try
        {
            proxy = &model.retrieveProxy(name);
        }
        catch(...)
        { }
        // retrieve data from proxy
        std::vector<std::string>* data = (std::vector<std::string>*)proxy->getData();

        // test assertions
        ensure( "Expecting data not null", data != NULL);
        ensure_equals( "Expecting data is Array", typeid(data).name(), typeid(std::vector<std::string>*).name() );
        ensure_equals("Expecting data.length == 3", data->size(), 3);
        ensure_equals("Expecting data[0] == 'red'", (*data)[0], "red");
        ensure_equals("Expecting data[1] == 'green'", (*data)[1], "green");
        ensure_equals("Expecting data[2] == 'blue'", (*data)[2], "blue");
    }

    template<> template<> 
    void object::test<3>(void)
    {
        do
        {
            PureMVC::FastMutex::ScopedLock _(_mutex);
            set_test_name("testRegisterAndRemoveProxy");
        }while (false);

        // register a proxy, remove it, then try to retrieve it
        IModel& model = Model::getInstance("ModelTestKey3");

        std::string proxy_name = "sizes";
        proxy_name += Thread::getCurrentThreadId();

        Proxy proxy_local(proxy_name);
        std::vector<std::string> data_local;
        data_local.push_back("7");
        data_local.push_back("13");
        data_local.push_back("21");
        proxy_local.setData(&data_local);

        // register a proxy, remove it, then try to retrieve it
        model.registerProxy(&proxy_local);

        // remove the proxy
        IProxy* removedProxy= model.removeProxy(proxy_name);

        // assert that we removed the appropriate proxy
        ensure_equals("Expecting removedProxy.getProxyName() == 'sizes'", 
                      removedProxy->getProxyName(), proxy_name);

        IProxy* proxy = NULL;
        try
        {
            // make sure we can no longer retrieve the proxy from the model
            proxy = &model.retrieveProxy(proxy_name);
        }
        catch(...)
        { }
        // test assertions
        ensure("Expecting proxy is null", proxy == NULL );
    }

    template<> template<> 
    void object::test<4>(void)
    {
        do
        {
            PureMVC::FastMutex::ScopedLock _(_mutex);
            set_test_name("testHasProxy");  
        }while (false);

        // register a proxy
        IModel& model = Model::getInstance("ModelTestKey4");

        std::string proxy_name = "aces";
        proxy_name += Thread::getCurrentThreadId();

        Proxy proxy_local(proxy_name);
        std::vector<std::string> data_local;
        data_local.push_back("clubs");
        data_local.push_back("spades");
        data_local.push_back("hearts");
        data_local.push_back("diamonds");
        proxy_local.setData(&data_local);

        model.registerProxy(&proxy_local);

        // assert that the model.hasProxy method returns true
        // for that proxy name
        ensure_equals("Expecting model.hasProxy('aces') == true", 
                      model.hasProxy(proxy_name), true);

        // remove the proxy
        model.removeProxy(proxy_name);

        // assert that the model.hasProxy method returns false
        // for that proxy name
        ensure_equals("Expecting model.hasProxy('aces') == false", 
                      model.hasProxy(proxy_name), false);
    }

    template<> template<> 
    void object::test<5>(void)
    {
        set_test_name("testOnRegisterAndOnRemove");

        // Get a Multiton View instance
       IModel& model = Model::getInstance("ModelTestKey5");

        // Create and register the test mediator
        IProxy* proxy = new data::ModelTestProxy();
        model.registerProxy(proxy);

        // assert that onRegsiter was called, and the proxy responded by setting its data accordingly
        ensure_equals("Expecting proxy.getData() == ModelTestProxy.ON_REGISTER_CALLED", 
                      proxy->getData(), data::ModelTestProxy::ON_REGISTER_CALLED );

        // Remove the component
        model.removeProxy( data::ModelTestProxy::NAME );

        // assert that onRemove was called, and the proxy responded by setting its data accordingly
        ensure_equals("Expecting proxy.getData() == ModelTestProxy.ON_REMOVE_CALLED", 
                      proxy->getData(), data::ModelTestProxy::ON_REMOVE_CALLED);
    }

    template<> template<>
    void object::test<6>(void)
    {
        set_test_name("testModelInheritance");

        // get Facade
        data::ModelTestInheritance& model = data::ModelTestInheritance::getInstance();

        ensure_equals("Expecting model.initializeModelCalled = Called!!!", *(model.initializeModelCalled), "Called!!!");

    }

    template<> template<>
    void object::test<7>(void)
    {
        set_test_name("testListProxyNames");

        data::ModelTestProxy proxy[3];

        // Fetch the model
        IModel& model = Model::getInstance("ModelTestKey6");

        IModel::ProxyNames aggregate = model.listProxyNames();

        do
        {
            IModel::ProxyNames::element_type::Iterator iterator = aggregate->getIterator();
            std::size_t counter = 0;
            // Move next to counter item
            while(iterator->moveNext())
                ++counter;

            // test assertions 
            // Make sure that counter is 0
            ensure_equals( "Expecting counter == 0", counter, 0);

            model.registerProxy(&proxy[0]);
            model.registerProxy(&proxy[1]);
            model.registerProxy(&proxy[2]);
        }while (false);

        do
        {
            IModel::ProxyNames::element_type::Iterator iterator = aggregate->getIterator();

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
            ensure_equals( "Expecting counter == 1", counter, 1);

            model.removeProxy(data::ModelTestProxy::NAME);
            model.removeProxy(data::ModelTestProxy::NAME);
            model.removeProxy(data::ModelTestProxy::NAME);
        }while (false);

        do
        {
            IModel::ProxyNames::element_type::Iterator iterator = aggregate->getIterator();

            std::size_t counter = 0;
            // Move next to counter item
            while(iterator->moveNext())
                ++counter;

            // test assertions 
            // Make sure that counter is 3
            ensure_equals( "Expecting counter == 0", counter,0);

            // Reset again iterator
            iterator->reset();
            // Move next to counter item
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
                tut::test_group<data::ModelTest>::object& test = *(tut::test_group<data::ModelTest>::object*)data[0];
                std::size_t& count = *(std::size_t*)data[1];
                
                static const std::size_t ThreadIterationCount = 10000;

                for (std::size_t i = 0; i < ThreadIterationCount; ++i)
                {
                    // All we need to do is test the registration and removal of proxies.
                    test.test<2>();
                    test.test<3>();
                    test.test<4>();
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
