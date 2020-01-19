	
 #include "TimerEntity.hpp"   
    
	TimerEntity::TimerEntity(const Timepoint &last,const Timepoint &tp, const TTimerCallback &cb)
	{
        this->last = last;
		this->timepoint = tp;
		this->cb=cb;
		timerType=1;
	}
    TimerEntity::TimerEntity(const Timepoint &last,const Millisecs & period, const TTimerCallback &cb)
	{   this->last = last;
		this->period = period;
		this->cb=cb;
		timerType=2;
	}
    TimerEntity::TimerEntity(const Timepoint &last,const Timepoint &tp, const Millisecs & period, const TTimerCallback &cb)
	{   this->last = last;
		this->timepoint = tp;
		this->cb=cb;
        this->period = period;
		timerType=3;
	}
    TimerEntity::TimerEntity(const Timepoint &last,const TPredicate &pred, const Millisecs & period, const TTimerCallback &cb)
	{   this->last = last;
		this->period = period;
		this->cb=cb;
		this->predicateFunction = pred;
        timerType=4;
	}
	
	TimerEntity::~TimerEntity()
	{
		delete this;
	}