//  IObserver.hpp
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__PUREMVC_INTERFACES_IOBSERVER_HPP__)
#define __PUREMVC_INTERFACES_IOBSERVER_HPP__

// STL include
#include <string>
// PureMVC include
#if !defined(__PUREMVC_HPP__)
#define __PUREMVC_INCLUDE__
#include "../PureMVC.hpp"
#endif /* __PUREMVC_HPP__ */

#include "INotification.hpp"

namespace PureMVC
{
    namespace Interfaces
    {
        /**
         * The interface definition for a PureMVC Observer.
         *
         * <P>
         * In PureMVC, <code>IObserver</code> implementors assume these responsibilities:
         * <UL>
         * <LI>Encapsulate the notification (callback) method of the interested object.</LI>
         * <LI>Encapsulate the notification context (this) of the interested object.</LI>
         * <LI>Provide methods for setting the interested object' notification method and context.</LI>
         * <LI>Provide a method for notifying the interested object.</LI>
         * </UL>
         *
         * <P>
         * PureMVC does not rely upon underlying event
         * models such as the one provided with Flash,
         * and ActionScript 3 does not have an inherent
         * event model.</P>
         *
         * <P>
         * The Observer Pattern as implemented within
         * PureMVC exists to support event driven communication
         * between the application and the actors of the
         * MVC triad.</P>
         *
         * <P>
         * An Observer is an object that encapsulates information
         * about an interested object with a notification method that
         * should be called when an <code>INotification</code> is broadcast. The Observer then
         * acts as a proxy for notifying the interested object.
         *
         * <P>
         * Observers can receive <code>Notification</code>s by having their
         * <code>notifyObserver</code> method invoked, passing
         * in an object implementing the <code>INotification</code> interface, such
         * as a subclass of <code>Notification</code>.</P>
         *
         * @see Interfaces/IView.hpp PureMVC::Interfaces::IView
         * @see Interfaces/INotification.hpp PureMVC::Interfaces::INotification
         */
        struct PUREMVC_API IObserver
        {
            /**
             * Notify the interested object.
             *
             * @param notification the <code>INotification</code> to pass to the interested object's notification method
             */
            virtual void notifyObserver(INotification const& notification) = 0;

            /**
             * Compare the given object to the notification context object.
             *
             * @param object the object to compare.
             * @return boolean indicating if the notification context and the observer are the same.
             */
            virtual bool compareNotifyContext(void const* object) const = 0;

            /**
             * Virtual destructor.
             */
            virtual ~IObserver(void);
        };
    }
}

#endif /* __PUREMVC_INTERFACES_IOBSERVER_HPP__ */
