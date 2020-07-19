#include "hardware.hpp"
#include "prediction.hpp"
#include "IF.hpp"

#ifndef __ID__
#define __ID__

uint getimm(uint data, char type)
{
	uint imm = 0, tmp;
	switch (type)
	{
	case'U':

		imm = data >> 12;
		break;

	case'J':

		tmp = data >> 31;
		for (int i = 1;i < 12;++i)
		{
			imm += tmp;
			imm <<= 1;
		}
		imm += tmp;

		tmp = (data >> 12) & 0b11111111;
		imm <<= 8;
		imm += tmp;

		tmp = (data >> 20) & 1;
		imm <<= 1;
		imm += tmp;

		tmp = (data >> 21) & 0b1111111111;
		imm <<= 10;
		imm += tmp;

		imm <<= 1;

		break;

	case'B':

		tmp = data >> 31;
		for (int i = 1;i < 20;++i)
		{
			imm += tmp;
			imm <<= 1;
		}
		imm += tmp;

		tmp = (data >> 7) & 1;
		imm <<= 1;
		imm += tmp;

		tmp = (data >> 25) & 0b111111;
		imm <<= 6;
		imm += tmp;

		tmp = (data >> 8) & 0b1111;
		imm <<= 4;
		imm += tmp;

		imm <<= 1;

		break;

	case'I':

		tmp = data >> 31;
		for (int i = 1;i < 21;++i)
		{
			imm += tmp;
			imm <<= 1;
		}
		imm += tmp;

		tmp = (data >> 20) & 0b11111111111;
		imm <<= 11;
		imm += tmp;

		break;

	case'S':

		tmp = data >> 31;
		for (int i = 1;i < 21;++i)
		{
			imm += tmp;
			imm <<= 1;
		}
		imm += tmp;

		tmp = (data >> 25) & 0b111111;
		imm <<= 6;
		imm += tmp;

		tmp = (data >> 7) & 0b11111;
		imm <<= 5;
		imm += tmp;

		break;

	default:
		break;
	}

	return imm;
}


uint getrs1(uint data)
{
	uint rs1;
	rs1 = (data >> 15) & 0b11111;
	return rs1;
}

uint getrs2(uint data)
{
	uint rs2;
	rs2 = (data >> 20) & 0b11111;
	return rs2;
}

uint getrd(uint data)
{
	uint rd;
	rd = (data >> 7) & 0b11111;
	return rd;
}


struct ID
{
	uint opcode, imm, rs1, rs2, rd, func3, func7, rs1num, rs2num, pc, data;
	bool jumppredict, error;
	char type;
	ID()
	{
		opcode = imm = rs1 = rs2 = rd = func3 = func7 = rs1num = rs2num = pc = data = 0;
		error = false;
		//pc = REG.readpc();
		type = '\0';
	}
	void get(const IF& tmp)
	{
		data = tmp.data;
		pc = tmp.pc;
	}
	void instructiondecode()
	{
		imm = getimm(data, type);
		rs1 = getrs1(data);
		rs2 = getrs2(data);
		rd = getrd(data);
		rs1num = REG.readreg(rs1);
		rs2num = REG.readreg(rs2);

		//if (!check())
		//{
		//	lock = true;
		//}
		if (PRINT) cout << "pc: " << pc << " ID" << '\n';
	}
	//void jumpping();
	//void makingprediction();
	//bool check();
};




//bool ID::check()
//{
//	if (REG.pcjump > 0 && (opcode == 0b1100011 || opcode == 0b1101111 || opcode == 0b0010111 || opcode == 0b1100111)) return false;
//	else return true;
//}
#endif