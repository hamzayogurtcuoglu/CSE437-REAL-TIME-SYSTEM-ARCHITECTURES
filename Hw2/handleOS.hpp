


#if defined(_WIN32)    
    #include <windows.h>
    #include <winbase.h>
#endif

using namespace std;


void setOSPriority(std::thread &th, int policy, int priority) {
    #if defined(__linux__)
        sched_param sch_params;
        sch_params.sched_priority = priority;
        if(pthread_setschedparam(th.native_handle(), policy, &sch_params)) {
            std::cerr << "Failed to set Thread scheduling : " << std::strerror(errno) << std::endl;
        }
    #elif defined(_WIN32)

            if(priority<15&&priority>=10)
                priority = 1;
            else if(priority<20&&priority>=15)
                priority = 2;
            else if(priority<25&&priority>=20)
                priority = 3;
            else if(priority<30&&priority>=25)
                priority = 4;
            else if(priority>=30)
                priority = 5;
            else
                priority = 0;
    switch (priority)
            {
                case 5   :  SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);   break;
                case 4   :  SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);         break;
                case 3   :  SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);    break;
                case 2   :  SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_NORMAL);          break;
                case 1   :  SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_BELOW_NORMAL);    break;
                default   :  SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_LOWEST);          break;
            }
            
    #endif
}