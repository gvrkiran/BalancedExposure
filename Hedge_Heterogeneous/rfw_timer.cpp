/*************************************
 *
 * RFWTimer (used for time measured)
 *
 *************************************/

#include "rfw_timer.h"
#define INFINITE_TIME 10e100

/********************
 * Generic functions
 ********************/

RFWTimer::RFWTimer (bool s) {
	base_time = 0.0;
	max_time = 0.0;
	if (s) start();
	else running = false;
}

double RFWTimer::getTime() {
	if (running) return (getElapsedTime() + base_time);
	else return base_time;
}

double RFWTimer::start() {
	double current = getTime();
	base_time = 0.0;
	startTiming();
	running = true;
	return current;
}

void RFWTimer::setMaxTime (double mt) {max_time = mt;}
double RFWTimer::getMaxTime () {return max_time;}

bool RFWTimer::isTimeExpired () {
	if (getMaxTime() == 0) return false;
	bool time_expired = (getTime() >= getMaxTime());
	return time_expired;
}

double RFWTimer::getTimeToExpire () { //may be negative!
	if (getMaxTime() == 0) return INFINITE_TIME;
	else return (getTime() - getMaxTime());
}

void RFWTimer::setBaseTime (double bt) {base_time = bt;}

double RFWTimer::reset() {
	double current = getTime();
	running = false;
	base_time = 0.0;
	return current;
}

double RFWTimer::pause() {
	base_time = getTime();
	running = false;
	return base_time;
}

double RFWTimer::resume() {
	if (running) return getTime();
	else {
		running = true;
		startTiming();
		return base_time;
	}
}

//------------
// RFW_RUSAGE
//------------

#ifdef RFW_RUSAGE

void RFWTimer::startTiming() {
  getrusage(RUSAGE_SELF, &ru);
  start_time = ru.ru_utime;
}

double RFWTimer::getElapsedTime() {
  double t;
  getrusage(RUSAGE_SELF, &ru);
  end_time = ru.ru_utime;
  if (end_time.tv_usec < start_time.tv_usec){
    end_time.tv_usec += 1000000;
    end_time.tv_sec -= 1;
  }
  t = 100.0*(double)(end_time.tv_sec - start_time.tv_sec) + (double)(end_time.tv_usec - start_time.tv_usec) / (double)10000.0;
  return ((double)t/(double)100);
}

#endif


//-----------
// RFW_CLOCK
//-----------

#ifdef RFW_CLOCK

void RFWTimer::startTiming() {start_time = getUserTime();}

double RFWTimer::getElapsedTime() {
	return (getUserTime() - start_time);
}

double RFWTimer::getUserTime() {
	double msecs = (double) clock() / CLOCKS_PER_SEC;
	if (msecs > 0) return msecs; 
	else return 0.0; //sometimes msecs is -0.000 (go figure...)
}

#endif


/*************
 *RFW_HTIME
 *************/
#ifdef RFW_HTIME

void RFWTimer::startTiming() {start_time = (long)gethrvtime();}

double RFWTimer::getElapsedTime() {
	return (double)(gethrvtime()-start_time)/(double)10e8;
}

#endif
