//  Notification.cpp
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#include "../../Common.hpp"

Notification::Notification(std::string const& name,
                           void const* body,
                           std::string const& type)
    : INotification()
    , _name(name)
    , _body(body)
    , _type(type)
{ }

Notification::Notification(Notification const& arg)
    : INotification()
    , _name(arg._name)
    , _body(arg._body)
    , _type(arg._type)
{ }

inline std::string const& Notification::getName(void) const
{
    return _name;
}

inline void Notification::setBody(void const* body)
{
    _body = body;
}

inline void const* Notification::getBody(void) const
{
    return _body;
}

inline void Notification::setType(std::string const& type)
{
    _type = type;
}

inline std::string const& Notification::getType(void) const
{
    return _type;
}

inline std::string Notification::toString(void) const
{
    std::string msg;
    toString(msg);
    return msg;
}

void Notification::toString(std::string& arg) const
{
    arg = "Notification Name: ";
    arg += getName();
    arg += "\nBody: ";
    arg += typeid(_body).name();
    arg += "\nType: ";
    arg += _type;
}

Notification& Notification::operator=(Notification const& arg)
{
    _name = arg._name;
    _type = arg._type;
    _body = arg._body;
    return *this;
}

Notification::~Notification(void)
{ }
