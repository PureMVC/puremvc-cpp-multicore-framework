//  Proxy.cpp
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#include "../../Common.hpp"

char const* const Proxy::NAME = "Proxy";

Proxy::Proxy(std::string const& proxy_name, void const* data)
    : INotifier()
    , IProxy()
    , Notifier()
    , _proxy_name(proxy_name)
    , _data(data)
{ }

Proxy::Proxy(Proxy const& arg)
    : INotifier()
    , IProxy()
    , Notifier(arg)
    , _proxy_name(arg._proxy_name)
    , _data(arg._data)
{ }

inline std::string const& Proxy::getProxyName(void) const
{
    return _proxy_name;
}

inline void Proxy::setData(void const* data)
{
    _data = data;
}

inline void const* Proxy::getData(void) const
{
    return _data;
}

inline void Proxy::onRegister(void)
{ }

inline void Proxy::onRemove(void)
{ }

Proxy& Proxy::operator=(Proxy const& arg)
{
    _proxy_name = arg._proxy_name;
    _data = arg._data;
    return *this;
}

Proxy::~Proxy(void)
{ }
