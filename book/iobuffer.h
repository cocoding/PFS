#ifndef _H_IOBUFFER
#define _H_IOBUFFER
class IoBuffer
{
	public:
	IoBuffer(int ioSize=0):bufSize(ioSize),buffer(NULL)
	{
		
	}
	SetSize(int size)
	{
		bufSize=size;
	}
	~IoBuffer()
	{
		free(buffer);
	}
	private:
	int bufSize;
	char *buffer;
};
#endif
