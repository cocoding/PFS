#ifndef _H_REACTOR
#define _H_REACTOR
#include<vector.h>
#include"event.h"
class Reactor
{
	public:
	Reactor(Poll &_poll);
	int RegisterEvent(EventHandler*event_handler);//如果出现多个进行同时对调用这个函数的话怎么办呢
//	void HandleTimer();//这里是处理的event的timer的问题
	void Poll();//while(1);
	void UnRegisterEvent(EventHandler*event_handler);// 这里如何删除还是有点问题的
	private:
	ePoll &poll;//这里面返回的时候是通过处理event_handler中的status来的
	//这里得需要对event_list进行加锁的工作
	void HandleEvents();
//	bool HandleTime();//这个函数名视乎要该，IsEventTimerOut()
	pthread_cond_t event_cond;
	pthread_mutex event_mutex;
	std::vector<EventHandler *> event_list;
}

class ePoll//这里有必要继承自其他的baseClass吗//这里代表的是一种方式
{
	public:
		ePoll(int fd_num);
		//默认构造函数
		void Poll(vector<EventHandler *>&event_list);//这里是个引用
	private:
		int fd_num;
}



#endif
