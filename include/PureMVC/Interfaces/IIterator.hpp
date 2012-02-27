//  IIterator.hpp
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__PUREMVC_INTERFACES_IITERATOR_HPP__)
#define __PUREMVC_INTERFACES_IITERATOR_HPP__

// PureMVC include
#if !defined(__PUREMVC_HPP__)
#define __PUREMVC_INCLUDE__
#include "../PureMVC.hpp"
#endif /* __PUREMVC_HPP__ */

namespace PureMVC
{
    namespace Interfaces
    {
        /**
         * Interface of iterator class
         */
        template<typename _Type>
        struct IIterator
        {
            typedef _Type type;

            /**
             * Gets the current item.
             *
             * @return The references of current item.
            **/
            virtual _Type const& getCurrent(void) const = 0;

            /**
             * Gets the current item base on operator.
             *
             * @return The references of current item.
            **/
            virtual _Type const& operator*(void) const = 0;

            /**
             * Move to next item.
             *
             * @return true if it succeeds, false if it fails. 
            **/
            virtual bool moveNext(void) const = 0;

            /**
             * Reset iterator.
            **/
            virtual void reset(void) const = 0;

            /**
             * Virtual destructor.
             */
            virtual ~IIterator(void) { };
        };
    }
}

#endif /* __PUREMVC_INTERFACES_IITERATOR_HPP__ */
