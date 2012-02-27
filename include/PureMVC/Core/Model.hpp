//  Model.hpp
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__PUREMVC_CORE_MODEL_HPP__)
#define __PUREMVC_CORE_MODEL_HPP__

// STL include
#include <string>
#include <exception>
#include <stdexcept>
#include <cassert>
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

#include "../Interfaces/IModel.hpp"
#include "../Interfaces/IProxy.hpp"
#include "../Patterns/Iterator/Iterator.hpp"

namespace PureMVC
{
    namespace Core
    {
        using Interfaces::IModel;
        using Interfaces::IProxy;
        using Interfaces::IAggregate;
        using Interfaces::IIterator;

        /**
         * A Multiton <code>IModel</code> implementation.
         *
         * <P>
         * In PureMVC, the <code>Model</code> class provides
         * access to model objects (Proxies) by named lookup.
         *
         * <P>
         * The <code>Model</code> assumes these responsibilities:</P>
         *
         * <UL>
         * <LI>Maintain a cache of <code>IProxy</code> instances.</LI>
         * <LI>Provide methods for registering, retrieving, and removing
         * <code>IProxy</code> instances.</LI>
         * </UL>
         *
         * <P>
         * Your application must register <code>IProxy</code> instances
         * with the <code>Model</code>. Typically, you use an
         * <code>ICommand</code> to create and register <code>IProxy</code>
         * instances once the <code>Facade</code> has initialized the Core
         * actors.</p>
         *
         * @see Patterns/Proxy/Proxy.hpp PureMVC::Patterns::Proxy
         * @see Interfaces/IProxy.hpp PureMVC::Interfaces::IProxy
         */
        class PUREMVC_API Model : public virtual IModel
        {
        protected:
#if defined(PUREMVC_USES_TR1)
            typedef std::tr1::unordered_map<std::string, IProxy*> ProxyMap;
#else
            typedef std::map<std::string, IProxy*> ProxyMap;
#endif
        protected:
            /**
             * Define iterator converter for getting proxy name only.
             */
            struct IteratorConverter
#if !defined(__DMC__) // The C++ compiler of Digital Mars cannot resolve this case
                : public std::unary_function<ProxyMap::const_iterator, ProxyMap::key_type> 
#endif          
            {
                /**
                 * Converting operator.
                 *
                 * @param iterator the iterator of internal container.
                 * @return the name of proxy inside iterator.
                 */
                ProxyMap::key_type const& operator()(ProxyMap::const_iterator const& iterator) const;
            };
            /**
             * Define iterator range of internal container.
             */
            struct IteratorRange {
                /**
                 * Get begin point.
                 *
                 * @return the begin of iterator.
                 */
                ProxyMap::const_iterator begin(ProxyMap const* const& iterator) const;
                /**
                 * Get end point.
                 *
                 * @return the end of iterator.
                 */
                ProxyMap::const_iterator end(ProxyMap const* const& iterator) const;
            };
        public:
            static char const* const DEFAULT_KEY;
        protected:
            // Message Constants
            static char const* const MULTITON_MSG;
            // The Multiton Key for this Core
            std::string const _multiton_key;
            // Mapping of proxyNames to IProxy instances
            ProxyMap _proxy_map;
            // Synchronous access
            mutable FastMutex _synchronous_access;
        private:
            Model(Model const&);
            Model(IModel const&);
            Model& operator=(Model const&);
            Model& operator=(IModel const&);
        protected:
            static IModel* find(std::string const& key);
            static void insert(std::string const& key, IModel* model);
        public:
            /**
             * Constructor.
             *
             * <P>
             * This <code>IModel</code> implementation is a Multiton,
             * so you should not call the constructor
             * directly, but instead call the static Multiton
             * Factory method <code>Model.getInstance( multitonKey )</code>
             *
             * @throws Error Error if instance for this Multiton key instance has already been constructed
             *
             */
            explicit Model(std::string const& key = PureMVC::Core::Model::DEFAULT_KEY);

        protected:
            /**
             * Constructor.
             *
             * <P>
             * Support call virtual method in constructor of base class (<code>Model</code>).
             *
             * Condition: Derived class (class inherit from <code>Model</code>) must implement method: initializeModel
             *
             * Please use this way:
             * <code>
             * 
             * ConcreateModel::ConcreateModel(void)
             * :Model(this)
             * {
             *     // Your code here
             * }
             * </code>
             *
             * Factory method <code>Model::getInstance( key )</code>
             *
             * @throws Error Error if instance for this Multiton key has already been constructed
             *
             */
            template<typename _DerivedType>
            explicit Model(_DerivedType* instance, std::string const& key = PureMVC::Core::Model::DEFAULT_KEY)
                : _multiton_key(key)
            {
                if (find(key))
                    throw std::runtime_error(MULTITON_MSG);
                insert(_multiton_key, this);
                instance->_DerivedType::initializeModel();
            }

            /**
             * Initialize the <code>Model</code> instance.
             *
             * <P>
             * Called automatically by the constructor, this
             * is your opportunity to initialize the Singleton
             * instance in your subclass without overriding the
             * constructor.</P>
             *
             * @return void
             */
            virtual void initializeModel(void);

        public:
            /**
             * <code>Model</code> Multiton Factory method.
             *
             * @return the instance for this Multiton key
             */
            static IModel& getInstance(std::string const& key = PureMVC::Core::Model::DEFAULT_KEY);

            /**
             * Register an <code>IProxy</code> with the <code>Model</code>.
             *
             * @param proxy an <code>IProxy</code> to be held by the <code>Model</code>.
             */
            virtual void registerProxy(IProxy* proxy);

            /**
             * Retrieve an <code>IProxy</code> from the <code>Model</code>.
             *
             * @param proxy_name
             * @return the <code>IProxy</code> instance previously registered with the given <code>proxyName</code>.
             */
            virtual IProxy const& retrieveProxy(std::string const& proxy_name) const;

            /**
             * Retrieve an <code>IProxy</code> from the <code>Model</code>.
             *
             * @param proxy_name
             * @return the <code>IProxy</code> instance previously registered with the given <code>proxyName</code>.
             */
            virtual IProxy& retrieveProxy(std::string const& proxy_name);

            /**
             * Check if a Proxy is registered
             *
             * @param proxy_name
             * @return whether a Proxy is currently registered with the given <code>proxyName</code>.
             */
            virtual bool hasProxy(std::string const& proxy_name) const;

            /**
             * Remove an <code>IProxy</code> from the <code>Model</code>.
             *
             * @param proxy_name name of the <code>IProxy</code> instance to be removed.
             * @return the <code>IProxy</code> that was removed from the <code>Model</code>
             */
            virtual IProxy* removeProxy(std::string const& proxy_name);

            /**
             * List all names of proxy
             *
             * @return the aggregate container of <code>proxy_name</code>.
             */
            virtual ProxyNames listProxyNames(void) const;

            /**
             * Remove an IModel instance
             *
             * @param key of IModel instance to remove
             */
            static void removeModel(std::string const& key);
            
            /**
             * Virtual destructor.
             */
            virtual ~Model(void);
        };
    }
}

#endif /* __PUREMVC_CORE_MODEL_HPP__ */
