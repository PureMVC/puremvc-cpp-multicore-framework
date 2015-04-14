//  Iterator.hpp
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__PUREMVC_PATTERNS_ITERATOR_ITERATOR_HPP__)
#define __PUREMVC_PATTERNS_ITERATOR_ITERATOR_HPP__

// STL include
#include <functional>
#include <algorithm>
#include <exception>
#include <stdexcept>
// PureMVC include
#if !defined(__PUREMVC_HPP__)
#define __PUREMVC_INCLUDE__
#include "../../PureMVC.hpp"
#endif /* __PUREMVC_HPP__ */

#include "../../Interfaces/IIterator.hpp"

namespace PureMVC
{
    namespace Patterns
    {
        using Interfaces::IAggregate;
        using Interfaces::IIterator;

        /**
         * Default converter from stl-iterator to value.
         */
        template<typename _Type, typename _IteratorType>
        struct DefaultIteratorConverter : public std::unary_function<_IteratorType, _Type>
        {
            /**
             * Converting operator.
             *
             * @param iterator The stl-iterator.
             * @return The value of stl-iterator.
             */
            inline _Type const& operator()(_IteratorType const& iterator) const
            {
                return *(const _Type*)(&(*iterator));
            }
        };

        /**
         * Iterator template class.
         */
        template<typename _Type, 
                 typename _IteratorType = _Type,
                 typename _ConverterType = DefaultIteratorConverter<_Type, _IteratorType> >
        class Iterator : public virtual IIterator<_Type>
        {
        protected:
            mutable _IteratorType* _begin;
            mutable _IteratorType* _end;
            mutable _IteratorType* _current;
            mutable _ConverterType _converter;
            mutable PureMVC::FastMutex _mutex;
        public:
            /**
             * Empty default constructor.
             */
            explicit Iterator(void)
                : _begin(NULL)
                , _end(NULL)
                , _current(NULL)
            {  }

            /**
             * Constructor iterator with begin & end iterator.
             *
             * @param begin The begin point of stl-iterator.
             * @param end The end point of stl-iterator.
             **/
            explicit Iterator(_IteratorType const& begin, _IteratorType const& end)
                : _begin(new _IteratorType(begin) )
                , _end(new _IteratorType(end) )
                , _current(NULL)
            {  } 

            /**
             * Copy constructor.
             *
             * @param arg The iterator.
             */
            explicit Iterator(Iterator const& arg)
                : _begin(new _IteratorType(*(arg._begin) ) )
                , _end(new _IteratorType(*(arg._end) ) )
                , _current(new _IteratorType(*(arg._current) ) )
            {  }

#if defined(PUREMVC_USES_RVALUE)
            /**
             * Move constructor.
             *
             * @param arg The iterator.
             */
            explicit Iterator(Iterator&& arg)
                : _begin(std::move(arg._begin) )
                , _end(std::move(arg._end) )
                , _current(std::move(arg._current) )
            {
                arg._begin = NULL;
                arg._end = NULL;
                arg._current = NULL;
            }
#endif
        public:
            /**
             * Gets the current item.
             *
             * @return The references of current item.
             */
            virtual _Type const& getCurrent(void) const
            {
                PureMVC::FastMutex::ScopedLock _(_mutex);
                if (this->_begin == NULL)
                    throw std::runtime_error("Begin iterator is null.");
                if (this->_end == NULL )
                    throw std::runtime_error("End iterator is null.");
                if (this->_current == NULL)
                    throw std::out_of_range("Iterator is out of range. Please use moveNext() method.");
                if (*this->_current == *_end)
                    throw std::out_of_range("Iterator is out of range. Please use reset() method.");
                return _converter(*this->_current);
            }

            /**
             * Gets the current item base on operator.
             *
             * @return The references of current item.
             */
            virtual _Type const& operator*() const
            {
                return getCurrent();
            }

            /**
             * Move to next item.
             *
             * @return True if it succeeds, false if it fails. 
             */
            virtual bool moveNext(void) const
            {
                PureMVC::FastMutex::ScopedLock _(_mutex);
                if (this->_begin == NULL)
                    throw std::runtime_error("Begin iterator is null.");
                if (this->_end == NULL )
                    throw std::runtime_error("End iterator is null.");
                if (this->_current == NULL)
                    this->_current = new _IteratorType(*_begin);
                else if (*this->_current == *_end)
                    return false;
                else
                    ++(*this->_current);
                if (*this->_current == *_end)
                    return false;
                return true;
            }

