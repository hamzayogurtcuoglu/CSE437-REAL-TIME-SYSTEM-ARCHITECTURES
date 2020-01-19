#include <iostream>
#include <chrono>
#include <functional>
#include "ITimer.hpp"
#include "SubTimer.hpp"
#include <mutex>
#include <condition_variable>
#include <stdlib.h> 

using namespace std;


int main(void)
{   
    srand(time(0)); 
    const TPredicate predicate = [&]{
        return rand()%2==1;
    };
        
    const  TTimerCallback cb = [&]{
        cout<<"I'm first type timer - 1"<<endl;
    };
    const  TTimerCallback cb2 = [&]{
        cout<<"I'm first type timer - 2"<<endl;
    };  
    const  TTimerCallback cb3 = [&]{
        cout<<"I'm second type timer"<<endl;
    }; 
    const  TTimerCallback cb4 = [&]{
        cout<<"I'm third type timer"<<endl;
    }; 
    const  TTimerCallback cb5 = [&]{
        cout<<"I'm fourth type timer"<<endl;
    }; 
        
    SubTimer timerQueue;
    
    //Type 1
    Millisecs timer1{5000}; // 5second
    auto timePoint = CLOCK::now()+timer1; 
    timerQueue.registerTimer(timePoint,cb);    
    
    //Type 1 Again.
    Millisecs timer1_2{15000}; // 15 second
    auto timePoint2 = CLOCK::now()+timer1_2; 
    timerQueue.registerTimer(timePoint2,cb2);    

    //Type 2 ---> 1.5 second forever 
    Millisecs timer2{1500}; //second
    timerQueue.registerTimer(timer2,cb3);

    //Type 3 ---> 5 second periodically until 20 second timepoint
    Millisecs timer3{2000}; // 2second
    Millisecs timer3a{20000}; // 20second 
    auto timePoint3 = CLOCK::now()+timer3a; 
    timerQueue.registerTimer(timePoint3,timer3,cb4);

    //Type 4 : predicate depends
    Millisecs timer4{2000};
    timerQueue.registerTimer(predicate,timer4 ,cb5);    
    
    return 0;
}