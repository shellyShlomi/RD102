

#include <pthread.h>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <iostream>

#include "scope_lock.hpp"

static const size_t SIZE(100);

using ilrd::ScopeLock;

class MutexP
{
public:
    MutexP(pthread_mutex_t *lock) : m_lock(lock)
    {
        pthread_mutex_init(m_lock, NULL);
        std::cout << "MutexP Ctor" << std::endl;
    }
    ~MutexP()
    {
        pthread_mutex_destroy(m_lock);
        std::cout << "MutexP Dtor" << std::endl;
    }
    void lock()
    {
        pthread_mutex_lock(m_lock);
    }
    void
    unlock()
    {
        pthread_mutex_unlock(m_lock);
    }

private:
    pthread_mutex_t *m_lock;
};

struct Data
{
    MutexP *m_lock;
    boost::mutex *mutex;
    long int val;
};

static long unsigned int x1 = 0;
static long unsigned int x2 = 0;

static void *TestAsScope(void *data);
static void *TestAsScopeP(void *data);
static void TestScopeLock();


int main()
{
    TestScopeLock();
    return (0);
}

static void TestScopeLock()
{
    pthread_mutex_t m_lock;
    boost::mutex mutex;
    MutexP m_p(&m_lock);
    struct Data d_p = {&m_p, 0, -1};
    struct Data d_p2 = {&m_p, 0, -1};
    struct Data d = {0, &mutex, -1};
    struct Data d2 = {0, &mutex, -1};

    long int arr[] = {d.val, d2.val, d_p.val, d_p2.val};

    pthread_t thread = {0};
    pthread_t thread2 = {0};
    pthread_t threadP = {0};
    pthread_t threadP2 = {0};

    pthread_create(&thread, NULL, TestAsScope, (void *)&d);
    pthread_create(&thread2, NULL, TestAsScope, (void *)&d2);
    pthread_create(&threadP, NULL, TestAsScopeP, (void *)&d_p);
    pthread_create(&threadP2, NULL, TestAsScopeP, (void *)&d_p2);

    pthread_join(thread, (void **)(arr));
    pthread_join(thread2, (void **)(arr + 1));
    pthread_join(threadP, (void **)(arr + 2));
    pthread_join(threadP2, (void **)(arr + 3));

    for (size_t i = 0; i < 4; ++i)
    {
        std::cout << (arr[i]) << std::endl;
    }

    return;
}

static void *TestAsScopeP(void *data)
{

    ScopeLock<MutexP> m_l(((struct Data *)data)->m_lock);


    ((struct Data *)data)->val = x1;
    ++x1;

    return (void *)(((struct Data *)data)->val);
}

static void *TestAsScope(void *data)
{
    ScopeLock<boost::mutex> m_l(((struct Data *)data)->mutex);

    ((struct Data *)data)->val = x2;
    ++x2;

    return (void *)(((struct Data *)data)->val);
}
