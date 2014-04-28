#include"event.h"
#include<iostream>
//Acceptor::Acceptor(SockAddr _listen_addr):EventHandle(-1),listen_address(_listen_addr)
//{
//	InitAcceptor();
	 //SetAlarmTime(_alarm);
//}

extern G_Reactor g_reactor;
LogHandler::LogHandler(Sock sock_fd,TYPE t=LOGGER):EventHandler(sock_fd,t)
{

}
void Acceptor::HandleDropOut()
{ 
	//这里是不会出现掉线的
	//这里是不会出现问题的 
	_exit(3);
}
void LogHandler::HandleDropOut()
{
		g_reactor.Instance()->UnRegisterEvent(this);
}
void LogHandler::HandleRead()
{
		char buffer[100];
		Sock sock_fd=GetSock();
		int i=read(sock_fd,buffer,100);
}
void Acceptor::InitAcceptor()
{
	//SetEventType(ACCEPTOR);//enum 的使用方法不知道是否正确;
	int _sock_fd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in sin;
	sin.sin_family=AF_INET;
	sin.sin_port=htons(listen_address.GetPort());
	inet_pton(AF_INET,listen_address.GetIp().c_str(),&sin.sin_addr);
	if(bind(_sock_fd,(struct sockaddr*)&sin,sizeof(sin))<0)
	{
		std::cout<<"Bind Error"<<std::endl;
			_exit(1);
	}
	if(listen(_sock_fd,1000)<0)
	{

		std::cout<<"listen Error..."<<std::endl;
			_exit(2);
	}
	SetSock(_sock_fd);//这里的setSock的里面向reactor了相应的世界 
	//initAcceptor
}
void Acceptor::HandleRead()
{
		Sock listen_fd=GetSock();
		Sock log_fd=accept(listen_fd,NULL,NULL);
		LogHandler *lg=new LogHandler(log_fd);//这里应该怎样处理呢？？？ 内存没有被释放掉。。？？
		std::cout<<"HandlerRead"<<endl;
}

EventHandler::EventHandler(Sock _fd,TYPE t/*,Time *_alarm_time*/)
{
	type=t;
	//alarm_time=_alarm_time;
	if(_fd!=-1)
	{
		sock_fd=_fd;
		g_reactor.Instance()->RegisterEvent(this);
	}
	else
	sock_fd=-1;
	//alarm_time=_alarm_time;
}
void EventHandler::SetEventType(TYPE t)
{
		type=t;
}
TYPE EventHandler::GetEventType()
{
		return type;
}
int EventHandler::SetSock(Sock _fd)
{
	if(sock_fd!=-1)
		return 0 ;
	sock_fd=_fd;//这里的sock_fd只能设置一次,如果在构造函数中声明了的话就不需要在声明了
	g_reactor.Instance()->RegisterEvent(this);
	return 1;
}
void EventHandler::SetStatus(STATUS _status)
{
	status=_status;
}
STATUS EventHandler::GetStatus()
{
	return status;
}
Sock EventHandler::GetSock()
{
		return sock_fd;
}

