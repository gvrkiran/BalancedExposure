/**********************************************************
 *
 * RFWTimer
 * - measures running time in second
 * - supports three different facilities (clock, rusage, 
 *   and htime); define RFW_USAGE, RFW_CLOCK, or RFW_HTIME
 * - if none is the defined, a very crude heuristic is used
 *   to determine which one is to be used; don't rely on
 *   each to much
 *
 * log:
 *   Mar 24, 2003:
 *     - some formatting 
 *
 *   Mar 17, 2003: 
 *     - class created from ancient "BossaTimer"
 *     - made sure RFW_RUSAGE always includes sys/time.h
 *
 *
 **********************************************************/
#ifndef rfw_timer_h
#define rfw_timer_h

//-----------------------------------------------------
// heuristic to determine which timing facility to use
//-----------------------------------------------------
#ifndef RFW_RUSAGE
#ifndef RFW_CLOCK
#ifndef RFW_HTIME

#ifdef WIN32
	#define RFW_CLOCK
#else 
	#include <sys/time.h>
	#ifdef __GLIBC__
		#define RFW_RUSAGE
	#else 
		#define RFW_HTIME
	#endif
#endif

#endif
#endif
#endif 

#ifdef RFW_RUSAGE
#include <sys/time.h>
#include <sys/resource.h>
#endif

#ifdef RFW_HTIME 
#include <sys/time.h>
#endif

#ifdef RFW_CLOCK
#include <stdio.h>
#include <time.h>
#endif

//------------------
// the class itself
//------------------
class RFWTimer {
	private:
		bool running; //is it running now? (false -> paused)
		double base_time; //time of previous runs since last reset
		double max_time;  //reference time  

	#ifdef RFW_CLOCK 
		double getUserTime();
		double start_time;
	#endif

	#ifdef RFW_HTIME
		long start_time, end_time;
	#endif

	#ifdef RFW_RUSAGE
		struct rusage ru;
		struct timeval start_time, end_time, sample_time;
	#endif
		
		void setBaseTime (double bt); 

		//facility-dependent functions
		double getElapsedTime(); //time since last resume/start
		void startTiming();      //store time for future comparison

	public:
		//basic functions
		RFWTimer (bool start=false);
		double getTime(); //return current time
		double pause();   //pause and return current time
		double resume();  //continue if paused, start if reset; return time before resuming
		double start();   //reset and resume; return time before reset
		double reset();   //reset timer and pause (at zero); return time before reset

		//auxiliary functions
		void setMaxTime (double mt);
		double getMaxTime();
		double getTimeToExpire();
		bool isTimeExpired ();
};

#endif
