#include"reactor.h"
#include"event.h"
#include"sockaddr.h"
#include<iostream>
#include<string>
extern G_Reactor g_reactor;
void init_server()
{
	string str("127.0.0.1");
	SockAddr *sa=new SockAddr(str,5656);
	Acceptor *acceptor=new Acceptor(*sa);
}
int main()
{

		ePoll poll;
		g_reactor.Instance()->SetPoll(&poll);
		init_server();
		g_reactor.Instance()->Poll();
		return 0;
}

