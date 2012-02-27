//  View.hpp
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__PUREMVC_CORE_VIEW_HPP__)
#define __PUREMVC_CORE_VIEW_HPP__

// STL include
#include <string>
#include <exception>
#include <cassert>
#include <stdexcept>
// PureMVC include
#if !defined(__PUREMVC_HPP__)
#define __PUREMVC_INCLUDE__
#include "../PureMVC.hpp"
#endif /* __PUREMVC_HPP__ */
#if defined(PUREMVC_USES_TR1)
#if defined(__GNUC__) || defined(__MINGW32__)
#include <tr1/unordered_map>
#else
#include <unordered_map>
#endif
#else
#include <map>
#endif

#include "../Interfaces/IView.hpp"
#include "../Interfaces/IObserver.hpp"
#include "../Interfaces/INotification.hpp"
#include "../Interfaces/IMediator.hpp"
#include "../Interfaces/IAggregate.hpp"
#include "../Interfaces/IIterator.hpp"
#include "../Patterns/Iterator/Iterator.hpp"

namespace PureMVC
{
    namespace Core
    {
        using Interfaces::IObserver;
        using Interfaces::IView;
        using Interfaces::INotification;
        using Interfaces::IMediator;
        using Interfaces::IAggregate;
        using Interfaces::IIterator;

        /**
         * A Multiton <code>IView</code> implementation.
         *
         * <P>
         * In PureMVC, the <code>View</code> class assumes these responsibilities:
         * <UL>
         * <LI>Maintain a cache of <code>IMediator</code> instances.</LI>
         * <LI>Provide methods for registering, retrieving, and removing <code>IMediators</code>.</LI>
         * <LI>Notifiying <code>IMediators</code> when they are registered or removed.</LI>
         * <LI>Managing the observer lists for each <code>INotification</code> in the application.</LI>
         * <LI>Providing a method for attaching <code>IObservers</code> to an <code>INotification</code>'s observer list.</LI>
         * <LI>Providing a method for broadcasting an <code>INotification</code>.</LI>
         * <LI>Notifying the <code>IObservers</code> of a given <code>INotification</code> when it broadcast.</LI>
         * </UL>
         *
         * @see Patterns/Mediator/Mediator.hpp PureMVC::Patterns::Mediator
         * @see Patterns/Observer/Observer.hpp PureMVC::Patterns::Observer
         * @see Patterns/Observer/Notification.hpp PureMVC::Patterns::Notification
         */
        class PUREMVC_API View : public virtual IView
        {
        protected:
#if defined(PUREMVC_USES_TR1)
            typedef std::tr1::unordered_map<std::string, IMediator*> MediatorMap;
            typedef std::tr1::unordered_multimap<std::string, IObserver*> ObserverMap;
#else
            typedef std::map<std::string, IMediator*> MediatorMap;
            typedef std::multimap<std::string, IObserver*> ObserverMap;
#endif
        protected:
            /*
             * Define iterator converter for getting mediator name only.
             */
            struct IteratorConverter
#if !defined(__DMC__) // The C++ compiler of Digital Mars cannot resolve this case
            : public std::unary_function<MediatorMap::const_iterator, MediatorMap::key_type>
#endif
            {
            /*
             * Converting operator.
             *
             * @param iterator the iterator of internal container.
             * @return the name of mediator inside iterator.
             */
                MediatorMap::key_type const& operator()(MediatorMap::const_iterator const& iterator) const;
            };
            /*
             * Define iterator range of internal container.
             */
            struct IteratorRange {
                /*
                 * Get begin point.
                 *
                 * @return the begin of iterator.
                 */
                MediatorMap::const_iterator begin(MediatorMap const* const& iterator) const;
                /*
                 * Get end point.
                 *
                 * @return the end of iterator.
                 */
                MediatorMap::const_iterator end(MediatorMap const* const& iterator) const;
            };
        public:
            static char const* const DEFAULT_KEY;
        protected:
            // Message Constants
            static char const* const MULTITON_MSG;
        protected:
            // The Multiton Key for this Core
            std::string const _multiton_key;
            // Mapping of Mediator names to Mediator instances
            MediatorMap _mediator_map;
            // Mapping of Notification names to Observer lists
            ObserverMap _observer_map;
            // Synchronous access
            mutable FastMutex _synchronous_access;
        private:
            View(View const&);
            View(IView const&);
            View& operator=(View const&);
            View& operator=(IView const&);
        protected:
            static IView* find(std::string const& key);
            static void insert(std::string const& key, IView* view);
        public:
            /**
             * Constructor.
             *
             * <P>
             * This <code>IView</code> implementation is a Multiton,
             * so you should not call the constructor
             * directly, but instead call the static Multiton
             * Factory method <code>View::getInstance(key)</code>
             *
             * @throws Error Error if instance for this Multiton key has already been constructed
             *
             */
            explicit View(std::string const& key = PureMVC::Core::View::DEFAULT_KEY);
        protected:
            /**
             * Constructor.
             *
             * <P>
             * Support call virtual method in constructor of base class (<code>View</code>).
             *
             * Condition: Derived class (class inherit from <code>View</code>) must implement method: initializeView
             *
             * Please use in this way:
             * <code>
             * 
             * ConcreateView::ConcreateView(void)
             * :View(this)
             * {
             *     // Your code here
             * }
             * </code>
             *
             * Factory method <code>View::getInstance( key )</code>
             *
             * @throws Error Error if instance for this Multiton key has already been constructed
             *
             */
            template<typename _DerivedType>
            explicit View(_DerivedType* instance, std::string const& key = PureMVC::Core::View::DEFAULT_KEY)
                : _multiton_key(key)
            {
                if (find(key))
                    throw std::runtime_error(MULTITON_MSG);
                insert(_multiton_key, this);
                instance->_DerivedType::initializeView();
            }