            /**
             * Reset iterator.
             */
            virtual void reset(void) const
            {
                PureMVC::FastMutex::ScopedLock _(_mutex);
                if (this->_current != NULL )
                    delete this->_current;

                this->_current = NULL;
            }

            /**
             * Setting stl-iterator range.
             *
             * @param begin The begin point of stl-iterator.
             * @param end The end point of stl-iterator.
             */
            virtual void operator()(_IteratorType const& begin, _IteratorType const& end) const
            {
                PureMVC::FastMutex::ScopedLock _(_mutex);
                if (this->_begin != NULL )
                    delete this->_begin;
                if (this->_end != NULL )
                    delete this->_end;
                if (this->_current != NULL )
                    delete this->_current;

                this->_current = NULL;
                this->_begin = new _IteratorType(begin);
                this->_end = new _IteratorType(end);
            }

            /**
             * Assignment operator.
             *
             * @return The reference of itself. 
             */
            Iterator& operator=(Iterator const& arg)
            {
                PureMVC::FastMutex::ScopedLock _(_mutex);
                if (this->_begin != NULL )
                    delete this->_begin;
                if (this->_end != NULL )
                    delete this->_end;
                if (this->_current != NULL )
                    delete this->_current;

                this->_current = new _IteratorType(arg._current);
                this->_begin = new _IteratorType(arg._begin);
                this->_end = new _IteratorType(arg._end);
                return *this;
            }

#if defined(PUREMVC_USES_RVALUE)
            /**
             * Moving operator.
             *
             * @return this The reference of itself. 
             */
            Iterator& operator=(Iterator&& arg)
            {
                PureMVC::FastMutex::ScopedLock _(_mutex);
                if (this->_begin != NULL )
                    delete this->_begin;
                if (this->_end != NULL )
                    delete this->_end;
                if (this->_current != NULL )
                    delete this->_current;

                this->_current = std::move(arg._current);
                this->_begin = std::move(arg._begin);
                this->_end = std::move(arg._end);
                arg._current = NULL;
                arg._begin = NULL;
                arg._end = NULL;
                return *this;
            }
#endif

        public:
            virtual ~Iterator(void)
            {
                if (this->_begin != NULL )
                    delete this->_begin;
                if (this->_end != NULL )
                    delete this->_end;
                if (this->_current != NULL )
                    delete this->_current;
                this->_begin = NULL;
                this->_end = NULL;
                this->_current = NULL;
            }
        };

        /**
         * Default converter from stl-iterator to value.
         */
        template<typename _Container,
                 typename _IteratorType = typename _Container::const_iterator>
        struct StdContainerRange
        {
            /**
             * Convert begin range of iterator.
             *
             * @param iterator The source iterator.
             * @return The result iterator.
             */
            inline _IteratorType begin(_Container const& iterator) const
            {
                return iterator.begin();
            }

            /**
             * Convert begin range of iterator.
             *
             * @param iterator The source iterator.
             * @return The result iterator.
             */
            inline _IteratorType end(_Container const& iterator) const
            {
                return iterator.end();
            }
        };

