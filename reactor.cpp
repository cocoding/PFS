#include"Reactor.h"
#include"event.h"
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
					
					vector<EventHandler*>::iterator event_iter=event_list.begin();
						for(event_iter;event_iter<event_list.end();event_iter++)
								{
											event_iter->SetStatus(Wait);
													struct epoll_event *env=(struct epoll_event*)malloc(sizeof(struct epoll_event));//这里这块内存不是很好回收，还是让它使用上面的数组？？
															if(event_iter->GetType()==)//acceptor
																		{
																						env->events=EPOLLIN;
																		}
																	else
															if(event_iter->GetType()==)//reader
																		{
																					  env->events=EPOLLIN|EPOLLET;
																		}
																		env->data.ptr=(void *)event_iter;//这里是必须的
																		Sock sock_fd=event_iter->GetSock();
																		env->data.fd=sock_fd;
																	  epoll_ctl(poll_fd, EPOLL_CTL_ADD,sock_fd,env);
								 }
							int fds=epoll_wait(poll_fd,p_events,even_num,1000);
								for(int i=0;i<fds;i++)
										{
													if(p_events[i].events&EPOLLIN)
																{
																				EventHandler* tmpEvent=static_cast<EventHandler*>p_events[i].data.ptr;
																				tmpEvent->SetStatus(READ);
																				continue;
																}
															else
													if(p_events[i].events&EPOLLRDHUP)
																{
																				EventHandler* tmpEvent=static_cast<EventHandler*>p_events[i].data.ptr;
																				tmpEvent->SetStatus(DEAD);
																				continue;
																}
										}
							delete[] p_events;
									//下面是删除这块内存.上面还有分配的内存不能被删除
									//上面还有分配的内存不能被删除delete[] p_events;
		
}


	

