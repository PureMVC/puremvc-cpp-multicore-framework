//  ViewTestNote.hpp
//  PureMVC_C++ Test suite
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__VIEW_TEST_NOTE_HPP__)
#define __VIEW_TEST_NOTE_HPP__

#include <string>
#include <PureMVC/PureMVC.hpp>

namespace data
{
    using PureMVC::Interfaces::INotification;
    using PureMVC::Patterns::Notification;
   /**
   * A Notification class used by ViewTest.
   * 
   * @see org.puremvc.as3.multicore.core.view.ViewTest ViewTest
   */
    struct ViewTestNote : public Notification
    {
        /**
         * The name of this Notification.
         */
        static char const* const NAME;
        /**
         * Constructor.
         * 
         * @param name Ignored and forced to NAME.
         * @param body the body of the Notification to be constructed.
         */
        ViewTestNote(std::string const& name, void const* body)
            :Notification(name, body)
        { }
        
        /**
         * Factory method.
         * 
         * <P> 
         * This method creates new instances of the ViewTestNote class,
         * automatically setting the note name so you don't have to. Use
         * this as an alternative to the constructor.</P>
         * 
         * @param name the name of the Notification to be constructed.
         * @param body the body of the Notification to be constructed.
         */
        static INotification* create(std::string const& name, void const* body ) 
        {
            return new data::ViewTestNote(name, body);
        }
    };
    char const* const ViewTestNote::NAME = "ViewTestNote";
}

#endif /* __VIEW_TEST_NOTE_HPP__ */
