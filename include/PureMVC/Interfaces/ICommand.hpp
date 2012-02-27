//  ICommand.hpp
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__PUREMVC_INTERFACES_ICOMMMAND_HPP__)
#define __PUREMVC_INTERFACES_ICOMMMAND_HPP__

// PureMVC include
#if !defined(__PUREMVC_HPP__)
#define __PUREMVC_INCLUDE__
#include "../PureMVC.hpp"
#endif /* __PUREMVC_HPP__ */

#include "INotifier.hpp"
#include "INotification.hpp"

namespace PureMVC
{
    namespace Interfaces
    {
        /**
         * The interface definition for a PureMVC Command.
         *
         * @see Interfaces/INotification.hpp PureMVC::Interfaces::INotification
         */
        struct PUREMVC_API ICommand : public virtual INotifier
        {
            /**
             * Execute the <code>ICommand</code>'s logic to handle a given <code>INotification</code>.
             *
             * @param notification an <code>INotification</code> to handle.
             */
            virtual void execute(INotification const& notification) = 0;

            /**
             * Virtual destructor.
             */
            virtual ~ICommand(void);
        };
    }
}

#endif /* __PUREMVC_INTERFACES_ICOMMMAND_HPP__ */
