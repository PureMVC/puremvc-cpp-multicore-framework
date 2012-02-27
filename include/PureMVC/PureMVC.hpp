//  pure_mvc.hpp
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#if !defined(__PUREMVC_HPP__)
#define __PUREMVC_HPP__

#if (defined(_WIN32) || defined(_WIN64)) && (defined(_DLL) || defined(USE_DLL))
    #if defined(PUREMVC_API_EXPORT)
        #define PUREMVC_API __declspec(dllexport)
    #elif !defined(PUREMVC_NO_IMPORT)
        #define PUREMVC_API __declspec(dllimport)
    #endif
#else
    #if defined(__GNUC__) || defined(__MINGW32__)
        #define PUREMVC_API
    #else
        #define PUREMVC_API
    #endif
#endif

//
// Automatically link PureMVC library.
//
#if defined(_MSC_VER) || defined(__CODEGEARC__) || defined(__BORLANDC__) || defined(__INTEL_COMPILER) || defined(__DMC__)
    #if !defined(PUREMVC_API_EXPORT)
        #if defined(__MSVC_RUNTIME_CHECKS) && !defined(_DEBUG) && !defined(DEBUG)
        #pragma message("Using the /RTC option without specifying a debug runtime will lead to linker errors")
        #pragma message("Hint: go to the code generation options and switch to one of the debugging runtimes")
        #error "Incompatible build options"
        #endif
        #if !defined(PUREMVC_NO_AUTO_IMPORT)
            #if defined(_DLL) || defined(USE_DLL)
                #if defined(_DEBUG) || defined(DEBUG)
                    #pragma comment(lib, "PureMVCddll.lib")
                #else
                    #pragma comment(lib, "PureMVCdll.lib")
                #endif
            #else
                #if defined(_DEBUG) || defined(DEBUG)
                    #pragma comment(lib, "PureMVCd.lib")
                #else
                    #pragma comment(lib, "PureMVC.lib")
                #endif
            #endif
        #endif
    #endif
#endif

// Macro support R-Value for C++0x
#if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 4))
#if defined (__GXX_EXPERIMENTAL_CXX0X__)
#define PUREMVC_USES_RVALUE
#else
#define PUREMVC_USES_TR1
#endif
#endif 

#if (__BORLANDC__ >= 0x599)
#pragma defineonoption PUREMVC_CODEGEAR_0X_SUPPORT -Ax
#endif

#if defined( PUREMVC_CODEGEAR_0X_SUPPORT ) && (__BORLANDC__ >= 0x613)
#define PUREMVC_USES_RVALUE
#endif

#if (__BORLANDC__ >= 0x613)
#define PUREMVC_USES_TR1
#endif

#if _MSC_VER >= 1600
#define PUREMVC_USES_RVALUE
#define PUREMVC_USES_TR1
#endif

#if (!(defined(_WIN32) || defined(_WIN64)) && defined(__STDC_HOSTED__) && __STDC_HOSTED__) || defined(__GXX_EXPERIMENTAL_CPP0X__)
#define PUREMVC_INTEL_STDCXX0X
#endif
#if defined(_MSC_VER) && (_MSC_VER >= 1600)
#define PUREMVC_INTEL_STDCXX0X
#endif

#if defined(__INTEL_COMPILER)
#  define PUREMVC_INTEL_CXX_VERSION __INTEL_COMPILER
#elif defined(__ICL)
#  define PUREMVC_INTEL_CXX_VERSION __ICL
#elif defined(__ICC)
#  define PUREMVC_INTEL_CXX_VERSION __ICC
#elif defined(__ECC)
#  define PUREMVC_INTEL_CXX_VERSION __ECC
#endif

#if defined(PUREMVC_INTEL_STDCXX0X) && (PUREMVC_INTEL_CXX_VERSION >= 1200)
#define PUREMVC_USES_RVALUE
#define PUREMVC_USES_TR1
#endif

#if defined(_MSC_VER) && _MSC_VER < 1300
namespace std {
    typedef unsigned long size_t;
}
#endif

namespace PureMVC
{
    /**
     *  Unique lock helper
     */
    template<typename _Lockable>
    class UniqueLock
    {
    private:
        _Lockable& _lockable;
    private:
        UniqueLock(UniqueLock const&);
        UniqueLock& operator=(UniqueLock const&);
    public:
        /**
         * Construct <c>UniqueLock</c> with lockable target.
         *
         * @param lockable the target to lock.
         */
        explicit UniqueLock(_Lockable& lockable)
            : _lockable(lockable)
        {
            _lockable.lock();
        }

        /**
         * Release lock.
         */
        ~UniqueLock(void)
        {
            _lockable.unlock();
        }
    };

