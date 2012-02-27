//  MediatorTest.cpp
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
    struct MediatorTest
    { };
}

namespace testgroup
{
    typedef tut::test_group<data::MediatorTest> mediator_test_t;
    typedef mediator_test_t::object object ;
    mediator_test_t mediator_test("MediatorTest");
}

namespace tut
{
    using namespace testgroup;
    
    using PureMVC::Patterns::Mediator;

    template<> template<> 
    void object::test<1>(void)
    {
        set_test_name("testNameAccessor");

        Mediator mediator;
        ensure_equals("Expecting mediator.getMediatorName() == Mediator.NAME", mediator.getMediatorName(), Mediator::NAME);
    }

    template<> template<> 
    void object::test<2>(void)
    {
        set_test_name("testViewAccessor");

        std::string *str = new std::string();
        Mediator mediator(Mediator::NAME, str);

        ensure( "Expecting mediator.getViewComponent() not null", mediator.getViewComponent() != NULL );

        delete str;
    }
}
