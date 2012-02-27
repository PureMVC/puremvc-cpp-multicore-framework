//  ViewTestMediator6.hpp
//  PureMVC_C++ Test suite
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__VIEW_TEST_MEDIATOR6_HPP__)
#define __VIEW_TEST_MEDIATOR6_HPP__

#include <string>
#include <PureMVC/PureMVC.hpp>
#include "ViewTest.hpp"

namespace data
{
    using PureMVC::Interfaces::INotification;
    using PureMVC::Interfaces::IView;
    using PureMVC::Patterns::Mediator;
    using PureMVC::Core::View;
    /**
     * A Mediator class used by ViewTest.
     */
    struct ViewTestMediator6 : public Mediator
    {
        /**
         * The Mediator base name
         */
        static char const* const NAME;
                
        /**
         * Constructor
         */
        ViewTestMediator6(std::string const& name, const void* view) 
            :Mediator(name, view)
        { }

        virtual NotificationNames listNotificationInterests(void) const
        {
            // be sure that the mediator has some Observers created
            // in order to test removeMediator
            typedef StdContainerAggregate<std::list<NotificationNames::element_type::type> > result_t;
            result_t* result = new result_t;
            result->get().push_back(ViewTest::NOTE6);
            return NotificationNames(result);
        }

        virtual void handleNotification(INotification const& notification)
        {
            (void)notification;
            IView& view = View::getInstance("ViewTestKey11");
            // Now supporting remove observer in list during loop
            view.removeMediator(getMediatorName());
        }

        void onRemove(void)
        {
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
    char const* const ViewTestMediator6::NAME = "ViewTestMediator6";
}

#endif /* __VIEW_TEST_MEDIATOR6_HPP__ */
