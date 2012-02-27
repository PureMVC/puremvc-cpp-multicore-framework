//  ControllerTestInheritance.hpp
//  PureMVC_C++ Test suite
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__CONTROLLER_TEST_HERITANCE_HPP__)
#define __CONTROLLER_TEST_HERITANCE_HPP__

#include <PureMVC/PureMVC.hpp>

namespace data
{
    using PureMVC::Core::Controller;
    using PureMVC::Interfaces::IController;

    class ControllerTestInheritance 
        : public virtual IController
        , public Controller
    {
        friend class Controller;
    public:
        std::string* initializeControllerCalled;
    protected:
        ControllerTestInheritance(void)
        :Controller(this, "ControllerTestInheritance")
        { }
    public:
        static ControllerTestInheritance& getInstance(void)
        {
            if (Controller::find("ControllerTestInheritance") == NULL)
                new ControllerTestInheritance();
            return *(dynamic_cast<ControllerTestInheritance*>(&Controller::getInstance("ControllerTestInheritance")));
        }
    protected:
        virtual void initializeController(void)
        {
            initializeControllerCalled = new std::string("Called!!!");
            Controller::initializeController();
        }
    public:
        ~ControllerTestInheritance()
        {
            delete initializeControllerCalled;
        }
    };
}

#endif /* __CONTROLLER_TEST_HERITANCE_HPP__ */
