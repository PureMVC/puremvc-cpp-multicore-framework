//  SimpleCommand.cpp
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#include "../../Common.hpp"

SimpleCommand::SimpleCommand(void)
    : INotifier()
    , ICommand()
    , Notifier()
{ }

SimpleCommand::SimpleCommand(SimpleCommand const& arg)
    : INotifier()
    , ICommand()
    , Notifier(arg)
{ }

inline void SimpleCommand::execute(INotification const& notification)
{
    (void)notification;
}

SimpleCommand& SimpleCommand::operator=(SimpleCommand const& arg)
{
    _multiton_key = arg._multiton_key;
    return *this;
}

SimpleCommand::~SimpleCommand(void)
{ }
