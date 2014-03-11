#include"event.h"
Acceptor::Acceptor(SockAddress &_listen_addr,Time* _alarm=NULL):Event_handler(-1,_alarm),listen_address(_listen_addr)
{
	SetAlarmTime(_alarm);
}
void Acceptor::InitAcceptor()
{
	SetSock(sock_fd);
}
EventHandler::EventHandler(Sock _fd,Time *_alarm_time)
{
	alarm_time=_alarm_time;
	if(_fd!=-1)
	{
		sock_fd=_fd;
		g_reactor()->RegisterEvent(this);
	}
	else
	sock_fd=-1;
	alarm_time=_alarm_time;
}
bool EventHandler::SetSock(Sock _fd)
{
	if(sock_fd!=-1)
		return False;
	sock_fd=_fd;//这里的sock_fd只能设置一次,如果在构造函数中声明了的话就不需要在声明了
	g_reactor()->RegisterEvent(this);
}




