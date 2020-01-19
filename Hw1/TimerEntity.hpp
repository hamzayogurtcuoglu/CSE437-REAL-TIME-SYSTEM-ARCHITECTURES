#ifndef TIMERENTITY
#define TIMERENTITY

#include "ITimer.hpp"
#include <ctime>
#include <ratio>

using namespace std;

    class TimerEntity
	{
        public:
            Timepoint timepoint;
            Timepoint last;
            TPredicate predicateFunction;	
            Millisecs period;
            TTimerCallback cb;
            int timerType;	
            bool active = true;
            TimerEntity(const Timepoint &last,const Timepoint &tp, const TTimerCallback &cb);
            TimerEntity(const Timepoint &last,const Millisecs & period, const TTimerCallback &cb);
            TimerEntity(const Timepoint &last,const Timepoint &tp, const Millisecs & period, const TTimerCallback &cb);
            TimerEntity(const Timepoint &last,const TPredicate &pred, const Millisecs & period, const TTimerCallback &cb);
            ~TimerEntity();
	};



#endif