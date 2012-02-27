//  ViewTestMediator4.hpp
//  PureMVC_C++ Test suite
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__VIEW_TEST_MEDIATOR4_HPP__)
#define __VIEW_TEST_MEDIATOR4_HPP__

#include <string>
#include <PureMVC/PureMVC.hpp>
#include "ViewTest.hpp"

namespace data
{
    using PureMVC::Patterns::Mediator;
    /**
     * A Mediator class used by ViewTest.
     */
    struct ViewTestMediator4 : public Mediator
    {
       /**
         * The Mediator name
         */
        static char const* const NAME;
                
        /**
         * Constructor
         */
        ViewTestMediator4(const void* view) 
            :Mediator(NAME, view)
        { }

        void onRegister(void)
        {
            viewTest()->onRegisterCalled = true;
        }

        void onRemove(void)
        {
            viewTest()->onRemoveCalled = true;
        }

        ViewTest const* viewTest(void) const
        {
            return (ViewTest*)_view_component;
        }

        ViewTest* viewTest(void)
        {
            return (ViewTest*)_view_component;
        }
    };
    char const* const ViewTestMediator4::NAME = "ViewTestMediator4";
}

#endif /* __VIEW_TEST_MEDIATOR4_HPP__ */
