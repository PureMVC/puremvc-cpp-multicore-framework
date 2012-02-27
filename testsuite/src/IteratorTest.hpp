//  IteratorTest.hpp
//  PureMVC_C++ Test suite
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__ITERATOR_TEST_HPP__)
#define __ITERATOR_TEST_HPP__

#include <PureMVC/PureMVC.hpp>

namespace data
{
    using PureMVC::Interfaces::IIterator;
    using PureMVC::Interfaces::IAggregate;

    struct IteratorTest : public IAggregate<std::string>
    {
        typedef std::list<std::string> list_string_t;
        std::list<std::string> listItem;

        struct Converter : public std::unary_function<list_string_t::const_iterator, std::string> {
            std::string const& operator()(list_string_t::const_iterator const& iterator) const;
        };
        class Iterator : public PureMVC::Patterns::Iterator<std::string, list_string_t::const_iterator, Converter>
        {  friend struct IteratorTest;    };

        virtual void setIterator(IIterator<std::string>& iterator) const;

        virtual void setIterator(IteratorTest::Iterator& iterator) const;

        virtual IAggregate<std::string>::Iterator getIterator(void) const;
        };
}

#endif /* __ITERATOR_TEST_HPP__ */
