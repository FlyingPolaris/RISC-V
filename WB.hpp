#include "hardware.hpp"
#include "MEM.hpp"
#ifndef __WB__
#define __WB__

struct WB
{
	uint opcode, imm, rs1, rs2, rd, func3, func7, rs1num, rs2num, pc, result, data;
	bool jumppredict, jumpresult, error;
	char type;
	WB()
	{
		opcode = imm = rs1 = rs2 = rd = func3 = func7 = rs1num = rs2num = pc = result = 0;
		type = '\0';
		error = false;
	}
	void get(const MEm& tmp)
	{
		type = tmp.type;
		opcode = tmp.opcode;
		imm = tmp.imm;
		rs1 = tmp.rs1;
		rs2 = tmp.rs2;
		rd = tmp.rd;
		func3 = tmp.func3;
		func7 = tmp.func7;
		rs1num = tmp.rs1num;
		rs2num = tmp.rs2num;
		pc = tmp.pc;
		result = tmp.result;
	}
	void writeback();
};

void WB::writeback()
{
	if (type != 'B' && type != 'S')
	{
		bool flag = true;
		if (opcode == 0b0010011 && (func3 == 001 || func3 == 101))
		{
			if (imm >> 5 != 0) flag = false;
		}
		if(flag) REG.writereg(result, rd);
	}

	if (PRINT)
	{
		cout << "pc: " << pc << " WB" << "  (";
		for (int i = 0;i <= 31;++i)
			cout << REG.readreg(i) << ' ';
		cout << ")\n";
	}

	//if (opcode == 0b1101111)
	//{
	//	REG.writepc(pc);
	//	REG.pcjump--;
	//}
	//else if (opcode == 0b1100111)
	//{
	//	REG.writepc(pc);
	//	REG.pcjump--;
	//}
}

#endif