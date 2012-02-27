//  MacroCommand.cpp2
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#include "../../Common.hpp"

MacroCommand::MacroCommand(void)
    : INotifier()
    , ICommand()
    , Notifier()
{
    initializeMacroCommand();
}

MacroCommand::MacroCommand(std::list<ICommand*> const& command_list)
    : INotifier()
    , ICommand()
    , Notifier()
    , _sub_commands(command_list)
{
    initializeMacroCommand();
}

MacroCommand::MacroCommand(MacroCommand const& arg)
    : INotifier()
    , ICommand()
    , Notifier(arg)
    , _sub_commands(arg._sub_commands)
{
    initializeMacroCommand();
}

inline void MacroCommand::initializeMacroCommand(void)
{ }

inline void MacroCommand::addSubCommand(ICommand* command)
{
    if (command == NULL)
        return;
    _sub_commands.push_back(command);
}

void MacroCommand::execute(INotification const& notification)
{
    CommandList::iterator result = _sub_commands.begin();
    while(result != _sub_commands.end())
    {
        (*result)->initializeNotifier(_multiton_key);
        (*result)->execute(notification);

        _sub_commands.erase(result);
        result = _sub_commands.begin();
    }
}

MacroCommand& MacroCommand::operator=(MacroCommand const& arg)
{
    _multiton_key = arg._multiton_key;
    _sub_commands = arg._sub_commands;
    return *this;
}

MacroCommand::~MacroCommand(void)
{ }
