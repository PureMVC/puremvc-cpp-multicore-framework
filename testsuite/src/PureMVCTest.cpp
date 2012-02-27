#include <tut/tut.hpp>
#include <tut_reporter.h>
#include <pure_mvc.h>
#include <iostream>
#include "SimpleCommandTestVO.hpp"
#include "PureMVCTestCommand.hpp"
#include "PureMVCTestCommand2.hpp"
#include "PureMVCTestCommand3.hpp"
#include "PureMVCTestCommand4.hpp"

namespace data
{
    struct PureMVCTest
    { };
}

namespace testgroup
{
    typedef tut::test_group<data::PureMVCTest> pure_mvc_test_t;
    typedef pure_mvc_test_t::object object;
    pure_mvc_test_t pure_mvc_test("_PureMVCTest");
}

namespace tut
{
    using namespace testgroup;
    using namespace data;
    using namespace PureMVC;
    using namespace PureMVC::Core;
    using namespace PureMVC::Interfaces;
    using namespace PureMVC::Patterns;

    template<> template<>
    void object::test<1>(void)
    { 
        set_test_name("testGetFacadeNames");

        std::auto_ptr<IAggregate<std::string> > names = getFacadeKeys();
        std::auto_ptr<IIterator<std::string> > iterator = names->getIterator();
        std::size_t count = 0;

#if defined(_DEBUG) || defined(DEBUG)
        std::cout << std::endl <<"The list name of Facade: " << std::endl;
#endif
        while(iterator->moveNext()) {
            ++count;
#if defined(_DEBUG) || defined(DEBUG)
            std::cout <<count << ". " <<iterator->getCurrent() << std::endl;
#endif
        }

        ensure_equals( "Expecting number of Facade equal 10 ", count, 10);
    }

    template<> template<>
    void object::test<2>(void)
    { 
        set_test_name("testGetControllerNames");

        std::auto_ptr<IAggregate<std::string> > names = PureMVC::getControllerKeys();
        std::auto_ptr<IIterator<std::string> > iterator = names->getIterator();
        std::size_t count = 0;

#if defined(_DEBUG) || defined(DEBUG)
        std::cout << std::endl <<"The list name of Controller: " << std::endl;
#endif
        while(iterator->moveNext()) {
            ++count;
#if defined(_DEBUG) || defined(DEBUG)
            std::cout <<count << ". " <<iterator->getCurrent() << std::endl;
#endif
        }

        ensure_equals( "Expecting number of Controller equal 17 ", count, 17);
    }

    template<> template<>
    void object::test<3>(void)
    { 
        set_test_name("testGetModelNames");

        std::auto_ptr<IAggregate<std::string> > names = PureMVC::getModelKeys();
        std::auto_ptr<IIterator<std::string> > iterator = names->getIterator();
        std::size_t count = 0;

#if defined(_DEBUG) || defined(DEBUG)
        std::cout << std::endl <<"The list name of Model: " << std::endl;
#endif
        while(iterator->moveNext()) {
            ++count;
#if defined(_DEBUG) || defined(DEBUG)
            std::cout <<count << ". " <<iterator->getCurrent() << std::endl;
#endif
        }

        ensure_equals( "Expecting number of Model equal 17 ", count, 17);
    }

    template<> template<>
    void object::test<4>(void)
    { 
        set_test_name("testGetViewNames");

        std::auto_ptr<IAggregate<std::string> > names = PureMVC::getViewKeys();
        std::auto_ptr<IIterator<std::string> > iterator = names->getIterator();
        std::size_t count = 0;

#if defined(_DEBUG) || defined(DEBUG)
        std::cout << std::endl <<"The list name of View: " << std::endl;
#endif
        while(iterator->moveNext()) {
            ++count;
#if defined(_DEBUG) || defined(DEBUG)
            std::cout <<count << ". " <<iterator->getCurrent() << std::endl;
#endif
        }

        ensure_equals( "Expecting number of View equal 30 ", count, 30);
    }

