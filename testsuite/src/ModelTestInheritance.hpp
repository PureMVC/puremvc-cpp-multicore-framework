//  ModelTestInheritance.hpp
//  PureMVC_C++ Test suite
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__MODEL_TEST_HERITANCE_HPP__)
#define __MODEL_TEST_HERITANCE_HPP__

#include <PureMVC/PureMVC.hpp>

namespace data
{
    using PureMVC::Interfaces::IModel;
    using PureMVC::Core::Model;

    class ModelTestInheritance 
        : public virtual IModel
        , public Model
    {
        friend class Model;
    public:
        std::string* initializeModelCalled;
    protected:
        ModelTestInheritance(void)
        :Model(this, "ModelTestInheritance")
        { }
    public:
        static ModelTestInheritance& getInstance(void)
        {
            if (Model::find("ModelTestInheritance") == NULL)
                new ModelTestInheritance();
            return *(dynamic_cast<ModelTestInheritance*>(&Model::getInstance("ModelTestInheritance")));
        }
    protected:
        void initializeModel(void)
        {
            initializeModelCalled = new std::string("Called!!!");
            Model::initializeModel();
        }
    public:
        ~ModelTestInheritance()
        {
            delete initializeModelCalled;
        }
    };
}

#endif /* __MODEL_TEST_HERITANCE_HPP__ */
