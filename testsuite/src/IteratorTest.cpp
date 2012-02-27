//  IteratorTest.cpp
//  PureMVC_C++ Test suite
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if defined(_MSC_VER)
#pragma warning( disable : 4250 ) // Disable: 'class1' : inherits 'class2::member' via dominance
#pragma warning( disable : 4355 ) // The this pointer is valid only within nonstatic member functions. It cannot be used in the initializer list for a base class.ck(16)
#endif

#include <tut/tut.hpp>
#include <tut_reporter.h>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <PureMVC/PureMVC.hpp>

#include "IteratorTest.hpp"

namespace data
{
    std::string const& IteratorTest::Converter::operator()(list_string_t::const_iterator const& iterator) const {
        return *iterator;
    }

    void IteratorTest::setIterator(IIterator<std::string>& iterator) const
    {
        IteratorTest::Iterator* result;
        result = dynamic_cast<IteratorTest::Iterator*>(&iterator);
        setIterator(*result);
    }

    IAggregate<std::string>::Iterator IteratorTest::getIterator(void) const
    {
        IAggregate<std::string>::Iterator result(new IteratorTest::Iterator());
        setIterator(*result);
        return result;
    }

    void IteratorTest::setIterator(IteratorTest::Iterator& iterator) const
    {
        iterator(listItem.begin(), listItem.end());
    }
}

namespace testgroup
{
    typedef tut::test_group<data::IteratorTest> itearator_test_t;
    typedef itearator_test_t::object object;
    itearator_test_t iterator_test("IteratorTest");
}

namespace tut
{
    using namespace testgroup;

    using PureMVC::Interfaces::IIterator;
    using PureMVC::Interfaces::IAggregate;
    using PureMVC::Patterns::StdContainerAggregate;
    using PureMVC::Patterns::Iterator;

    template<> template<> 
    void object::test<1>(void)
    {
        set_test_name("testGetIterator");

        IAggregate<std::string>::Iterator ret = this->getIterator();
        ensure("Expecting ret.get() != null", ret.get() != NULL);
    }

    template<> template<> 
    void object::test<2>(void)
    {
        set_test_name("testSetIterator");

        Iterator ret; 
        bool throw_exception = false;
        try
        {
            throw_exception = false;
            ret.getCurrent();
        }
        catch (std::exception const&)
        {
            throw_exception = true;
        }
        ensure("Expecting ret.getCurrent() throw exception", throw_exception);
        try
        {
            throw_exception = false;
            ret.moveNext();
        }
        catch (std::exception const&)
        {
            throw_exception = true;
        }
        ensure("Expecting ret.moveNext() throw exception", throw_exception);
        try
        {
            throw_exception = false;
            ret.reset();
        }
        catch (std::exception const&)
        {
            throw_exception = true;
        }
        ensure("Expecting ret.reset() nothrow exception", throw_exception == false);

        listItem.clear();
        listItem.push_back("test");

        this->setIterator(ret);

        ensure("Expecting ret.moveNext() == true", ret.moveNext());
        ensure_equals("Expecting ret.getCurrent() == test", ret.getCurrent(), "test");
    }

    template<> template<> 
    void object::test<4>(void)
    {
        set_test_name("testStdContainerAggregate");

        do
        {
            typedef StdContainerAggregate<std::vector<int> > type_t;

            type_t v;
            v.get().push_back(2);
            v.get().push_back(4);
            v.get().push_back(-5);
            v.get().push_back(7);

            type_t::Iterator iter = v.getIterator();

            std::size_t count = 0;

            while(iter->moveNext())
            {
                ++count;
                if (count == 3)
                    ensure_equals("Expecting iter->getCurrent() == -5", iter->getCurrent(), -5);
            }

            ensure_equals("Expecting number of element == 4", count, 4);
        }while (false);

        do
        {
            typedef StdContainerAggregate<std::list<int> > type_t;

            type_t v;
            v.get().push_back(2);
            v.get().push_back(4);
            v.get().push_back(-5);
            v.get().push_back(7);

            type_t::Iterator iter = v.getIterator();

            std::size_t count = 0;

            while(iter->moveNext())
            {
                ++count;
                if (count == 3)
                    ensure_equals("Expecting iter->getCurrent() == -5", iter->getCurrent(), -5);
            }

            ensure_equals("Expecting number of element == 4", count, 4);
        }while (false);

        do
        {
            typedef StdContainerAggregate<std::set<int> > type_t;

            type_t v;
            v.get().insert(2);
            v.get().insert(4);
            v.get().insert(2);
            v.get().insert(7);

            type_t::Iterator iter = v.getIterator();

            std::size_t count = 0;

            while(iter->moveNext())
            {
                ++count;
                if (count == 2)
                    ensure_equals("Expecting iter->getCurrent() == 4", iter->getCurrent(), 4);
            }

            ensure_equals("Expecting number of element == 3", count, 3);
        }while (false);

        do
        {
            typedef StdContainerAggregate<std::multiset<int> > type_t;

            type_t v;
            v.get().insert(7);
            v.get().insert(2);
            v.get().insert(4);
            v.get().insert(2);
            v.get().insert(7);

            type_t::Iterator iter = v.getIterator();

            std::size_t count = 0;

            while(iter->moveNext())
            {
                ++count;
                if (count == 4)
                    ensure_equals("Expecting iter->getCurrent() == 7", iter->getCurrent(), 7);
            }

            ensure_equals("Expecting number of element == 5", count, 5);
        }while (false);

        do
        {
            typedef StdContainerAggregate<std::map<int, std::string> > type_t;

            type_t v;
            v.get().insert(std::pair<int, std::string>(1, "How"));
            v.get().insert(std::pair<int, std::string>(4, "you"));
            v.get().insert(std::pair<int, std::string>(2, "are"));

            type_t::Iterator iter = v.getIterator();

            std::size_t count = 0;

            while(iter->moveNext())
            {
                ++count;
                if (count == 3)
                    ensure_equals("Expecting iter->getCurrent().second == you", 
                        iter->getCurrent().second, std::string("you"));
            }

            ensure_equals("Expecting number of element == 3", count, 3);
        }while (false);
    }
}
