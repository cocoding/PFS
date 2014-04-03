#ifndef _H_EVENT
#define _H_EVENT
#include"sockaddr.h"
#include"global.h"
#include"reactor.h"
///变量 小写加下划线，类名大写，函数名大写
typedef int Sock;
enum  TYPE
{
	ACCEPTOR=0,
	LOGGER,
	NONE
};
enum STATUS
{
	WAIT=4,
	READ,
	DEAD
};
class EventHandler
{
	public:
	EventHandler(Sock _fd);//,Time _alarm_time);//这里对于acceptor来说_fd是-1代表的是以后会再次设置的
	Sock GetSock();//这个函数的必要性.主要是用于epool
	virtual void HandleRead(){
	}
	int SetSock(Sock _sock_fd);
	virtual void HandleWrite()
	{
	}
	virtual void HandleDropOut(){}
//	virtual void SetAlarmTime(Time *alarm);//这里的变量还需要处理一下
//	virtual Time GetAlarmTime();	
//	virtual void HandleTimerOut();
	void SetStatus(STATUS _status);
	STATUS GetStatus();
	TYPE GetEventType();
	void SetEventType(TYPE t);
	STATUS status;
	//Time alarm_time;
	Sock sock_fd;
	TYPE type;

};
class Acceptor:public EventHandler
{
	public:
	Acceptor(SockAddr & _listen_addr):EventHandler(-1),listen_address(_listen_addr)
	{
			InitAcceptor();
				 //SetAlarmTime(_alarm);
	}
	void InitAcceptor();
	void HandleRead();//需要重写这个函数
	void HandleDropOut();
	private:
		int Type;//这里主要是用于区别接受信号的和接受数据的 enum类型
		SockAddr &listen_address;
};
class LogHandler:public EventHandler
{
	public:
			LogHandler(/*SockAddress &sock_addr,*/Sock _sock_fd);//前面是否需要
			void HandleRead();
			void HandleDropOut();
};
#endif
