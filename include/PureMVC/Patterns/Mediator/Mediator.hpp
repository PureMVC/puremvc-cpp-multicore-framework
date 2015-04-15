//  Mediator.hpp
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__PUREMVC_PATTERNS_MEDIATOR_MEDIATOR_HPP__)
#define __PUREMVC_PATTERNS_MEDIATOR_MEDIATOR_HPP__

// STL include
#include <string>
// PureMVC include
#if !defined(__PUREMVC_HPP__)
#define __PUREMVC_INCLUDE__
#include "../../PureMVC.hpp"
#endif /* __PUREMVC_HPP__ */

#include "../../Interfaces/ICommand.hpp"
#include "../Observer/Notifier.hpp"

namespace PureMVC
{
    namespace Patterns
    {
        using Interfaces::IMediator;
        using Interfaces::INotifier;

        /**
         * A base <code>IMediator</code> implementation.
         *
         * @see Core/View.hpp PureMVC::Core::View
         */
        class PUREMVC_API Mediator
            : public virtual IMediator
            , public virtual INotifier
            , public Notifier
        {
        public:
            /**
             * Copy constructor.
             */
            explicit Mediator(Mediator const& arg);

        public:
            /**
             * Constructor.
             */
            Mediator(std::string const& mediator_name = Mediator::NAME, void const* view_component = NULL);

            /**
             * Get the name of the <code>Mediator</code>.
             */
            virtual std::string const& getMediatorName(void) const;

            /**
             * Set the <code>IMediator</code>'s view component.
             *
             * @param view_component the view component.
             */
            virtual void setViewComponent(void const* view_component);

            /**
             * Get the <code>Mediator</code>'s view component.
             *
             * <P>
             * Additionally, an implicit getter will usually
             * be defined in the subclass that casts the view
             * object to a type</P>
             *
             * @return the view component.
             */
            virtual void const* getViewComponent(void) const;

            /**
             * List the <code>INotification</code> names this
             * <code>Mediator</code> is interested in being notified of.
             *
             * @return Array the list of <code>INotification</code> names.
             */
            virtual Mediator::NotificationNames listNotificationInterests(void) const;

            /**
             * Handle <code>INotification</code>s.
             *
             * <P>
             * Typically this will be handled in a switch statement,
             * with one 'case' entry per <code>INotification</code>
             * the <code>Mediator</code> is interested in.
             */
            virtual void handleNotification(INotification const& notification);

            /**
             * Called by the View when the Mediator is registered.
             */
            virtual void onRegister(void);

            /**
             * Called by the View when the Mediator is removed.
             */
            virtual void onRemove(void);

            /**
             * Copy operator
             */
            Mediator& operator=(Mediator const& arg);

            /**
             * Virtual destructor.
             */
            virtual ~Mediator(void);

            /**
             * The name of the <code>Mediator</code>.
             *
             * <P>
             * Typically, a <code>Mediator</code> will be written to serve
             * one specific control or group controls and so,
             * will not have a need to be dynamically named.</P>
             */
        protected:
            // the mediator name
            std::string _mediator_name;
            // The view component
            void const* _view_component;
        public:
            static char const* const NAME;
        };
    }
}

#endif /* __PUREMVC_PATTERNS_MEDIATOR_MEDIATOR_HPP__ */
