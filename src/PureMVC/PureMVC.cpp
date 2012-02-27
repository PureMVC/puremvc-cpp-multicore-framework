//  pure_mvc.cpp
//  PureMVC_C++
//
//  PureMVC Port to C++ by Tang Khai Phuong <phuong.tang@puremvc.org>
//  PureMVC - Copyright(c) 2006-2011 Futurescale, Inc., Some rights reserved.
//  Your reuse is governed by the Creative Commons Attribution 3.0 License
//

#include "Common.hpp"
// 
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <winbase.h>
#include <process.h>
typedef HANDLE puremvc_mutex_t;
typedef CRITICAL_SECTION puremvc_fast_mutex_t;
typedef std::pair<HANDLE, UINT> puremvc_thread_t;
#if defined(__DMC__)
extern "C" WINBASEAPI BOOL WINAPI InitializeCriticalSectionAndSpinCount(LPCRITICAL_SECTION,DWORD);
#endif
#if defined(_MSC_VER) && _MSC_VER < 1300
extern "C" WINBASEAPI BOOL WINAPI InitializeCriticalSectionAndSpinCount(LPCRITICAL_SECTION,DWORD);
extern "C" WINBASEAPI DWORD WINAPI SetCriticalSectionSpinCount(LPCRITICAL_SECTION, DWORD);
extern "C" WINBASEAPI BOOL WINAPI TryEnterCriticalSection(LPCRITICAL_SECTION);
#endif
#else
#include <pthread.h>
#include <errno.h>
#include <sys/time.h>
typedef pthread_mutex_t puremvc_mutex_t;
typedef pthread_mutex_t puremvc_fast_mutex_t;
typedef std::pair<pthread_t, std::pair<bool, pthread_cond_t> > puremvc_thread_t;
#endif

#if defined(__APPLE__)
#define PTHREAD_MUTEX_RECURSIVE_NP PTHREAD_MUTEX_RECURSIVE
#endif

char const __PURE_MVC_DEFAULT_NAME__[] = "PureMVC";

char const __OBSERVER_NAME__[] = "Observer";
InstanceMapObserver puremvc_observer_instance_map;

char const __CONTROLLER_NAME__[] = "Controller";
InstanceMapController puremvc_controller_instance_map;

char const __MODEL_NAME__[] = "Model";
InstanceMapModel puremvc_model_instance_map;

char const __VIEW_NAME__[] = "View";
InstanceMapView puremvc_view_instance_map;

char const __FACADE_NAME__[] = "Facade";
InstanceMapFacade puremvc_facade_instance_map;

void PureMVC::cleanCache(void)
{
    puremvc_facade_instance_map.cleanCache();

    puremvc_view_instance_map.cleanCache();

    puremvc_controller_instance_map.cleanCache();

    puremvc_model_instance_map.cleanCache();

    puremvc_observer_instance_map.cleanCache();
}

void PureMVC::createCache(void)
{
    puremvc_observer_instance_map.createCache();

    puremvc_model_instance_map.createCache();

    puremvc_controller_instance_map.createCache();

    puremvc_view_instance_map.createCache();

    puremvc_facade_instance_map.createCache();
}

