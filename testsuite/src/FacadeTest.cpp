//  FacadeTest.cpp
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

#include "FacadeTestCommand.hpp"
#include "FacadeTestInheritance.hpp"

namespace data
{
    struct FacadeTest
    { };
}

namespace testgroup
{
    typedef tut::test_group<data::FacadeTest> itearator_test_t;
    typedef itearator_test_t::object object;
    itearator_test_t facade_test("FacadeTest");
}

namespace tut
{
    using namespace testgroup;

    using PureMVC::Interfaces::IFacade;
    using PureMVC::Interfaces::IProxy;
    using PureMVC::Interfaces::IMediator;
    using PureMVC::Interfaces::IAggregate;
    using PureMVC::Interfaces::IIterator;
    using PureMVC::Patterns::Facade;
    using PureMVC::Patterns::Proxy;
    using PureMVC::Patterns::Mediator;

    template<> template<> 
    void object::test<1>(void)
    {
        set_test_name("testGetInstanceAndGetMulitonKey");

        // Test Factory Method
        IFacade &facade = Facade::getInstance("FacadeTestKey1");

        ensure( "Expecting instance not null", &facade != NULL);
        // Because C++ doesn't provide operator cast 'as' 
        // so that I use dynamic_cast to make sure that facade is Facade
        ensure( "Expecting instance implements IFacade", dynamic_cast<Facade*>(&facade) != NULL);

        ensure_equals("Expecting facade.getMultitonKey() == FacadeTestKey1",
            facade.getMultitonKey(), "FacadeTestKey1");
    }

    template<> template<>
    void object::test<2>(void)
    {
        set_test_name("testRegisterCommandAndGetMultitonKeyAndSendNotification");

        // Create the Facade, register the FacadeTestCommand to 
        // handle 'FacadeTest' notifications
        IFacade &facade = Facade::getInstance("FacadeTestKey2");
        data::FacadeTestCommand facade_command;
        facade.registerCommand("FacadeTestNote", &facade_command);

        ensure_equals("Expecting facade_command.getMultitonKey()== FacadeTestKey2",
            facade_command.getMultitonKey(), "FacadeTestKey2");

        // Send notification. The Command associated with the event
        // (FacadeTestCommand) will be invoked, and will multiply 
        // the vo.input value by 2 and set the result on vo.result
        data::FacadeTestVO vo(32);
        facade.sendNotification("FacadeTestNote", &vo );

        // test assertions 
        ensure_equals("Expecting vo.result == 64", vo.result, 64);
    }

    template<> template<>
    void object::test<3>(void)
    {
        set_test_name("testRegisterAndRemoveCommandAndSendNotification");

        // Create the Facade, register the FacadeTestCommand to 
        // handle 'FacadeTest' events
        IFacade &facade = Facade::getInstance("FacadeTestKey3");
        data::FacadeTestCommand facade_command;
        facade.registerCommand("FacadeTestNote", &facade_command);
        facade.removeCommand("FacadeTestNote");

        // Send notification. The Command associated with the event
        // (FacadeTestCommand) will NOT be invoked, and will NOT multiply 
        // the vo.input value by 2 
        data::FacadeTestVO vo(32);
        facade.sendNotification("FacadeTestNote", &vo );

        // test assertions 
        ensure( "Expecting vo.result != 64", vo.result != 64 );
    }

