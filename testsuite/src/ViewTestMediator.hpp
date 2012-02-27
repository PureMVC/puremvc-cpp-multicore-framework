//  ViewTestMediator.hpp
//  PureMVC_C++ Test suite
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__VIEW_TEST_MEDIATOR_HPP__)
#define __VIEW_TEST_MEDIATOR_HPP__

#include <string>
#include <PureMVC/PureMVC.hpp>

namespace data
{
    using PureMVC::Patterns::Mediator;
    using PureMVC::Patterns::StdContainerAggregate;
    using PureMVC::Interfaces::IMediator;
    /**
     * A Mediator class used by ViewTest.
     */
    struct ViewTestMediator : public Mediator
    {
        /**
         * The Mediator name
         */
        static char const* const NAME;

        /**
         * Constructor
         */
        ViewTestMediator(std::string const& name, void const* view)
            :Mediator(name, view)
        { }

        virtual NotificationNames listNotificationInterests(void) const
        {
            typedef StdContainerAggregate<std::list<NotificationNames::element_type::type> > result_t;
            result_t* result = new result_t;
            result->get().push_back("ABC");
            result->get().push_back("DEF");
            result->get().push_back("GHI");
            return NotificationNames(result);
        }
    };
    char const* const ViewTestMediator::NAME = "ViewTestMediator";
}

#endif /* __VIEW_TEST_MEDIATOR_HPP__ */
