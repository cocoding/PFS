#include"reactor.h"
#include"event.h"
#include"sockaddr.h"
#include<iostream>
void init_server()
{
	SockAddr *sa=new SockAddr("127.0.0.1",3232);
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