    template<> template<>
    void object::test<4>(void)
    {
        set_test_name("testRegisterAndGetMultitionKeyAndRetrieveProxy");

        // Create the Facade, register the FacadeTestCommand to 
        // handle 'FacadeTest' events
        IFacade &facade = Facade::getInstance("FacadeTestKey4");

        Proxy proxy_local("colors");
        std::vector<std::string> data_local;
        data_local.push_back("red");
        data_local.push_back("green");
        data_local.push_back("blue");
        proxy_local.setData(&data_local);

        facade.registerProxy(&proxy_local);

        ensure_equals("Expecting proxy_local.getMultitonKey()== FacadeTestKey4",
            proxy_local.getMultitonKey(), "FacadeTestKey4");

        IProxy* proxy = NULL;
        try
        {
            proxy = &facade.retrieveProxy("colors");
        }
        catch (...)
        { }
        // test assertions
        ensure( "Expecting proxy is IProxy", dynamic_cast<Proxy*>(proxy) != NULL);

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
    void object::test<5>(void)
    {
        set_test_name("testRegisterAndRemoveProxy");

        IFacade &facade = Facade::getInstance("FacadeTestKey5");

        Proxy proxy_local("sizes");
        std::vector<std::string> data_local;
        data_local.push_back("7");
        data_local.push_back("13");
        data_local.push_back("21");
        proxy_local.setData(&data_local);

        // register a proxy, remove it, then try to retrieve it
        facade.registerProxy(&proxy_local);

        // remove the proxy
        IProxy* removedProxy= facade.removeProxy("sizes");

        // assert that we removed the appropriate proxy
        ensure_equals( "Expecting removedProxy.getProxyName() == 'sizes'",
            removedProxy->getProxyName(), "sizes");

        IProxy* proxy = NULL;
        try
        {
            // make sure we can no longer retrieve the proxy from the model
            proxy = &facade.retrieveProxy("sizes");
        }
        catch(...)
        { }
        // test assertions
        ensure("Expecting proxy is null", proxy == NULL );
    }

    template<> template<>
    void object::test<6>(void)
    {
        set_test_name("testRegisterRetrieveAndRemoveMediator");

        // register a mediator, remove it, then try to retrieve it
        IFacade &facade = Facade::getInstance("FacadeTestKey6");
        std::string str("Sprite");
        Mediator mediator_local(Mediator::NAME, &str);
        facade.registerMediator(&mediator_local);

        ensure_equals("Expecting mediator_local.getMultitonKey()== FacadeTestKey6",
            mediator_local.getMultitonKey(), "FacadeTestKey6");

        IMediator* mediator = NULL;
        try
        {
            mediator = &facade.retrieveMediator(Mediator::NAME);
        }
        catch (...)
        { }
        // retrieve the mediator
        ensure( "Expecting mediator is not null", mediator != NULL);

        // remove the mediator
        IMediator* removedMediator = facade.removeMediator(Mediator::NAME);

        // assert that we have removed the appropriate mediator
        ensure_equals("Expecting removedMediator.getMediatorName() == Mediator.NAME", 
                      removedMediator->getMediatorName(), Mediator::NAME);

        mediator= NULL;
        try
        {
            // assert that the mediator is no longer retrievable
            mediator = &facade.retrieveMediator(Mediator::NAME);
        }
        catch (...)
        { }
        ensure( "Expecting facade.retrieveMediator( Mediator.NAME ) == null )", mediator == NULL);
    }

    template<> template<>
    void object::test<7>(void)
    {
        set_test_name("testHasProxy");

        // register a mediator, remove it, then try to retrieve it
        IFacade &facade = Facade::getInstance("FacadeTestKey7");

        std::vector<std::string> data_local;
        data_local.push_back("1");
        data_local.push_back("2");
        data_local.push_back("3");
        Proxy proxy_local("hasProxyTest", &data_local);

        facade.registerProxy( &proxy_local );

        // assert that the model.hasProxy method returns true
        // for that proxy name
        ensure( "Expecting facade.hasProxy('hasProxyTest') == true", facade.hasProxy("hasProxyTest"));
    }

    template<> template<>
    void object::test<8>(void)
    {
        set_test_name("testHasMediator");

        IFacade &facade = Facade::getInstance("FacadeTestKey8");
        std::string str("Sprite");
        Mediator mediator_local("facadeHasMediatorTest", &str);

        // register a Mediator
        facade.registerMediator(&mediator_local);


        // assert that the facade.hasMediator method returns true
        // for that mediator name
        ensure( "Expecting facade.hasMediator('facadeHasMediatorTest') == true", 
                 facade.hasMediator("facadeHasMediatorTest"));

        facade.removeMediator("facadeHasMediatorTest");

        // assert that the facade.hasMediator method returns false
        // for that mediator name
        ensure("Expecting facade.hasMediator('facadeHasMediatorTest') == false", 
                facade.hasMediator("facadeHasMediatorTest") == false);
    }

    template<> template<>
    void object::test<9>(void)
    {
        set_test_name("testHasCommand");

        // register the ControllerTestCommand to handle 'hasCommandTest' notes
        IFacade &facade = Facade::getInstance("FacadeTestKey9");
        data::FacadeTestCommand facade_command;
        facade.registerCommand("facadeHasCommandTest", &facade_command);

        // test that hasCommand returns true for hasCommandTest notifications 
        ensure( "Expecting facade.hasCommand('facadeHasCommandTest') == true", 
               facade.hasCommand("facadeHasCommandTest"));

        // Remove the Command from the Controller
        facade.removeCommand("facadeHasCommandTest");

        // test that hasCommand returns false for hasCommandTest notifications 
        ensure("Expecting facade.hasCommand('facadeHasCommandTest') == false", 
              facade.hasCommand("facadeHasCommandTest") == false );
    }

    template<> template<>
    void object::test<10>(void)
    {
        set_test_name("testHasCoreAndRemoveCore");

        // assert that the Facade.hasCore method returns false first
        ensure("Expecting facade.hasCore('FacadeTestKey10') == false",
               Facade::hasCore("FacadeTestKey10") == false);

        // register a Core
        IFacade& facade = Facade::getInstance("FacadeTestKey10");

        // assert that the Facade.hasCore method returns true now that a Core is registered
        ensure("Expecting facade.hasCore('FacadeTestKey10') == true",
                Facade::hasCore("FacadeTestKey10"));

        // remove the Core
        Facade::removeCore("FacadeTestKey10");

        // assert that the Facade.hasCore method returns false now that the core has been removed.
        ensure("Expecting facade.hasCore('FacadeTestKey10') == false",
               Facade::hasCore("FacadeTestKey10") == false);
    }

    template<> template<>
    void object::test<11>(void)
    {
        set_test_name("testListCores");

        Facade::CoreNames aggregate = Facade::listCores();
        do
        {
            Facade::CoreNames::element_type::Iterator iterator = aggregate->getIterator();

            std::size_t counter = 0;
            while(iterator->moveNext())
                ++counter;
            // assert that the Facade.hasCore method returns false first
            ensure_equals("Expecting facade.listCores() == 10", counter, 10);

            // Create new facade core
            Facade::getInstance("FacadeTestKey11");

        }while (false);

        do
        {
            std::size_t counter = 0;
            Facade::CoreNames::element_type::Iterator iterator = aggregate->getIterator();
#if defined(_DEBUG) || defined(DEBUG)
            std::cout << std::endl << "List of cores:" << std::endl;
#endif
            while(iterator->moveNext())
            {
                ++counter;
#if defined(_DEBUG) || defined(DEBUG)
                std::cout <<counter << "." << iterator->getCurrent() << std::endl;;
#endif
            }

            // assert that the Facade.hasCore method returns false first
            ensure_equals("Expecting facade.listCores() == 11", counter, 11);
        }while (false);
    }

    template<> template<>
    void object::test<12>(void)
    {
        set_test_name("testFacadeInheritance");

        // get Facade
        data::FacadeTestInheritance& facade = data::FacadeTestInheritance::getInstance();

        ensure_equals("Expecting facade.initializeNotifierCalled = Called!!!", *(facade.initializeNotifierCalled), "Called!!!");

        ensure_equals("Expecting facade.initializeFacadeCalled = Called!!!", (*facade.initializeFacadeCalled), "Called!!!");
    }
}
