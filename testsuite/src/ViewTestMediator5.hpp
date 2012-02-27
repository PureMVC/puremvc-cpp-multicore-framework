//  ViewTestMediator5.hpp
//  PureMVC_C++ Test suite
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__VIEW_TEST_MEDIATOR5_HPP__)
#define __VIEW_TEST_MEDIATOR5_HPP__

#include <string>
#include <PureMVC/PureMVC.hpp>
#include "ViewTest.hpp"

namespace data
{
    using PureMVC::Patterns::Mediator;
   /**
    * A Mediator class used by ViewTest.
    */
    struct ViewTestMediator5 : public Mediator
    {
       /**
         * The Mediator name
         */
        static char const* const NAME;
                
        /**
         * Constructor
         */
        ViewTestMediator5(const void* view) 
            :Mediator(NAME, view)
        { }

        virtual NotificationNames listNotificationInterests(void) const
        {
            // be sure that the mediator has some Observers created
            // in order to test removeMediator
            typedef StdContainerAggregate<std::list<NotificationNames::element_type::type> > result_t;
            result_t* result = new result_t;
            result->get().push_back(ViewTest::NOTE5);
            return NotificationNames(result);
        }

        virtual void handleNotification(INotification const& notification)
        {
            (void)notification;
            viewTest()->counter++;
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
    char const* const ViewTestMediator5::NAME = "ViewTestMediator5";
}

#endif /* __VIEW_TEST_MEDIATOR5_HPP__ */
