#ifndef _H_TIME
#define _H_TIME
#include<time.h>
class Time//这里需要处理很多时间的问题
{
	public:
	Time();//这里先这样设置吧
	Time(int sec);
	//还没确定使用哪一个类型的参数作为时间的参数
	Time();//这里估计得需要多个构造函数处,如何处理Time()+某个数的情况，这个数代表的时间是小时，分钟还是秒数？？//最好是秒数吧
	bool operator <(Time&);
	{
		//这里如果是sec为-1的情况下代表其不会设置相应的time，也就是不需要到时间调用函数功能
	}
	int month;
	int day;
	int hour;
	int min;
	int sec;
};

class Timer
{
	public:
	Timer();
	Time GetTime();//这两个有点区别吧，一个是RefreshTime后在返回时间的函数一个直接返回时间的函数
	Time Now();
	void RefreshTime();
	private:
		time now_time;
};
//g_timer这个也是单列的模式


//在外面在包装一层的话会比较好

//这里需要有一个得到全局时间的类

#endif
