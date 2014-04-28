#include"reactor.h"
#include"event.h"
#include"sockaddr.h"
#include<iostream>
#include<string>
extern G_Reactor g_reactor;
int main()
{

		ePoll poll;
		g_reactor.Instance()->SetPoll(&poll);
		string str("127.0.0.1");
		SockAddr *sa=new SockAddr(str,5656);
		Acceptor *acceptor=new Acceptor(*sa);
		g_reactor.Instance()->Poll();
		free(sa);
		return 0;
}