    /**
     * Mutex class of PureMVC.
     */
    class PUREMVC_API Mutex
    {
    private:
        void* _mutex;
    public:
        typedef UniqueLock<Mutex> ScopedLock;
    public:
        /**
         * Default constructor.
         */
        explicit Mutex(void);
    public:
        /**
         * Locks the mutex. Blocks if the mutex is held by another thread.
         */
        void lock(void);

        /**
         * Tries to lock the mutex. Returns false immediately if the mutex is already held by another thread. Returns true if the mutex was successfully locked.
         */
        bool tryLock(void);

        /**
         * Unlocks the mutex so that it can be acquired by other threads.
         */
        void unlock(void);

        /**
         * Destructor.
         */
        ~Mutex(void);
    };

    /**
     * FastMutex class of PureMVC.
     */
    class PUREMVC_API FastMutex
    {
    private:
        void* _mutex;
    public:
        typedef UniqueLock<FastMutex> ScopedLock;
    public:
        /**
         * Default constructor.
         */
        explicit FastMutex(void);
    public:
        /**
         * Locks the mutex. Blocks if the mutex is held by another thread.
         */
        void lock(void);

        /**
         * Tries to lock the mutex. Returns false immediately if the mutex is already held by another thread. Returns true if the mutex was successfully locked.
         */
        bool tryLock(void);

        /**
         * Unlocks the mutex so that it can be acquired by other threads.
         */
        void unlock(void);

        /**
         * Destructor.
         */
        ~FastMutex(void);
    };
}

#if !defined(__PUREMVC_INCLUDE__)
#define __PUREMVC_INCLUDE__
#include "Interfaces/INotifier.hpp"
#include "Interfaces/IProxy.hpp"
#include "Interfaces/INotification.hpp"
#include "Interfaces/IObserver.hpp"
#include "Interfaces/ICommand.hpp"
#include "Interfaces/IController.hpp"
#include "Interfaces/IModel.hpp"
#include "Interfaces/IMediator.hpp"
#include "Interfaces/IFacade.hpp"
#include "Interfaces/IView.hpp"
#include "Interfaces/IAggregate.hpp"
#include "Interfaces/IIterator.hpp"
#include "Patterns/Observer/Notification.hpp"
#include "Patterns/Observer/Notifier.hpp"
#include "Patterns/Observer/Observer.hpp"
#include "Patterns/Command/SimpleCommand.hpp"
#include "Patterns/Command/MacroCommand.hpp"
#include "Patterns/Command/DelegateCommand.hpp"
#include "Patterns/Proxy/Proxy.hpp"
#include "Patterns/Mediator/Mediator.hpp"
#include "Patterns/Facade/Facade.hpp"
#include "Patterns/Iterator/Iterator.hpp"
#include "Core/Model.hpp"
#include "Core/View.hpp"
#include "Core/Controller.hpp"
#endif

namespace PureMVC
{
    /**
     * Create container of internal cache.
     */
    PUREMVC_API void createCache(void);

    /**
     * Clean all instance from internal cache.
     */
    PUREMVC_API void cleanCache(void);

    using Interfaces::ICommand;
    using Interfaces::INotification;

    /**
     * Thread base PureMVC.
     */
    class PUREMVC_API Thread
    {
    private:
        bool _auto_destroy;
        ICommand* _command;
        mutable FastMutex _mutex;
        void* _thread_handler;
        std::size_t _stack_size;
        Thread& operator=(Thread const&);
    public:
        /**
         * Default constructor.
         *
         * @param destroyable_command to run in thread. 
         * This command will be destroy in Thread's destructor.
         */
        explicit Thread(ICommand* destroyable_command);

        /**
         * Default constructor.
         *
         * @param command to run in thread.
         */
        explicit Thread(ICommand& command);

    public:
        /**
         * Sets the thread's stack size in bytes.
         */
        void setStackSize(std::size_t size);

        /**
         * Returns the thread's stack size in bytes.
         *
         * @return the default stack size is used.
         */
        std::size_t getStackSize() const;

        /**
         * Start thread with notification.
         *
         * @param notification parameter.
         */
        void start(INotification const& notification);

        /**
         * Start thread with notification. 
         *
         * @param destroyable_notification parameter will be destroy by Thread.
         */
        void start(INotification const* destroyable_notification);

        /**
         * Returns true if the thread is running.
         */
        bool isRunning(void) const;

        /**
         * Waits until the thread completes execution.
         */
        void join(void);

        /**
         * Waits for at most the given interval for the thread to complete.
         */
        void join(long milliseconds);

        /**
         * Waits for at most the given interval for the thread to complete.
         */
        bool tryJoin(long milliseconds);

        /**
         * Suspends the current thread for the specified amount of time.
         */
        static void sleep(long milliseconds);

        /**
         * Get current thread id.
         */
        static std::string getCurrentThreadId(void);

        /**
         * Destructor.
         */
        ~Thread();
    };
}

#endif /* __PUREMVC_HPP__ */
