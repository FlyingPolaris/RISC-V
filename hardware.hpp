#include "typedef.hpp"
#include <cstring>


#ifndef __HARDWARE__
#define __HARDWARE__

const int MAXSIZE = 999999;
bool PRINT = false;

class reg 
{
private:
	uint pc;
	uint x[32];
public:
	int pcjump = 0;
	reg()
	{
		pc = 0;
		for (int i = 0;i < 32;++i) x[i] = 0;
	}
	void writepc(uint data)
	{
		pc = data;
	}
	void writereg(uint data, int index)
	{
		if (index == 0)
		{
			x[index] = 0;
		}
		else x[index] = data;
	}
	uint readpc()
	{
		return pc;
	}
	uint readreg(int index)
	{
		return x[index];
	}
}REG;

class mem
{
private:
	uint x[MAXSIZE];
public:
	mem()
	{
		memset(x, 0, sizeof(x));
	}

	uint readdata(int index)
	{
		return x[index];
	}

	void writedata(uint thedata, int index)
	{
		x[index] = thedata;
	}
}MEM;

#endif
