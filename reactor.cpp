#include"Reactor.h"

Reactor::Reactor(Poll &_poll):poll(_poll)
{
	event_cond_t=PTHREAD_COND_INITIALIER;
	event_mutex=PTHREAD_MUTEX_INITIALIER;
}
int Reactor::RegisterEvent(EventHandler*event_handler)
{
	
	event_handler->SetStatus(WAIT);

	pthread_mutex_lock(&event_mutex);
	pthread_cond_wait(&event_cond);

	event_list.append(event_handler);
	
}
int Reactor::Poll()
{
	while(1)//这里没次都会
	{
		poll.Poll(event_list);//这里只是设置相应的标志位就可以了
		HandleEvent();//处理完以后要重新设置相应的,记住了这里还是要改变的因为相应的event可以设置为死掉的
		pthread_cond_signal();//提醒Register的内容
	}
}
int Reactor::UnRegisterEvent(EventHandler *event_handler)
{

}
int Reactor::HandleEvents()
{
	globla_timer.FreshTime();//单列模式
	vector<EventHandler*>::iterator event_iter=event_list.begin();
	for(event_iter;event_iter<event_list.end();event_iter++)
	{
		//下面的是否需要变成为
		STATUS status=event_iter->GetStatus();
		if(status==READ)
		{
			event_iter->HandleRead();//在这里最好是设置好相应的wait 标志 
		}
		if(status==DEAD)
		{
			event_iter->HandleDropOut();
		}
		if(!HandleTime(event_iter))
		{
			event_iter->HandleTimeOut();
		}
		//event_iter->SetStatus(Wait);
	}
}
bool  Reactor::HandleTime(EventHandler *handler)
{
	if(handler->GetTime()>GlobalTimer.GetTime())//调用这个函数需要配合上面35行的代码
		return 0;
	return 1;
}
ePoll::ePoll(int _fd_num)
{
	fd_num=_fd_num;

}

void  ePoll::Poll(vector<EventHandler *>event_list)
{
	vector<EventHandler*>::iterator event_iter=event_list.begin();
	for(event_iter;event_iter<event_list.end();event_iter++)
	{
		struct epoll_event *env=(struct epoll_event*)malloc(sizeof(struct epoll_event));
		if(event_iter->GetEventType()==)//acceptor
		{
			env->events=
		}
		if(event_iter->GetEventType()==)
		{
			env->events=	
		}
			
	}
		
}


	

