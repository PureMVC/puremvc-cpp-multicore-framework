//  ProxyTest.cpp
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
    struct ProxyTest
    { };
}

namespace testgroup
{
    typedef tut::test_group<data::ProxyTest> proxy_test_t;
    typedef proxy_test_t::object object;
    proxy_test_t proxy_test("ProxyTest");
}

namespace tut
{
    using namespace testgroup;
    using PureMVC::Patterns::Proxy;

    template<> template<> 
    void object::test<1>(void)
    {
        set_test_name("testNameAccessor");

        Proxy proxy("TestProxy");

        ensure_equals( "Expecting proxy.getProxyName() == 'TestProxy'", proxy.getProxyName(), "TestProxy" );
    }

    template<> template<> 
    void object::test<2>(void)
    {
        set_test_name("testDataAccessors");

        Proxy proxy("colors");
        std::vector<std::string>* data = new std::vector<std::string>();
        data->push_back("red");
        data->push_back("green");
        data->push_back("blue");
        proxy.setData(data);

        data = (std::vector<std::string>*)proxy.getData();

        ensure_equals( "Expecting data.length == 3", data->size(), 3 );
        ensure_equals( "Expecting data[0] == 'red'", (*data)[0], "red" );
        ensure_equals( "Expecting data[1] == 'green'", (*data)[1], "green" );
        ensure_equals( "Expecting data[2] == 'blue'", (*data)[2], "blue" );
        delete data;
        proxy.setData(NULL);
    }

    template<> template<> 
    void object::test<4>(void)
    {
        set_test_name("testConstructor");
   
        std::vector<std::string>* data = new std::vector<std::string>();
        data->push_back("red");
        data->push_back("green");
        data->push_back("blue");
        Proxy* proxy = new Proxy("colors", data);

        data = (std::vector<std::string>*)proxy->getData();

        ensure("Expecting proxy not null", proxy != NULL);
        ensure_equals( "Expecting proxy.getProxyName() == 'colors'", proxy->getProxyName(), "colors");
        ensure_equals( "Expecting data.length == 3", data->size(), 3 );
        ensure_equals( "Expecting data[0] == 'red'", (*data)[0], "red" );
        ensure_equals( "Expecting data[1] == 'green'", (*data)[1], "green" );
        ensure_equals( "Expecting data[2] == 'blue'", (*data)[2], "blue" );

        delete proxy;
        delete data;
    }
}
