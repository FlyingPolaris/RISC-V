#include <iostream>
#include <fstream>
#include <string>
#include "hardware.hpp"
using namespace std;

#ifndef __IF__
#define __IF__

struct IF
{
	uint data, pc, opcode, func3, func7;
	char type;
	bool error;
	IF()
	{
		data = pc = 0;
		error = false;
	}
	void instructionfetch();
	void gettype();
	void getopcode();
	void getfunc3();
	void getfunc7();
};


void IF::instructionfetch()
{
	pc = REG.readpc();
	data = 0;
	for (int i = 3;i >= 0;--i)
	{
		data <<= 8;
		data += MEM.readdata(pc + i);
	}
	REG.writepc(pc + 4);
	getopcode();
	gettype();
	getfunc3();
	getfunc7();
	if (PRINT) cout << "pc: " << pc << " IF" << '\n';
}
void IF::getopcode()
{
	opcode = data & 0b1111111u;
}
void IF::gettype()
{
	switch (opcode)
	{
	case 0b0110111:
	case 0b0010111:
		type = 'U';
		break;
	case 0b1101111:
		type = 'J';
		break;
	case 0b1100011:
		type = 'B';
		break;
	case 0b1100111:
	case 0b0000011:
	case 0b0010011:
		type = 'I';
		break;
	case 0b0100011:
		type = 'S';
		break;
	case 0b0110011:
		type = 'R';
		break;
	default:
		break;
	}
}

void IF::getfunc3()
{
	func3 = (data >> 12) & 0b111;
}

void IF::getfunc7()
{
	func7 = (data >> 25) & 0b1111111;
}

#endif