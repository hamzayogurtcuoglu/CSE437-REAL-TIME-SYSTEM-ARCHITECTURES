#ifndef SUBTIMER
#define SUBTIMER

#include "TimerEntity.hpp"
#include<iostream>
#include <thread>
#include <chrono>
#include <functional>
#include "ITimer.hpp"
#include <queue> 
#include <mutex>
#include <condition_variable>

using namespace std;


class SubTimer : public ITimer
{
  public:
      SubTimer();
      ~SubTimer();
      bool getterSize(){return 0!=size;} 
      void registerTimer(const Timepoint &tp, const TTimerCallback &cb);
      void registerTimer(const Millisecs & period, const TTimerCallback &cb);
      void registerTimer(const Timepoint &tp, const Millisecs & period, const TTimerCallback &cb);
      void registerTimer(const TPredicate &pred, const Millisecs & period, const TTimerCallback &cb);
      TimerEntity ** timerArray = new TimerEntity*[100];
      double minTime(TimerEntity ** timerArray);
      int size = 0;
      std::thread th;
      std::mutex m;
      std::condition_variable cv;
      int processedTimer = 0;
      bool processed = false;
};



#endif