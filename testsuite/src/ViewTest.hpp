//  ViewTest.hpp
//  PureMVC_C++ Test suite
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__VIEW_TEST_HPP__)
#define __VIEW_TEST_HPP__

#include <string>
#include <map>
#include <PureMVC/PureMVC.hpp>
    
namespace data
{
    using PureMVC::Interfaces::INotification;

    struct ViewTest
    {
        std::string lastNotification;
        bool onRegisterCalled;
        bool onRemoveCalled;
        int counter;
        PureMVC::Mutex viewTestVarsLock;
        std::map<std::string, int> viewTestVars;
        ViewTest();
        // viewTestMethod must be virtual!!! 
        virtual void viewTestMethod(INotification const& note);
        static char const* const NOTE1;
        static char const* const NOTE2;
        static char const* const NOTE3;
        static char const* const NOTE4;
        static char const* const NOTE5;
        static char const* const NOTE6;
    };
}

#endif /* __VIEW_TEST_HPP__ */
