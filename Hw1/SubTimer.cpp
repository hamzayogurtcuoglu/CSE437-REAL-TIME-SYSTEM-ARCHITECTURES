#include "SubTimer.hpp"
#include "ITimer.hpp"
#include <ctime>
#include <ratio>
#include "TimerEntity.hpp"

using namespace std;
	

	
	SubTimer::SubTimer() {
      	th = thread([=]()
        {
            while (true) {
				if (processed)
				{	//thread sleep until minimum coming time of a timer				
					std::this_thread::sleep_for(std::chrono::duration<double>(minTime(timerArray)));
					
				 	std::chrono::duration<double> diff;
					//if min timer is first type timer. calling callback and passive
					if (timerArray[processedTimer]->timerType == 1)
					{
						timerArray[processedTimer]->cb();
						timerArray[processedTimer]->active = false;	
						diff = 	CLOCK::now() - timerArray[processedTimer]->timepoint;
					}//if min remaining timer is second type.We will call periodically.
					else if(timerArray[processedTimer]->timerType == 2)
					{
						timerArray[processedTimer]->cb();
						diff = (timerArray[processedTimer]->last + 
								timerArray[processedTimer]->period ) - CLOCK::now();

						timerArray[processedTimer]->last = CLOCK::now();

					}else if(timerArray[processedTimer]->timerType == 3)
					{
						timerArray[processedTimer]->cb();

						diff = (timerArray[processedTimer]->last + 
								timerArray[processedTimer]->period ) - CLOCK::now();
						
						timerArray[processedTimer]->last = CLOCK::now();
						//if timer is running until timepoint.Then inactive. 
						if (CLOCK::now()>=timerArray[processedTimer]->timepoint){
							timerArray[processedTimer]->active = false;	
						}
					}else
					{	//predicate is false not calling timer if type of timer is fourth
						if (timerArray[processedTimer]->predicateFunction())
						{
							timerArray[processedTimer]->cb();
							diff = (timerArray[processedTimer]->last + 
							timerArray[processedTimer]->period ) - CLOCK::now();
							timerArray[processedTimer]->last = CLOCK::now();

						}else
						{	
							diff = (timerArray[processedTimer]->last + 
							timerArray[processedTimer]->period ) - CLOCK::now();
							timerArray[processedTimer]->active = false;	
						}				
					}
					//If the callback is called outside 5 milliseconds’ offset
					//from the registered time point, the timer will report “Deadline error”
					if ((int)(diff.count()*1000)>4)
					{
						cout<<"Deadline error"<<endl;
					
					}else{
					}
	
				}else{
					// class thread is waited when all timers are registered.
					std::unique_lock<std::mutex> lck(m);
					cv.wait(lck,[&]{return processed;});
				}
			}
        });
    }

	SubTimer::~SubTimer(){
		processed = true;
        cv.notify_one();
        th.join();
	}

    void SubTimer::registerTimer(const Timepoint &tp, const TTimerCallback &cb){
			
			auto last = CLOCK::now();
			std::unique_lock<std::mutex> lck(m);
			timerArray[size] = new TimerEntity(last,tp,cb);
			size++;
	}
    void SubTimer::registerTimer(const Millisecs & period, const TTimerCallback &cb){
			
			cb();
			auto last = CLOCK::now();
			std::unique_lock<std::mutex> lck(m);
			timerArray[size] = new TimerEntity(last,period,cb);
			size++;	   	
    }
    void SubTimer::registerTimer(const Timepoint &tp, const Millisecs & period, const TTimerCallback &cb){
			cb();
			auto last = CLOCK::now();
			timerArray[size] = new TimerEntity(last,tp,period,cb);
			size++;  		
    }
    void SubTimer::registerTimer(const TPredicate &pred, const Millisecs & period, const TTimerCallback &cb){
			auto last = CLOCK::now();
			timerArray[size] = new TimerEntity(last,pred,period,cb);
			size++;
    }

	double SubTimer::minTime(TimerEntity ** timerArray){
		auto now = CLOCK::now();
		int i,j;
		std::chrono::duration<double> diff2; 
		double min;	
		
		//finding remaining time of a active timer
		for ( i = 0; (i<this->size); i++)
		{
			if ((timerArray[i]->active))
			{
				if (timerArray[i]->timerType == 1)
				{
					diff2  = ((timerArray[i]->timepoint) - now ); 
				}else{
					diff2  = ((timerArray[i]->last + timerArray[i]->period) - now );	
				}
				processedTimer = i;
				min=diff2.count();
				i++;
				break;
			}	
		}
		//if there is any timer . Finding minimum remaining timer.
		for ( j = i;(j<this->size); j++)
		{	
			if ((timerArray[j]->active))
			{
				if (timerArray[j]->timerType == 1)
				{
					diff2  = ((timerArray[j]->timepoint) - now ); 
				}else{
					diff2  = ((timerArray[j]->last + timerArray[j]->period) - now );	
				}
				if (min>diff2.count()){	
					processedTimer = j;
					min=diff2.count();
				}	
			}
		}
		return min;
	}
