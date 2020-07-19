#include "IF.hpp"
#include "operation.hpp"


#ifndef __EX__
#define __EX__

struct EX
{
	uint opcode, imm, rs1, rs2, rd, func3, func7, rs1num, rs2num, pc, result, data;
	bool jumppredict, jumpresult, error;
	char type;
	EX()
	{
		opcode = imm = rs1 = rs2 = rd = func3 = func7 = rs1num = rs2num = pc = result = 0;
		jumppredict = jumpresult = false;
		error = false;
		type = '\0';
	}
	void get(const ID& tmp)
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
		jumppredict = tmp.jumppredict;
	}
	void execute();
	bool jumpcheck();
};

void EX::execute()
{
	if (PRINT) cout << "pc: " << pc << " EX" << "  (OP:  ";
	//char type = tmp.type;
	//uint func7 = tmp.func7;
	//uint func3 = tmp.func3;
	//uint rs1 = rs1num;
	//uint rs2 = rs2num;
	//uint rd = tmp.rd;
	//uint opcode = tmp.opcode;
	//uint imm = tmp.imm;
	//uint shamt = tmp.imm;
	//opcode = getopcode(data);
	//if (PRINT) cout << " op: ";
	if (type == 'U')
	{
		//imm = getimm(data);
		//rd = getrd(data);
		switch (opcode)
		{
		case 0b0110111:
			result = LUI(rd, imm);
			break;
		case 0b0010111:
			result = AUIPC(rd, imm, pc);
			break;
		default:
			break;
		}
	}

	if (type == 'B')
	{
		//func3 = getfunc3(data);
		//rs1 = getrs1(data);
		//rs2 = getrs2(data);
		//imm = getimm(data);
		switch (func3)
		{
		case 0b000:
			jumpresult = BEQ(rs1num, rs2num, imm);
			break;
		case 0b001:
			jumpresult = BNE(rs1num, rs2num, imm);
			break;
		case 0b100:
			jumpresult = BLT(rs1num, rs2num, imm);
			break;
		case 0b101:
			jumpresult = BGE(rs1num, rs2num, imm);
			break;
		case 0b110:
			jumpresult = BLTU(rs1num, rs2num, imm);
			break;
		case 0b111:
			jumpresult = BGEU(rs1num, rs2num, imm);
			break;
		default:
			break;
		}
	}

	if (type == 'J')
	{
		//imm = getimm(data);
		//rd = getrd(data);
		result = JAL(rd, imm, pc);
	}

	if (type == 'I')
	{
		//imm = getimm(data);
		//rd = getrd(data);
		//rs1 = getrs1(data);
		//func3 = getfunc3(data);


		switch (opcode)
		{
		case 0b1100111:
			result = JALR(rd, rs1num, imm, pc);
			break;
			

		case 0b0010011:
			switch (func3)
			{
			case 0b000:
				result = ADDI(rd, rs1num, imm);
				break;
			case 0b010:
				result = SLTI(rd, rs1num, imm);
				break;
			case 0b011:
				result = SLTIU(rd, rs1num, imm);
				break;
			case 0b100:
				result = XORI(rd, rs1num, imm);
				break;
			case 0b110:
				result = ORI(rd, rs1num, imm);
				break;
			case 0b111:
				result = ANDI(rd, rs1num, imm);
				break;
			case 0b001:
				result = SLLI(rd, rs1num, imm);
				break;
			case 0b101:
			//	func7 = getfunc7(data);
			//	shamt = getrs2(data);
				if (func7 == 0b0000000) result = SRLI(rd, rs1num, imm);
				if (func7 == 0b0100000) result = SRAI(rd, rs1num, imm);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}

		/*if (PRINT)
		{
			for (int i = 0;i <= 31;++i)
				cout << REG.readreg(i) << ' ';
			cout << '\n';
		}*/
	}


	if (type == 'R')
	{
		//imm = getimm(data);
		//rd = getrd(data);
		//rs1 = getrs1(data);
		//rs2 = getrs2(data);
		//func3 = getfunc3(data);
		//func7 = getfunc7(data);

		switch (func3)
		{
		case 0b000:
			if (func7 == 0b0000000) result = ADD(rd, rs1num, rs2num);
			if (func7 == 0b0100000) result = SUB(rd, rs1num, rs2num);
			break;
		case 0b001:
			result = SLL(rd, rs1num, rs2num);
			break;
		case 0b010:
			result = SLT(rd, rs1num, rs2num);
			break;
		case 0b011:
			result = SLTU(rd, rs1num, rs2num);
			break;
		case 0b100:
			result = XOR(rd, rs1num, rs2num);
			break;
		case 0b101:
			if (func7 == 0b0000000) result = SRL(rd, rs1num, rs2num);
			if (func7 == 0b0100000) result = SRA(rd, rs1num, rs2num);
			break;
		case 0b110:
			result = OR(rd, rs1num, rs2num);
			break;
		case 0b111:
			result = AND(rd, rs1num, rs2num);
			break;
		default:
			break;
		}
	}
	if (PRINT) cout << ")\n";
}



#endif
