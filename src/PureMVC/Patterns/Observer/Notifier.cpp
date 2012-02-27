//  Notifier.cpp
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#include "../../Common.hpp"

char const* const Notifier::MULTITON_MSG = 
"Multiton key for this Notifier not yet initialized!";

Notifier::Notifier(void)
    : INotifier()
{ }

Notifier::Notifier(Notifier const& arg)
    : INotifier()
    , _multiton_key(arg._multiton_key)
{ }

void Notifier::sendNotification(std::string const& notification_name,
                                       void const* body,
                                       std::string const& type)
{
    getFacade().sendNotification(notification_name, body, type);
}

void Notifier::initializeNotifier(std::string const& key)
{
    _multiton_key = key;
}

std::string const& Notifier::getMultitonKey(void) const
{
    return _multiton_key;
}

IFacade& Notifier::getFacade(void)
{
    if (_multiton_key == "" )
        throw std::runtime_error(MULTITON_MSG);
    return Facade::getInstance(_multiton_key);
}

Notifier& Notifier::operator=(Notifier const& arg)
{
    _multiton_key = arg._multiton_key;
    return *this;
}

Notifier::~Notifier(void)
{ }
