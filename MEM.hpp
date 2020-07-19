#include "hardware.hpp"
#include "EX.hpp"
#include "operation.hpp"
#ifndef __MEM__
#define __MEM__


struct MEm
{
	uint opcode, imm, rs1, rs2, rd, func3, func7, rs1num, rs2num, pc, result, data;
	bool jumppredict, jumpresult, error;
	char type;
	MEm()
	{
		opcode = imm = rs1 = rs2 = rd = func3 = func7 = rs1num = rs2num = pc = result = 0;
		type = '\0';
		error = false;
	}
	void get(const EX& tmp)
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
	void memoryaccess();
};

void MEm::memoryaccess()
{
	//uint opcode = tmp.opcode;
	//uint imm = tmp.imm;
	//uint rs1 = tmp.rs1num;
	//uint rs2 = tmp.rs2num;
	//uint func3 = tmp.func3;
	//uint rd = tmp.rd;
	//char type = tmp.type;

	if (PRINT) cout << "pc: " << pc << " MEM" <<" (OP:  ";

	if (type == 'S')
	{
		switch (func3)
		{
		case 0b000:
			SB(rs1num, rs2num, imm);
			break;
		case 0b001:
			SH(rs1num, rs2num, imm);
			break;
		case 0b010:
			SW(rs1num, rs2num, imm);
			break;
		default:
			break;
		}
	}
	if (opcode == 0b0000011)
	{
		switch (func3)
		{
		case 0b000:
			result = LB(rd, rs1num, imm);
			break;
		case 0b001:
			result = LH(rd, rs1num, imm);
			break;
		case 0b010:
			result = LW(rd, rs1num, imm);
			break;
		case 0b100:
			result = LBU(rd, rs1num, imm);
			break;
		case 0b101:
			result = LHU(rd, rs1num, imm);
			break;
		default:
			break;
		}
	}


	if (PRINT) cout << ")\n";
}

#endif
