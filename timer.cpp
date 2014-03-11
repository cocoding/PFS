#include"timer.h"
Timer::Timer()
{
	RefreshTime();
}
void Timer::RefreshTime()
{
  time_t now;
  now = time(0);
  struct tm *tnow = localtime(&now);
  now_time->month= tnow->tm_mon+1;
  now_time->day=tnow->tm_mday;
  now_time->hour=tnow->tm_hour;
  now_time->min=tnow->tm_min;
  now_time->sec=tnow->tm_sec;
}
void Timer::Now()
{
	RefreshTime();
	return now_time;
}
void Timer::GetTime()
{
	return now_time
}

