#include"event.h"

Acceptor::Acceptor(SockAddress &_listen_addr/*,Time _alarm=NULL*/):Event_handler(-1,/*_alarm*/),listen_address(_listen_addr)
{
	InitAcceptor();
	 //SetAlarmTime(_alarm);
}
void Acceptor::InitAcceptor()
{
	SetType(ACCEPTOR);//enum 的使用方法不知道是否正确;
	sock_fd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in sin;
	sin.sin_family=AF_INET;
	sin.sin_port=htons(listen_address.GetPort());
	inet_pton(AF_INET,listen_address.GetIp().c_str(),&sin.sin_addr);
	if(bind(sock_fd,(struct sockaddr*)&sin,sizeof(sin))<0)
	{
			cout<<"Bind Error..."<<endl;
			exit();
	}
	if(listen(sock_fd,1000)<0)
	{
		cout<<"listen Error..."<<endl;
		exit();
	}
	SetSock(sock_fd);//这里的setSock的里面向reactor了相应的世界 
	//initAcceptor
}
void Acceptor::HandleRead()
{
		Sock listen_fd=GetSock();
		Sock log_fd=accept(listen_fd,NULL,NULL);
		LogHandler *lg=new LogHandler(log_fd);//这里应该怎样处理呢？？？ 内存没有被释放掉。。？？
}
EventHandler::EventHandler(Sock _fd/*,Time *_alarm_time*/)
{
	//alarm_time=_alarm_time;
	if(_fd!=-1)
	{
		sock_fd=_fd;
		g_reactor::Instance()->RegisterEvent(this);
	}
	else
	sock_fd=-1;
	//alarm_time=_alarm_time;
}
bool EventHandler::SetSock(Sock _fd)
{
	if(sock_fd!=-1)
		return False;
	sock_fd=_fd;//这里的sock_fd只能设置一次,如果在构造函数中声明了的话就不需要在声明了
	g_reactor::Instance()->RegisterEvent(this);
}
void EventHander::SetStatusI(STATUS _status)
{
	status=_status;
}
STATUS EventHander::GetStatus()
{
	return status;
}