        /**
         * Default wrapper the stl-container to iterator pattern.
         */
        template<typename _ContainerType,
#if defined(_MSC_VER) && _MSC_VER < 1300
                 typename _ValueType = _ContainerType::value_type,
                 typename _IteratorType = _ContainerType::const_iterator,
#else
                 typename _ValueType = typename _ContainerType::value_type,
                 typename _IteratorType = typename _ContainerType::const_iterator,
#endif
                 typename _ConverterType = DefaultIteratorConverter<_ValueType, _IteratorType>,
                 typename _ContainerRangeType = StdContainerRange<_ContainerType, _IteratorType> >
        class StdContainerAggregate : public virtual IAggregate<_ValueType>
        {
        public:
            typedef _ContainerType ContainerType;
            typedef _ValueType ValueType;
            typedef _IteratorType IteratorType;
            typedef _ConverterType ConverterType;
            typedef _ContainerRangeType ContainerRangeType;
            typedef typename Interfaces::IAggregate<_ValueType> Aggregate;
        private:
            ContainerType _container;
            ContainerRangeType _container_range;
        private:
            template<typename _Type>
            static inline void setNull(_Type const& arg){ }
            template<typename _Type>
            static inline void setNull(_Type*& arg) { arg = NULL; }
            template<typename _Type>
            static inline void setNull(_Type const*& arg) { arg = NULL; }
        public:
            class IteratorImplement : public Patterns::Iterator<ValueType, IteratorType, ConverterType>
            {  friend class StdContainerAggregate<ContainerType, ValueType, IteratorType, ConverterType, ContainerRangeType>;    };
        public:
            /**
             * Default constructor.
             */
            explicit StdContainerAggregate(void)
            { }

            /**
             * Constructor with constant reference to stl-container.
             *
             * @param container the stl-iterator reference.
             */
            explicit StdContainerAggregate(ContainerType const& container)
                : _container(container)
            { }

            /**
             * Copy constructor.
             *
             * @param arg the target argument to be copy from.
             */
            explicit StdContainerAggregate(StdContainerAggregate const& arg)
                : _container(arg._container)
            { }

            #if defined(PUREMVC_USES_RVALUE)
            /**
             * Move constructor.
             *
             * @param arg the target argument to be move from.
             */
            explicit StdContainerAggregate(StdContainerAggregate&& arg)
                : _container(std::move(arg._container))
            {
                setNull(arg._container);
            }
            #endif
        public:
            /**
             * Assignment operator support.
             *
             * @param arg the target augment to be copy from.
             * @return The this reference.
             */
            StdContainerAggregate& operator=(StdContainerAggregate const& arg)
            {
                _container = arg._container;
                return *this;
            }

            #if defined(PUREMVC_USES_RVALUE)
            /**
             * Moving operator support.
             *
             * @param arg the target augment to be copy from.
             * @return The this reference.
             */
            StdContainerAggregate& operator=(StdContainerAggregate&& arg)
            {
                _container = std::move(arg._container);
                setNull(arg._container);
                return *this;
            }
            #endif
        public:
            /**
             * Get stl-container from aggregate.
             *
             * @return The stl-container reference.
             */
            virtual ContainerType& get(void)
            {
                return _container;
            }
            /**
             * Get stl-container from aggregate.
             *
             * @return The stl-container reference.
             */
            virtual ContainerType const& get(void) const
            {
                return _container;
            }
        public:
            /**
             * Set iterator to iterator.
             *
             * @param iterator the stl-iterator.
             */
            virtual void setIterator(IIterator<ValueType>& iterator) const
            {
                typename StdContainerAggregate::IteratorImplement* result;
                result = dynamic_cast<typename StdContainerAggregate::IteratorImplement*>(&iterator);
                setIterator(*result);
            }

            /**
             * Set iterator to iterator.
             *
             * @param iterator the stl-iterator.
             */
            virtual void setIterator(typename StdContainerAggregate<ContainerType, ValueType, IteratorType, ConverterType, ContainerRangeType>::IteratorImplement& iterator) const
            {
                iterator(_container_range.begin(_container), _container_range.end(_container));
            }

            /**
             * Get iterator from this.
             *
             * @return The auto pointer of iterator.
             */
#if defined(PUREMVC_USES_TR1)
            virtual std::unique_ptr<IIterator<ValueType> > getIterator(void) const
#else
            virtual std::auto_ptr<IIterator<ValueType> > getIterator(void) const
#endif
            {
#if defined(PUREMVC_USES_TR1)
                std::unique_ptr<IIterator<ValueType> > 
#else
                std::auto_ptr<IIterator<ValueType> > 
#endif
                result(new typename StdContainerAggregate::IteratorImplement());

                setIterator(*result);
                return result;
            }

            /**
             * Virtual destructor.
             */
            virtual ~StdContainerAggregate()
            { }
        };
    }
}

#endif /* __PUREMVC_PATTERNS_ITERATOR_ITERATOR_HPP__ */
