#ifndef _H_SOCKADDR
#define _H_SOCKADDR
#include<string>
using namespace std;
class SockAddr
{
		public:
				SockAddr(string ip_addr,int _port)
				{
						ip=ip_addr;
						port=_port;
				}
				string GetIp()
				{
						return ip;
				}
				int GetPort()
				{
						return port;
				}
		private:
					string ip;
					int port;
};	

#endif