            /**
             * Initialize the Singleton View instance.
             *
             * <P>
             * Called automatically by the constructor, this
             * is your opportunity to initialize the Singleton
             * instance in your subclass without overriding the
             * constructor.</P>
             *
             * @return void
             */
            virtual void initializeView(void);

        public:
            /**
             * View Singleton Factory method.
             *
             * @return the Singleton instance of <code>View</code>
             */
            static IView& getInstance(std::string const& key = PureMVC::Core::View::DEFAULT_KEY);

            /**
             * Register an <code>IObserver</code> to be notified
             * of <code>INotifications</code> with a given name.
             *
             * @param notification_name the name of the <code>INotifications</code> to notify this <code>IObserver</code> of
             * @param observer the <code>IObserver</code> to register
             */
            virtual void registerObserver (std::string const& notification_name, IObserver* observer);

            /**
             * Notify the <code>IObservers</code> for a particular <code>INotification</code>.
             *
             * <P>
             * All previously attached <code>IObservers</code> for this <code>INotification</code>'s
             * list are notified and are passed a reference to the <code>INotification</code> in
             * the order in which they were registered.</P>
             *
             * @param notification the <code>INotification</code> to notify <code>IObservers</code> of.
             */
            virtual void notifyObservers(INotification const& notification);

            /**
             * Remove the observer for a given notifyContext from an observer list for a given Notification name.
             * <P>
             * @param notification_name which observer list to remove from
             * @param notify_context remove the observer with this object as its notify_context
             */
            virtual void removeObserver(std::string const& notification_name, void const* notify_context);

            /**
             * Register an <code>IMediator</code> instance with the <code>View</code>.
             *
             * <P>
             * Registers the <code>IMediator</code> so that it can be retrieved by name,
             * and further interrogates the <code>IMediator</code> for its
             * <code>INotification</code> interests.</P>
             * <P>
             * If the <code>IMediator</code> returns any <code>INotification</code>
             * names to be notified about, an <code>Observer</code> is created encapsulating
             * the <code>IMediator</code> instance's <code>handleNotification</code> method
             * and registering it as an <code>Observer</code> for all <code>INotifications</code> the
             * <code>IMediator</code> is interested in.</p>
             *
             * @param mediator a reference to the <code>IMediator</code> instance
             */
            virtual void registerMediator(IMediator* mediator);

            /**
             * Retrieve an <code>IMediator</code> from the <code>View</code>.
             *
             * @param mediator_name the name of the <code>IMediator</code> instance to retrieve.
             * @return the <code>IMediator</code> instance previously registered with the given <code>mediator_name</code>.
             */
            virtual IMediator const& retrieveMediator(std::string const& mediator_name) const;

            /**
             * Retrieve an <code>IMediator</code> from the <code>View</code>.
             *
             * @param mediator_name the name of the <code>IMediator</code> instance to retrieve.
             * @return the <code>IMediator</code> instance previously registered with the given <code>mediator_name</code>.
             */
            virtual IMediator& retrieveMediator(std::string const& mediator_name);

            /**
             * Remove an <code>IMediator</code> from the <code>View</code>.
             *
             * @param mediator_name name of the <code>IMediator</code> instance to be removed.
             * @return the <code>IMediator</code> that was removed from the <code>View</code>
             */
            virtual IMediator* removeMediator(std::string const& mediator_name);

            /**
             * Check if a Mediator is registered or not
             *
             * @param mediator_name
             * @return whether a Mediator is registered with the given <code>mediator_name</code>.
             */
            virtual bool hasMediator(std::string const& mediator_name) const;

            /**
             * List all names of mediator
             *
             * @return the aggregate container of <code>mediator_name</code>.
             */
            virtual MediatorNames listMediatorNames(void) const;

            /**
             * Remove an IView instance
             *
             * @param key of IView instance to remove
             */
            static void removeView(std::string const& key);

            /**
             * Virtual destructor.
             */
            virtual ~View(void);
        };
    }
}

#endif /* __PUREMVC_CORE_VIEW_HPP__ */
