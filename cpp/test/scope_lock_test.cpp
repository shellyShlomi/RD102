

#include <pthread.h>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

#include <iostream>

#include "scope_lock.hpp"

static const size_t SIZE(100);

static void *TestAsScope(void *data);
static void *TestAsScopeP(void *data);
static void TestScopeLock();

using ilrd::ScopeLock;

class Mutex
{
public:
    void lock()
    {
        std::cout << "Locked boost::mutex" << std::endl;
    }
    void
    unlock()
    {
        std::cout << "Unlocked boost::mutex" << std::endl;
    }

private:
    boost::mutex mutex;
};

class MutexP
{
public:
    MutexP()
    {
        pthread_mutex_init(&m_lock, NULL);
    }
    ~MutexP()
    {
        pthread_mutex_destroy(&m_lock);
    }
    void lock()
    {
        std::cout << "Locked pthread_mutex_t" << std::endl;
    }
    void
    unlock()
    {
        std::cout << "Unlocked pthread_mutex_t" << std::endl;
    }

private:
    pthread_mutex_t m_lock;
};


int main()
{
    TestScopeLock();
    return (0);
}


static void TestScopeLock()
{
    pthread_t thread = {0};
    pthread_t thread2 = {0};

    pthread_create(&thread, NULL, TestAsScope, (void *)"thread");
    pthread_create(&thread2, NULL, TestAsScope, (void *)"thread2");

    pthread_join(thread, NULL);
    pthread_join(thread2, NULL);

    pthread_t threadP = {0};
    pthread_t threadP2 = {0};

    pthread_create(&threadP, NULL, TestAsScopeP,(void *)"threadP");
    pthread_create(&threadP2, NULL, TestAsScopeP, (void *)"threadP2");

    pthread_join(threadP, NULL);
    pthread_join(threadP2, NULL);

    return;
}


static void *TestAsScopeP(void *data)
{
    MutexP m;

    ScopeLock<MutexP> m_l(&m);

    static int x1 = 0;

    std::cout << x1 << std::endl;
    ++x1;
    return data;
}

static void *TestAsScope(void *data)
{
    Mutex m;

    ScopeLock<Mutex> m_l(&m);

    static int x1 = 0;

    std::cout << x1 << std::endl;
    ++x1;
    return data;
}
