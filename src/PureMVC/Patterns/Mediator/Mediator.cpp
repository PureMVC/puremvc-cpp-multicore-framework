//  Mediator.cpp
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#include "../../Common.hpp"

char const* const Mediator::NAME = "Mediator";

Mediator::Mediator(std::string const& mediator_name,
                   void const* view_component)
    : INotifier()
    , IMediator()
    , Notifier()
    , _mediator_name(mediator_name)
    , _view_component(view_component)
{ }

Mediator::Mediator(Mediator const& arg)
    : INotifier()
    , IMediator()
    , Notifier(arg)
    , _mediator_name(arg._mediator_name)
    , _view_component(arg._view_component)
{ }

inline std::string const& Mediator::getMediatorName(void) const
{
    return _mediator_name;
}

inline void Mediator::setViewComponent(void const* view_component)
{
    _view_component = view_component;
}

inline void const* Mediator::getViewComponent(void) const
{
    return _view_component;
}

inline Mediator::NotificationNames Mediator::listNotificationInterests(void) const
{
    typedef std::list<NotificationNames::element_type::type> list_t;
    typedef StdContainerAggregate<list_t> result_t;
    return NotificationNames(new result_t);
}

inline void Mediator::handleNotification(INotification const& notification)
{
    (void)notification;
}

inline void Mediator::onRegister(void)
{ }

inline void Mediator::onRemove(void)
{ }

Mediator& Mediator::operator=(Mediator const& arg)
{
    _mediator_name = arg._mediator_name;
    _view_component = arg._view_component;
    return *this;
}

Mediator::~Mediator(void)
{ }
