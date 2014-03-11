#ifndef _H_CONNNECTOR
#define _H_CONNNECTOR
class Connector
{
	public:
	read(IoBuffer &in);
	write(IoBuffer &out);
	
	private:
	Sock sockFd;

};
class Sock
{
		

};

#endif 
