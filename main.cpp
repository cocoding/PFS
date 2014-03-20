#include"reactor.h"
#include"event.h"
#include"sockaddress.h"
#include<iosteram>
void init_server()
{
	SockAddress sa("127.0.0.1",3232);
	AcceptorHandler *acceptor=new AcceptorHandler(sa);
}
int main()
{

		ePoll poll();
		g_reactor.Intance()->SetPoll(&Poll);
		init_server();
		g_reactor.Instance()->Poll();
		return 0;
}