    template<> template<>
    void object::test<5>(void)
    { 
        set_test_name("testRemoveFacade");

        bool exist = false;

        Facade::getInstance("testRemoveFacade");

        std::auto_ptr<IAggregate<std::string> > names = getFacadeKeys();
        std::auto_ptr<IIterator<std::string> > iterator = names->getIterator();

        while(iterator->moveNext())
            if (iterator->getCurrent() == "testRemoveFacade")
            {
                exist = true;
                break;
            }

        ensure("Expecting Facade testRemoveFacade is existed!", exist);

        removeFacade("testRemoveFacade");

        names = getFacadeKeys();
        iterator = names->getIterator();

        exist = false;

        while(iterator->moveNext())
            if (iterator->getCurrent() == "testRemoveFacade")
            {
                exist = true;
                break;
            }

        ensure("Expecting Facade testRemoveFacade is removed!", !exist);
    }

    template<> template<>
    void object::test<6>(void)
    { 
        set_test_name("testRemoveController");

        bool exist = false;

        Controller::getInstance("testRemoveController");

        std::auto_ptr<IAggregate<std::string> > names = getControllerKeys();
        std::auto_ptr<IIterator<std::string> > iterator = names->getIterator();

        while(iterator->moveNext())
            if (iterator->getCurrent() == "testRemoveController")
            {
                exist = true;
                break;
            }

        ensure("Expecting Controller testRemoveController is existed!", exist);

        removeController("testRemoveController");

        names = getControllerKeys();
        iterator = names->getIterator();

        exist = false;

        while(iterator->moveNext())
            if (iterator->getCurrent() == "testRemoveController")
            {
                exist = true;
                break;
            }

        ensure("Expecting Controller testRemoveController is removed!", !exist);
    }

    template<> template<>
    void object::test<7>(void)
    { 
        set_test_name("testRemoveModel");

        bool exist = false;

        Model::getInstance("testRemoveController");

        std::auto_ptr<IAggregate<std::string> > names = getModelKeys();
        std::auto_ptr<IIterator<std::string> > iterator = names->getIterator();

        while(iterator->moveNext())
            if (iterator->getCurrent() == "testRemoveController")
            {
                exist = true;
                break;
            }

        ensure("Expecting Model testRemoveController is existed!", exist);

        removeModel("testRemoveController");

        names = getModelKeys();
        iterator = names->getIterator();

        exist = false;

        while(iterator->moveNext())
            if (iterator->getCurrent() == "testRemoveController")
            {
                exist = true;
                break;
            }

        ensure("Expecting Model testRemoveController is removed!", !exist);
    }

    template<> template<>
    void object::test<8>(void)
    { 
        set_test_name("testRemoveView");

        bool exist = false;

        View::getInstance("testRemoveController");

        std::auto_ptr<IAggregate<std::string> > names = getViewKeys();
        std::auto_ptr<IIterator<std::string> > iterator = names->getIterator();

        while(iterator->moveNext())
            if (iterator->getCurrent() == "testRemoveController")
            {
                exist = true;
                break;
            }

        ensure("Expecting View testRemoveController is existed!", exist);

        removeView("testRemoveController");

        names = getModelKeys();
        iterator = names->getIterator();

        exist = false;

        while(iterator->moveNext())
            if (iterator->getCurrent() == "testRemoveController")
            {
                exist = true;
                break;
            }

        ensure("Expecting View testRemoveController is removed!", !exist);
    }


    template<> template<>
    void object::test<9>(void)
    {
        set_test_name("testBroadcastNotification");
        Facade::getInstance("testBroadcastNotification_1").registerCommand("calculateValue", new PureMVCTestCommand);
        Facade::getInstance("testBroadcastNotification_2").registerCommand("calculateValue", new PureMVCTestCommand2);
        Facade::getInstance("testBroadcastNotification_3").registerCommand("calculateValue", new PureMVCTestCommand3);
        Facade::getInstance("testBroadcastNotification_4").registerCommand("calculateValue", new PureMVCTestCommand4);
        int value = 5;
        broadcastNotification("calculateValue", &value);
        removeFacade("testBroadcastNotification_1");
        removeFacade("testBroadcastNotification_2");
        removeFacade("testBroadcastNotification_3");
        removeFacade("testBroadcastNotification_4");
        ensure_equals( "Expecting value == 600", value, 600 );
    }
}