Mutex::Mutex(void)
#if defined(_WIN32) || defined(_WIN64)
    : _mutex(NULL)
{
    _mutex = ::CreateMutex((LPSECURITY_ATTRIBUTES) 0, FALSE,(LPCTSTR) 0);
    if (_mutex == NULL)
        throw std::runtime_error("Cannot create mutex!");
#else
{
    register int rc;
    puremvc_mutex_t* mutex = new puremvc_mutex_t();
    pthread_mutexattr_t attr;
    ::pthread_mutexattr_init(&attr);
    ::pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
    if ((rc = ::pthread_mutex_init(mutex, &attr)))
    {
        ::pthread_mutexattr_destroy(&attr);
        std::cerr << strerror(rc) << std::endl;
        throw std::runtime_error("Cannot create mutex!");
    }
    _mutex = mutex;
    ::pthread_mutexattr_destroy(&attr);
#endif
}

void Mutex::lock(void)
{
#if defined(_WIN32) || defined(_WIN64)
    if (::WaitForSingleObject(_mutex, INFINITE) == WAIT_OBJECT_0)
        return;
    throw std::runtime_error("Cannot lock mutex!");
#else
    register int rc;
    puremvc_mutex_t* mutex = (puremvc_mutex_t*)_mutex;
    if ((rc = ::pthread_mutex_lock(mutex)))
    {
        std::cerr << strerror(rc) << std::endl;
        throw std::runtime_error("Cannot lock mutex!");
    }
#endif
}

bool Mutex::tryLock(void)
{
#if defined(_WIN32) || defined(_WIN64)
    switch (::WaitForSingleObject(_mutex, 0)) 
    {
        case WAIT_TIMEOUT:
            return false;
        case WAIT_OBJECT_0:
            return true;
        default:
            throw std::runtime_error("Cannot try lock mutex!");
    }
#else
    register int rc;
    puremvc_mutex_t* mutex = (puremvc_mutex_t*)_mutex;
    if ((rc = ::pthread_mutex_trylock(mutex)) == 0)
        return true;
    if (rc == EBUSY)
        return false;
    std::cerr << strerror(rc) << std::endl;
    throw std::runtime_error("Cannot try lock mutex!");
#endif
#if defined(__DMC__)
    return false;
#endif
}

void Mutex::unlock(void)
{
#if defined(_WIN32) || defined(_WIN64)
    if (!::ReleaseMutex(_mutex))
        throw std::runtime_error("Cannot unlock mutex!");
#else
    register int rc;
    puremvc_mutex_t* mutex = (puremvc_mutex_t*)_mutex;
    if ((rc = ::pthread_mutex_unlock(mutex)))
    {
        std::cerr << strerror(rc) << std::endl;
        throw std::runtime_error("Cannot unlock mutex!");
    }
#endif
}
Mutex::~Mutex(void)
{
#if defined(_WIN32) || defined(_WIN64)
    ::CloseHandle(_mutex);
#else
    puremvc_mutex_t* mutex = (puremvc_mutex_t*)_mutex;
    ::pthread_mutex_destroy(mutex);
    delete mutex;
    _mutex = NULL;
#endif
}


FastMutex::FastMutex(void)
#if defined(_WIN32) || defined(_WIN64)
    : _mutex(NULL)
{
    _mutex = new CRITICAL_SECTION();
    ::InitializeCriticalSectionAndSpinCount((CRITICAL_SECTION*)_mutex, 4000);

#else
    {
    register int rc;
    puremvc_fast_mutex_t* mutex = new puremvc_fast_mutex_t();
    pthread_mutexattr_t attr;
    ::pthread_mutexattr_init(&attr);
    ::pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_NORMAL);
    if ((rc = ::pthread_mutex_init(mutex, &attr)))
    {
        ::pthread_mutexattr_destroy(&attr);
        std::cerr << strerror(rc) << std::endl;
        throw std::runtime_error("Cannot create mutex!");
    }
    _mutex = mutex;
    ::pthread_mutexattr_destroy(&attr);
#endif
}

void FastMutex::lock(void)
{
    puremvc_fast_mutex_t* mutex = (puremvc_fast_mutex_t*)_mutex;
#if defined(_WIN32) || defined(_WIN64)
	EnterCriticalSection(mutex);
#else
    register int rc;
    if ((rc = ::pthread_mutex_lock(mutex)))
    {
        std::cerr << strerror(rc) << std::endl;
        throw std::runtime_error("Cannot lock mutex!");
    }
#endif
}

bool FastMutex::tryLock(void)
{
    puremvc_fast_mutex_t* mutex = (puremvc_fast_mutex_t*)_mutex;
#if defined(_WIN32) || defined(_WIN64)
    return ::TryEnterCriticalSection(mutex) != 0;
#else
    register int rc;
    if ((rc = ::pthread_mutex_trylock(mutex)) == 0)
        return true;
    if (rc == EBUSY)
        return false;
    std::cerr << strerror(rc) << std::endl;
    throw std::runtime_error("Cannot try lock mutex!");
#endif
#if defined(__DMC__)
    return false;
#endif
}

void FastMutex::unlock(void)
{
    puremvc_fast_mutex_t* mutex = (puremvc_fast_mutex_t*)_mutex;
#if defined(_WIN32) || defined(_WIN64)
	LeaveCriticalSection(mutex);
#else
    register int rc;
    if ((rc = ::pthread_mutex_unlock(mutex)))
    {
        std::cerr << strerror(rc) << std::endl;
        throw std::runtime_error("Cannot unlock mutex!");
    }
#endif
}

FastMutex::~FastMutex(void)
{
    if (_mutex == NULL) return;
    puremvc_fast_mutex_t* mutex = (puremvc_fast_mutex_t*)_mutex;
#if defined(_WIN32) || defined(_WIN64)
    ::DeleteCriticalSection(mutex);
#else
    ::pthread_mutex_destroy(mutex);
#endif
    delete mutex;
    _mutex = NULL;
}

Thread::Thread(ICommand& command)
    : _auto_destroy(false)
    , _command(&command)
#if defined(_WIN32) || defined(_WIN64)
    , _thread_handler(new puremvc_thread_t((HANDLE)NULL, 0))
#else
    , _thread_handler(new puremvc_thread_t())
#endif
    , _stack_size(0)
{
#if !defined(_WIN32) && !defined(_WIN64)
    puremvc_thread_t* thread = (puremvc_thread_t*)_thread_handler;
    thread->second.first = false;
    ::pthread_cond_init(&thread->second.second, NULL);
#endif
}

Thread::Thread(ICommand* destroyable_command)
    : _auto_destroy(true)
    , _command(destroyable_command)
#if defined(_WIN32) || defined(_WIN64)
    , _thread_handler(new puremvc_thread_t((HANDLE)NULL, 0))
#else
    , _thread_handler(new puremvc_thread_t())
#endif
    , _stack_size(0)
{
    if (_command == NULL)
        throw std::runtime_error("Command parameter is null.");

#if !defined(_WIN32) && !defined(_WIN64)
    puremvc_thread_t* thread = (puremvc_thread_t*)_thread_handler;
    thread->second.first = false;
    ::pthread_cond_init(&thread->second.second, NULL);
#endif
}
void Thread::start(INotification const& notification)
{
        if (isRunning())
        throw std::runtime_error("Thread is started!");

    FastMutex::ScopedLock _(_mutex);

    struct ThreadEntry {
#if defined(_WIN32) || defined(_WIN64)
        static DWORD WINAPI action(LPVOID param_data) {
#else
        static void* action(void* param_data) {
            ::pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
#endif
            void** data = (void**)param_data;
            ICommand* command = (ICommand*)data[0];
            INotification* notification = (INotification*)data[1];

            try
            {
                command->execute(*notification);
            }
            catch(std::exception const* ex)
            {
            	std::cerr << ex->what() << std::endl;
                delete ex;
            }
            catch(std::exception const& ex)
            {
            	std::cerr << ex.what() << std::endl;
            }
            catch(...)
            {
                std::cerr << "Cannot handle exception from thread." << std::endl;
            }

#if defined(_WIN32) || defined(_WIN64)
            delete[] data;
            return S_OK;
#else
            PureMVC::FastMutex::ScopedLock _(*(PureMVC::FastMutex*)data[2]);
            std::pair<bool, pthread_cond_t>* run_cond = (std::pair<bool, pthread_cond_t>*) data[3];
            pthread_cond_signal(&run_cond->second);
            run_cond->first = false;
            delete[] data;
            return NULL;
#endif
        }
    };

    void** data = new void*[4];
    data[0] = _command;
    data[1] = const_cast<INotification*>(&notification);
    data[2] = &_mutex;
   
    puremvc_thread_t* thread = (puremvc_thread_t*)_thread_handler;

#if defined(_WIN32) || defined(_WIN64)
    data[3] = NULL;
    thread->first = ::CreateThread(NULL,
        _stack_size, &ThreadEntry::action, data, 0, (DWORD*)&thread->second);
    if (!_thread_handler)
    {
        delete[] data;
        throw std::runtime_error("Cannot create thread!");
    }
#else
    data[3] = &thread->second;
    pthread_attr_t attributes;
    ::pthread_attr_init(&attributes);
    register int rc;
    if (_stack_size != 0 )
    {
        if ((rc = ::pthread_attr_setstacksize(&attributes, _stack_size)))
        {
            ::pthread_attr_init(&attributes);
            std::cerr << strerror(rc) << std::endl;
            delete[] data;
            throw std::runtime_error("Cannot set thread stack size!");
        }
    }
    thread->second.first = true;
    if ((rc = ::pthread_create(&thread->first, &attributes, &ThreadEntry::action, data)))
    {
        ::pthread_attr_init(&attributes);
        std::cerr << strerror(rc) << std::endl;
        thread->second.first = false;
        delete[] data;
        std::runtime_error("Cannot start thread!");
    }
    ::pthread_attr_init(&attributes);
#endif
}

void Thread::start(INotification const* destroyable_notification)
{
    if (destroyable_notification == NULL)
        throw std::runtime_error("Notification parameter is null.");

    if (isRunning())
    {
        delete destroyable_notification;
        throw std::runtime_error("Thread is started!");
    }
    FastMutex::ScopedLock _(_mutex);

    struct ThreadEntry {
#if defined(_WIN32) || defined(_WIN64)
        static DWORD WINAPI action(LPVOID param_data) {
#else
        static void* action(void* param_data) {
            ::pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
#endif
            void** data = (void**)param_data;
            ICommand* command = (ICommand*)data[0];
            INotification* notification = (INotification*)data[1];

            try
            {
                command->execute(*notification);
            }
            catch(std::exception const* ex)
            {
                std::cerr << ex->what() << std::endl;
                delete ex;
            }
            catch (std::exception const& ex)
            {
                std::cerr << ex.what() << std::endl;
            }
            catch(...)
            {
                std::cerr << "Cannot handle exception from thread." << std::endl;
            }
            delete notification;
#if defined(_WIN32) || defined(_WIN64)
            delete[] data;
            return S_OK;
#else
            PureMVC::FastMutex::ScopedLock _(*(PureMVC::FastMutex*)data[2]);
            std::pair<bool, pthread_cond_t>* run_cond = (std::pair<bool, pthread_cond_t>*) data[3];
            pthread_cond_signal(&run_cond->second);
            run_cond->first = false;
            delete[] data;
            return NULL;
#endif
        }
    };

    void** data = new void*[4];
    data[0] = _command;
    data[1] = const_cast<INotification*>(destroyable_notification);
    data[2] = &_mutex;
    puremvc_thread_t* thread = (puremvc_thread_t*)_thread_handler;

#if defined(_WIN32) || defined(_WIN64)
    data[3] = NULL;
    thread->first = ::CreateThread(NULL,
        _stack_size, &ThreadEntry::action, data, 0, (DWORD*)&thread->second);
    if (!_thread_handler)
    {
        delete destroyable_notification;
        delete[] data;
        throw std::runtime_error("Cannot create thread!");
    }
#else
    data[3] = &thread->second;
    pthread_attr_t attributes;
    ::pthread_attr_init(&attributes);
    register int rc;
    if (_stack_size != 0 )
    {
        if ((rc = ::pthread_attr_setstacksize(&attributes, _stack_size)))
        {
            ::pthread_attr_init(&attributes);
            std::cerr << strerror(rc) << std::endl;
            delete destroyable_notification;
            delete[] data;
            throw std::runtime_error("Cannot set thread stack size!");
        }
    }
    thread->second.first = true;
    if ((rc = ::pthread_create(&thread->first, &attributes, &ThreadEntry::action, data)))
    {
        ::pthread_attr_init(&attributes);
        std::cerr << strerror(rc) << std::endl;
        delete destroyable_notification;
        thread->second.first = false;
        delete[] data;
        std::runtime_error("Cannot start thread!");
    }
    ::pthread_attr_init(&attributes);
#endif
}

bool Thread::isRunning(void) const
{
    puremvc_thread_t* thread = (puremvc_thread_t*)_thread_handler;

#if defined(_WIN32) || defined(_WIN64)
    if (thread->first == NULL) return false;
    FastMutex::ScopedLock _(_mutex);
    if (thread->first == NULL) return false;

    DWORD ec = 0;
    return ::GetExitCodeThread(thread->first, &ec) && ec == STILL_ACTIVE;
#else
    FastMutex::ScopedLock _(_mutex);
    return thread->second.first;
#endif
}

void Thread::join(void)
{
    if (!isRunning()) return;

    puremvc_thread_t* thread = (puremvc_thread_t*)_thread_handler;

#if defined(_WIN32) || defined(_WIN64)

    if (thread->first == NULL) return;
    FastMutex::ScopedLock _(_mutex);
    if (thread->first == NULL) return;

    switch (::WaitForSingleObject(thread->first, INFINITE))
    {
    case WAIT_OBJECT_0:
        if (::CloseHandle(thread->first))
            thread->first = NULL;
        else
            throw std::runtime_error("Cannot close thread handle!");
        return;
    default:
        throw std::runtime_error("Cannot join thread!");
    }
#else
    register int rc;
    if ((rc = ::pthread_join(thread->first, NULL)))
    {
        std::cerr << strerror(rc) << std::endl;
        throw std::runtime_error("Cannot join thread!");
    }
    thread->second.first = false;
#endif
}

void Thread::join(long milliseconds)
{
    if (!tryJoin(milliseconds))
        throw std::runtime_error("Join thread timeout!");
}

void Thread::sleep(long milliseconds)
{
#if defined(_WIN32) || defined(_WIN64)
    ::Sleep(DWORD(milliseconds));
#else
    ::usleep(milliseconds * 1000);
#endif
}

bool Thread::tryJoin(long milliseconds)
{
    if (!isRunning()) return true;


    puremvc_thread_t* thread = (puremvc_thread_t*)_thread_handler;

#if defined(_WIN32) || defined(_WIN64)

    if (thread->first == NULL) return true;
    FastMutex::ScopedLock _(_mutex);
    if (thread->first == NULL) return true;

    switch (::WaitForSingleObject(thread->first, milliseconds + 1))
    {
        case WAIT_TIMEOUT: return false;
        case WAIT_OBJECT_0:
            if (::CloseHandle(thread->first))
                thread->first = NULL;
            else
                throw std::runtime_error("Cannot close thread handle!");
            return true;
    default:
        throw std::runtime_error("Cannot join thread!");
    }
#else
    register int rc;
    struct timespec   ts;
    struct timeval    tp;
    if ((rc = ::gettimeofday(&tp, NULL)))
    {
        std::cerr << strerror(rc) << std::endl;
        throw std::runtime_error("Cannot calculate time!");
    }

    ts.tv_sec  = tp.tv_sec + milliseconds / 1000;
    ts.tv_nsec = tp.tv_usec*1000 + (milliseconds % 1000)*1000000;
    if (ts.tv_nsec >= 1000000000)
    {
        ts.tv_nsec -= 1000000000;
        ts.tv_sec++;
    }

    FastMutex::ScopedLock _(_mutex);

    rc = ::pthread_cond_timedwait(&thread->second.second, *(puremvc_mutex_t**)&_mutex, &ts);
    /* If the wait timed out, in this example, the work is complete, and   */
    /* the thread will end.                                                */
    /* In reality, a timeout must be accompanied by some sort of checking  */
    /* to see if the work is REALLY all complete. In the simple example    */
    /* we will just go belly up when we time out.                          */
    if (rc == ETIMEDOUT)
        return false;
    return true;
#endif
#if defined(__DMC__)
    return false;
#endif
}

std::string Thread::getCurrentThreadId(void)
{
    std::stringstream ss;
#if defined(_WIN32) || defined(_WIN64)
    ss << ::GetCurrentThreadId();
#else
    ss << ::pthread_self();
#endif
    return ss.str();
}

Thread::~Thread()
{
    try
    {
        join();
    }
    catch (...)
    { }

    puremvc_thread_t* thread = (puremvc_thread_t*)_thread_handler;
#if !defined(_WIN32) && !defined(_WIN64)
    ::pthread_cond_destroy(&thread->second.second);
#endif
    delete thread;
    _thread_handler = NULL;

    if (_command != NULL && _auto_destroy)
        delete _command;
    _command = NULL;
}

ICommand::~ICommand(void) { }
IController::~IController(void) { }
IFacade::~IFacade(void) { }
IMediator::~IMediator(void) { }
IModel::~IModel(void) { }
INotification::~INotification(void) { }
INotifier::~INotifier(void) { }
IObserver::~IObserver(void) { }
IProxy::~IProxy(void) { }
IView::~IView(void) { }

#if defined (PURE_MVC_CREATE_CACHE)
#if defined(_MSC_VER)
    #define CCALL __cdecl
    #pragma section(".CRT$XCU", read)
    #define INITIALIZER(f)                                          \
    static void __cdecl f(void);                                    \
    __declspec(allocate(".CRT$XCU")) void (__cdecl*f##_)(void) = f; \
    static void __cdecl f(void)
#elif defined(__GNUC__) || defined(__MINGW32__)
    #define CCALL
    #define INITIALIZER(f)                             \
    static void f(void) __attribute__((constructor));  \
    static void f(void)
#elif defined(__BORLANDC__) || defined(__CODEGEARC__)
    #define CCALL __cdecl
    #define INITIALIZER(f) \
    static void f(void)
#endif

static void CCALL destructPureMVC(void)
{
    try
    {
         cleanCache();
    }
    catch (std::exception const& ex)
    {
        std::cerr << ex.what();    
    }
}

INITIALIZER(constructPureMVC)
{
#if defined(__BORLANDC__) || defined(__CODEGEARC__)
#pragma startup constructPureMVC
#endif
    try
    {
        createCache();
    }
    catch (std::exception const& ex)
    {
        std::cerr << ex.what();    
    }
    std::atexit(destructPureMVC);
}
#endif

#if defined(PUREMVC_API_EXPORT)
#if defined (_MSC_VER)
BOOL WINAPI DllMain(HINSTANCE /* hinstDLL */, DWORD fdwReason, PVOID /* lpReserved */)
{
    // Perform actions based on the reason for calling.
    switch( fdwReason ) 
    {
    case DLL_PROCESS_ATTACH:
#if defined(_DEBUG) || defined(DEBUG)
        std::cout << "New process attaches PureMVC library!" << std::endl;
#endif
        try
        {
            createCache();
        }
        catch (std::exception const& ex)
        {
            std::cerr << ex.what();
            return FALSE;
        }
        return TRUE;
    case DLL_THREAD_ATTACH:
#if defined(_DEBUG) || defined(DEBUG)
        std::cout << "New thread attaches PureMVC library!" << std::endl;
#endif
        break;

    case DLL_THREAD_DETACH:
#if defined(_DEBUG) || defined(DEBUG)
       std::cout << "PureMVC library is detached by thread!" << std::endl;
#endif
        break;

    case DLL_PROCESS_DETACH:
#if defined(_DEBUG) || defined(DEBUG)
        std::cout << "PureMVC library is detached by process!" << std::endl;
#endif
        try
        {
            cleanCache();
        }
        catch (std::exception const& ex)
        {
            std::cerr << ex.what();
            return FALSE;
        }
        return TRUE;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}
#elif defined(__CODEGEARC__) || defined(__BORLANDC__)
BOOL WINAPI DllEntryPoint(HINSTANCE /* hinstDLL */, DWORD fdwReason, PVOID /* lpReserved */)
{
    // Perform actions based on the reason for calling.
    switch( fdwReason ) 
    {
    case DLL_PROCESS_ATTACH:
#if defined(_DEBUG) || defined(DEBUG)
        std::cout << "New process attaches PureMVC library!" << std::endl;
#endif
        try
        {
            createCache();
        }
        catch (std::exception const& ex)
        {
            std::cerr << ex.what();
            return FALSE;
        }
        return TRUE;
    case DLL_THREAD_ATTACH:
#if defined(_DEBUG) || defined(DEBUG)
        std::cout << "New thread attaches PureMVC library!" << std::endl;
#endif
        break;

    case DLL_THREAD_DETACH:
#if defined(_DEBUG) || defined(DEBUG)
        std:: cout << "PureMVC library is detached by thread!" << std::endl;
#endif
        break;

    case DLL_PROCESS_DETACH:
#if defined(_DEBUG) || defined(DEBUG)
        std:: cout << "PureMVC library is detached by process!" << std::endl;
#endif
        try
        {
            cleanCache();
        }
        catch (std::exception const& ex)
        {
            std::cerr << ex.what();
            return FALSE;
        }
        return TRUE;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}

#elif defined(__GNUC__) || defined(__MINGW32__)
static void constructPureMVC(void) __attribute__((constructor));
static void destructPureMVC(void)
{
#if defined(_DEBUG) || defined(DEBUG)
   std:: cout << "PureMVC library is detached by process!" << std::endl;
#endif
    try
    {
        cleanCache();
    }
    catch (std::exception const& ex)
    {
        std::cerr << ex.what();    
    }
}

static void constructPureMVC(void)
{
#if defined(_DEBUG) || defined(DEBUG)
    std:: cout << "PureMVC library is detached by process!" << std::endl;
#endif
    std::atexit(destructPureMVC);
    try
    {
        createCache();
    }
    catch (std::exception const& ex)
    {
        std::cerr << ex.what();
    }
}
#endif
#endif
