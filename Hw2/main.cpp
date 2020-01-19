#include <iostream>
#include "threadFunctions.hpp"
#include <mutex>
#include <thread>
#include <chrono>
#include <cstring>
#include <pthread.h>

int main(){

    std::thread t1(oneIncreament), 
                t2(twoIncreament),
                t3(twoDecreament),
                t4(oneDecreament),
                t5(threeDecreament), 
                t6(threeIncreament),
                t7(fourDecreament), 
                t8(fourIncreament);
    setOSPriority(t1, SCHED_FIFO, 12);
    setOSPriority(t2, SCHED_FIFO, 11);
    setOSPriority(t3, SCHED_FIFO, 14);
    setOSPriority(t4, SCHED_FIFO, 13);
    setOSPriority(t5, SCHED_FIFO, 20);
    setOSPriority(t6, SCHED_FIFO, 21);
    setOSPriority(t7, SCHED_FIFO, 24);
    setOSPriority(t8, SCHED_FIFO, 23);
   
    t1.join(); 
    t2.join(); 
    t3.join();
    t4.join();
    t5.join(); 
    t6.join(); 
    t7.join();
    t8.join();

}

