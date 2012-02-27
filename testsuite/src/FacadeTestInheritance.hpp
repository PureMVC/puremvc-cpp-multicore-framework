//  FacadeTestInheritance.hpp
//  PureMVC_C++ Test suite
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__FACADE_TEST_HERITANCE_HPP__)
#define __FACADE_TEST_HERITANCE_HPP__

#include <PureMVC/PureMVC.hpp>

namespace data
{
    using PureMVC::Interfaces::IFacade;
    using PureMVC::Patterns::Facade;

    class FacadeTestInheritance
        : public virtual IFacade
        , public Facade
    {
        friend class Facade;
    public:
        std::string* initializeNotifierCalled;
        std::string* initializeFacadeCalled;
    protected:
        FacadeTestInheritance(void)
        :Facade(this, "FacadeTestInheritance")
        { }
    public:
        static FacadeTestInheritance& getInstance(void)
        {
            if (Facade::hasCore("FacadeTestInheritance"))
            {
                return *(dynamic_cast<FacadeTestInheritance*>(&Facade::getInstance("FacadeTestInheritance")));
            }
            return *(new FacadeTestInheritance());
        }
    protected:
        void initializeNotifier(std::string const& key)
        {
            initializeNotifierCalled = new std::string("Called!!!");
            Facade::initializeNotifier(key);
        }

        void initializeFacade(void)
        {
            initializeFacadeCalled = new std::string("Called!!!");
            Facade::initializeFacade();
        }
        ~FacadeTestInheritance()
        {
            delete initializeNotifierCalled;
            delete initializeFacadeCalled;
        }
    };
}

#endif /* __FACADE_TEST_HERITANCE_HPP__ */
