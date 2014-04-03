#include"reactor.h"
#include<iostream>
class EventHandler;
G_Reactor g_reactor;
Reactor::Reactor()
{
}
void Reactor::InitReactor()
{
	event_cond=PTHREAD_COND_INITIALIZER;//??
	event_mutex=PTHREAD_MUTEX_INITIALIZER;
	poll=NULL;

}
	

int Reactor::RegisterEvent(EventHandler* event_handler)
{//这里可能会出现问题，就是如果一开始的时候出现就使用registerEvent的话，会出现问题的/e/////////////
	
	event_handler->SetStatus(WAIT);

//	pthread_mutex_lock(&event_mutex);这里还是不先使用锁了吧，有点问题
//	pthread_cond_wait(&event_cond,&event_mutex);

	event_pending_list.push_back(event_handler);
	
}
void Reactor::SetPoll(ePoll *_poll)
{
	assert(poll==NULL);
	poll=_poll;
}
void Reactor::FreshEventList()
{
	//这里处理的是添加的情况
		 std::vector<EventHandler *>::iterator p_iter=event_pending_list.begin();
		 for(;p_iter<event_pending_list.end();p_iter++)
		 {
			 	event_list.push_back(*p_iter);
		 }
		 event_pending_list.clear();

		 //下面处理的死掉的进程的，但是有个问题就是内存没有被释放.在变量VECTOR的时候删除元素是有问题的 
		 p_iter=event_list.begin();
		 while(p_iter<event_list.end())//这里如果使用
		{
				if((*p_iter)->GetStatus()==DEAD)
					{
							std::cout<<"Event has been leave"<<std::endl;
							EventHandler *freeEvent=*p_iter;
							event_list.erase(p_iter);
							free(freeEvent);//这里是删除
					}
				else 
							p_iter++;
		}
}
void Reactor::Poll()
{
//	assert(poll==NULL);
	while(1)//这里没次都会
	{
		poll->Poll(event_list);//这里只是设置相应的标志位就可以了
		HandleEvents();//处理完以后要重新设置相应的,记住了这里还是要改变的因为相应的event可以设置为死掉的
		//pthread_cond_signal(&event_cond);//提醒Register的内容这里这样写有点问题
		FreshEventList(); 
	}
}
int Reactor::UnRegisterEvent(EventHandler *event_handler)
{
	//这块的代码也是有问题的 
/*	vector<EventHandler*>::iterator event_iter=event_list.begin(); 
	for(;event_iter<event_list.end();event_iter++)
	{
			if((*event_iter)->GetSock()==event_handler->GetSock())
			{
					event_list.erase(event_iter);
					break;
			}
	}
	*/
	event_handler->SetStatus(DEAD);//这里做了重复的工作了
	 
}
void Reactor::HandleEvents()
{
	//globla_timer.FreshTime();//单列模式
	vector<EventHandler*>::iterator event_iter=event_list.begin();
	for(;event_iter<event_list.end();event_iter++)
	{
		//下面的是否需要变成为
		STATUS status=(*event_iter)->GetStatus();
		if(status==READ)
		{
			(*event_iter)->HandleRead();//在这里最好是设置好相应的wait 标志 
		}
		if(status==DEAD)
		{
			(*event_iter)->HandleDropOut(); 
		}
		if(status==WAIT)
			continue;
	/*	if(!HandleTime(event_iter))
		{
			event_iter->HandleTimeOut();
		}*/
		//event_iter->SetStatus(Wait);
	}
}
/*bool  Reactor::HandleTime(EventHandler *handler)
{
	if(handler->GetTime()>GlobalTimer.GetTime())//调用这个函数需要配合上面35行的代码
		return 0;
	return 1;
}*/
ePoll::ePoll()
{
	//this not require nothing;

}

void  ePoll::Poll(vector<EventHandler *>&event_list)
{
		int eventNum=event_list.size();
		int poll_fd=epoll_create(eventNum);
		struct epoll_event *p_events =new epoll_event[eventNum];//这里在哪里进行释放还是个问题
		int event_index=0;	
		vector<EventHandler*>::iterator event_iter=event_list.begin();
		for(;event_iter<event_list.end();event_iter++)
		{ 
					(*event_iter)->SetStatus(WAIT);
		//			struct epoll_event *env=(struct epoll_event*)malloc(sizeof(struct epoll_event));//这里这块内存不是很好回收，还是让它使用上面的数组？？
					if((*event_iter)->GetEventType()==ACCEPTOR)//acceptor
						{
									p_events[event_index].events=EPOLLIN;
						}
						else
					if((*event_iter)->GetEventType()==LOGGER)//reader///////////////
						{
								  p_events[event_index].events=EPOLLIN|EPOLLRDHUP;
						}
						p_events[event_index].data.ptr=(void *)(*event_iter);//这里是必须的
						Sock sock_fd=(*event_iter)->GetSock();
																		//env->data.fd=sock_fd;
						epoll_ctl(poll_fd, EPOLL_CTL_ADD,sock_fd,&(p_events[event_index]));
						event_index++;
		 }
			int fds=epoll_wait(poll_fd,p_events,eventNum,1000);
			for(int i=0;i<fds;i++)
			{
													if(p_events[i].events&EPOLLRDHUP)
													{
																				EventHandler* tmpEvent=static_cast<EventHandler*>(p_events[i].data.ptr);
																				tmpEvent->SetStatus(DEAD);
																				continue;
													}
													if(p_events[i].events&EPOLLIN)
													{
																				EventHandler* tmpEvent=static_cast<EventHandler*>(p_events[i].data.ptr);
																				tmpEvent->SetStatus(READ);
																				continue;
													}
			}
			delete[] p_events;
			return ;
									//下面是删除这块内存.上面还有分配的内存不能被删除
									//上面还有分配的内存不能被删除delete[] p_events;
		
}
