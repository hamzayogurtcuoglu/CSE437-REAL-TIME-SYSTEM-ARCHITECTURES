#include <mutex>
#include <iostream>
#include <thread>
#include <pthread.h>
#include <cstring>
#include <cstdarg>
#include <stdarg.h>
#include <condition_variable>
#include "handleOS.hpp"

using namespace std;
namespace gtu{
    std::mutex m2;
    std::condition_variable cv2;
    bool checkIn = true;
    int value = 0;
    struct threadInfo
    {
        std::thread::id id;
        int priority = -1;
        bool waiting = false;
    };

    class mutex:public std::mutex
    {
    private:
        bool checkGetIn();
        bool registeredOrNOT();
    public:
        int celling = -1;
        int current = -1;
        std::condition_variable cv;
        std::mutex m;
        bool ready = true;
        std::thread::id id;
        void lock();
        void unlock();
        void registerThread();
        mutex();
        threadInfo * threadInfoArray;
        int size = 0;

    };
    gtu::mutex * mutexArray[100];
    int mutexSize = 0;

    mutex::mutex(){
        threadInfoArray = new threadInfo[10];
        mutexArray[mutexSize] = this;
        mutexSize++;
    }
            std::mutex m8;

    bool mutex::checkGetIn(){
        std::mutex::lock();
        #if defined(__linux__)

                sched_param sch;
                int policy;
                pthread_getschedparam(pthread_self(), &policy, &sch);
        #endif
            bool getIn = true;
            for (int i = 0; i < mutexSize; i++)
            {
                for (int  j = 0; j < mutexArray[i]->size; j++)
                {
                    if (mutexArray[i]->threadInfoArray[j].id == std::this_thread::get_id() )
                    {
                        #if defined(__linux__)
                            if (mutexArray[i]->current>sch.sched_priority&&
                                mutexArray[0]->id != std::this_thread::get_id()&&
                                mutexArray[1]->id != std::this_thread::get_id() )
                            {   
                                    std::mutex::unlock();
                                    return false;
                            }
                        #elif defined(_WIN32)
                            if (mutexArray[i]->current>GetThreadPriority(GetCurrentThread()))
                            {
                                return false;
                            }
                        #endif
                    }
                }
            }

            current = celling;
            std::mutex::unlock();
            
            return true;
    }
    bool mutex::registeredOrNOT(){
        bool registered = false;
        for (int i = 0; i < mutexSize; i++)
        {
            for (int  j = 0; j < mutexArray[i]->size; j++)
            {
                if (mutexArray[i]->threadInfoArray[j].id == std::this_thread::get_id() )
                {
                    registered = true;
                }
            }
        }
        if (!registered)
        {
            throw new std::exception;
        }
        return false;
    }

    void mutex::lock(){
         
        try
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
            registeredOrNOT();
            std::unique_lock<std::mutex> lk(m);
            cv.wait(lk, [&]{    
                return checkGetIn();
            });
        } catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        id = std::this_thread::get_id();
    }

    void mutex::unlock(){
        for (int i = 0; i < size; i++)
        {   
            if(threadInfoArray[i].id == std::this_thread::get_id())
                threadInfoArray[i].priority = -1;
        }
        int max = threadInfoArray[0].priority; 
        for (int i = 0; i < size; i++)
        {   
            if(threadInfoArray[i].priority > max)
                max = threadInfoArray[i].priority ;
        }
        value--;
        current = -1;
        cv.notify_one();
        ready = true;
         
    }
    void mutex::registerThread(){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        threadInfoArray[size].id = std::this_thread::get_id();
        #if defined(__linux__)
                sched_param sch;
                int policy;
                pthread_getschedparam(pthread_self(), &policy, &sch);
                threadInfoArray[size].priority = sch.sched_priority;
                pthread_getschedparam(pthread_self(), &policy, &sch);
                if (celling<sch.sched_priority)
                    celling = sch.sched_priority;
        #elif defined(_WIN32)
                threadInfoArray[size].priority = GetThreadPriority(GetCurrentThread());
                if (celling<threadInfoArray[size].priority)
                    celling = threadInfoArray[size].priority;
        #endif

        size++;


    }
}

