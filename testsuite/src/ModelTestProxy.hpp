//  ModelTestProxy.hpp
//  PureMVC_C++ Test suite
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__MODEL_TEST_PROXY_HPP__)
#define __MODEL_TEST_PROXY_HPP__

#include <PureMVC/PureMVC.hpp>

namespace data
{
    using PureMVC::Patterns::Proxy;

    struct ModelTestProxy: public Proxy
    {
        static char const* const NAME;
        static char const* const ON_REGISTER_CALLED;
        static char const* const ON_REMOVE_CALLED;

        ModelTestProxy() :Proxy(NAME, "")
        { }

        virtual void onRegister(void)
        {
            setData(ON_REGISTER_CALLED);
        }

        virtual void onRemove(void)
        {
            setData(ON_REMOVE_CALLED);
        }
    };

    char const* const ModelTestProxy::NAME = "ModelTestProxy";
    char const* const ModelTestProxy::ON_REGISTER_CALLED = "onRegister Called";
    char const* const ModelTestProxy::ON_REMOVE_CALLED = "onRemove Called";
}

#endif /* __MODEL_TEST_PROXY_HPP__ */
