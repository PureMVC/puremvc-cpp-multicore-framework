//  Controller.cpp
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#include "../Common.hpp"

char const* const Controller::MULTITON_MSG =
"Controller instance for this Multiton key already constructed!";

char const* const Controller::DEFAULT_KEY = "PureMVC";

inline Controller::CommandMap::key_type const& 
Controller::IteratorConverter::operator()
(Controller::CommandMap::const_iterator const& iterator) const
{
    return iterator->first;
}

inline Controller::CommandMap::const_iterator 
Controller::IteratorRange::begin(Controller::CommandMap const* const& iterator) const
{
    return iterator->begin();
}

inline Controller::CommandMap::const_iterator 
Controller::IteratorRange::end(Controller::CommandMap const* const& iterator) const
{
    return iterator->end();
}

IController* Controller::find(std::string const& key)
{
    return puremvc_controller_instance_map.find(key);
}

void Controller::insert(std::string const& key, IController* controller)
{
    puremvc_controller_instance_map.insert(key, controller);
}

Controller::Controller(std::string const& key)
    : _multiton_key(key)
    , _view(NULL)
{
    if (puremvc_controller_instance_map.find(_multiton_key))
        throw std::runtime_error(MULTITON_MSG);
    puremvc_controller_instance_map.insert(_multiton_key, this);
    initializeController();
}

inline void Controller::initializeController(void)
{
    if (_view != NULL)
        return;
    _view  = &View::getInstance(_multiton_key);
}

IController & Controller::getInstance(std::string const& key)
{
    IController* result = puremvc_controller_instance_map.find(key);
    if (result == NULL)
    {
        result = new Controller(key);
        puremvc_controller_instance_map.insert(key, result);
    }
    return *result;
}

void Controller::executeCommand(INotification const& notification)
{
    CommandMap::iterator result = _command_map.end();
    do
    {
        PureMVC::FastMutex::ScopedLock lock(_synchronous_access);
        result = _command_map.find(notification.getName());
        if (result == _command_map.end())
            return;
    }while (false);
    result->second->execute(notification);
}

void Controller::registerCommand(std::string const& notification_name, ICommand* command)
{
    PureMVC::FastMutex::ScopedLock lock(_synchronous_access);

    if (_command_map.find(notification_name) == _command_map.end() )
    {
        if (_view == NULL)
            throwException<std::runtime_error>("Cannot register command [%s]. View is null.", notification_name.c_str());

        IObserver* observer = createObserver(&Controller::executeCommand, this);
        puremvc_observer_instance_map.insert(observer);
        _view->registerObserver(notification_name, observer);
    }
    command->initializeNotifier(_multiton_key);
    _command_map[notification_name] =  command;
}

inline bool Controller::hasCommand(std::string const& notification_name) const
{
    PureMVC::FastMutex::ScopedLock lock(_synchronous_access);
    return _command_map.find(notification_name) != _command_map.end();
}

ICommand* Controller::removeCommand(std::string const& notification_name)
{
    CommandMap::value_type::second_type command = NULL;

    do
    {
        PureMVC::FastMutex::ScopedLock lock(_synchronous_access);
        // Retrieve the named mediator
        CommandMap::iterator result = _command_map.find(notification_name);

        if (result == _command_map.end() )
            break;

        // get mediator
        command = result->second;
        // remove the mediator from the map
        _command_map.erase(result);
    }while (false);

    if (command != NULL)
    {
        if (_view == NULL)
            throwException<std::runtime_error>("Cannot remove command with notification name: [%s]. View is null.", notification_name.c_str());
        // remove the observer
        _view->removeObserver(notification_name, (IObserver*)this);
    }
    return command;
}

ICommand const& Controller::retrieveCommand(std::string const& notification_name) const
{
    PureMVC::FastMutex::ScopedLock lock(_synchronous_access);

    CommandMap::const_iterator result = _command_map.find(notification_name);
    if (result == _command_map.end())
        throwException<std::runtime_error>("Cannot find any command with notification name: [%s].", notification_name.c_str());

    return *result->second;
}

inline ICommand& Controller::retrieveCommand(std::string const& notification)
{
    return const_cast<ICommand&>(static_cast<Controller const&>(*this).retrieveCommand(notification));
}

void Controller::removeController(std::string const& key)
{
    puremvc_controller_instance_map.remove(key);
}

Controller::NotificationNames Controller::listNotificationNames(void) const
{
    typedef StdContainerAggregate<CommandMap const*,
                                  CommandMap::key_type,
                                  CommandMap::const_iterator,
                                  IteratorConverter,
                                  IteratorRange> result_t;
#if defined(PUREMVC_USES_TR1)
    return std::unique_ptr<IAggregate<CommandMap::key_type> >(new result_t(&_command_map));
#else
    return std::auto_ptr<IAggregate<CommandMap::key_type> >(new result_t(&_command_map));
#endif
}

Controller::~Controller(void)
{
    removeController(_multiton_key);
    _command_map.clear();
}
