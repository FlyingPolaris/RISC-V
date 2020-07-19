#include "hardware.hpp"
#include <iostream>
using namespace std;

#ifndef __OPERATION__
#define __OPERATION__

uint ADD(uint rd, uint rs1, uint rs2)
{
	uint data = rs1 + rs2;
	//REG.writereg(data, rd);
	if (PRINT) cout << "add " << " rs1: " << rs1 << " rs2: " << rs2 << " rd: " << rd ;
	//pc += 4;
	return data;
}

uint ADDI(uint rd, uint rs1, uint imm)
{
	uint data = rs1 + imm;
	//REG.writereg(data, rd);
	if (PRINT) cout << "addi " << " rs1: " << rs1 << " rd: " << rd << " imm: " << imm ;
	//pc += 4;
	return data;
}

uint SUB(uint rd, uint rs1, uint rs2)
{
	uint data = rs1 - rs2;
	//REG.writereg(data, rd);
	if (PRINT) cout << "sub " << " rs1: " << rs1 << " rs2: " << rs2 << " rd: " << rd ;
	//pc += 4;

	return data;
}

uint LUI(uint rd, uint imm)
{
	imm <<= 12;
	//REG.writereg(imm, rd);
	if (PRINT) cout << "lui " << " rd: " << rd << " imm: " << imm ;
	//pc += 4;

	return imm;
}

uint AUIPC(uint rd, uint imm, uint pc)
{
	imm <<= 12;
	uint data = pc + imm;
	//REG.writereg(data, rd);
	//pc += 4;

	if (PRINT) cout << "auipc " << " rd: " << rd << " imm: " << imm ;
	return data;
}

uint XOR(uint rd, uint rs1, uint rs2)
{
	uint data = rs1 ^ rs2;
	//REG.writereg(data, rd);
	if (PRINT) cout << "xor " << " rs1: " << rs1 << " rs2: " << rs2 << " rd: " << rd ;
	//pc += 4;

	return data;
}

uint XORI(uint rd, uint rs1, uint imm)
{
	uint data = rs1 ^ imm;
	//REG.writereg(data, rd);
	if (PRINT) cout << "xori " << " rs1: " << rs1 << " rd: " << rd << " imm: " << imm ;
	//pc += 4;

	return data;
}

uint OR(uint rd, uint rs1, uint rs2)
{
	uint data = rs1 | rs2;
	//REG.writereg(data, rd);
	if (PRINT) cout << "or " << " rs1: " << rs1 << " rs2: " << rs2 << " rd: " << rd ;
	//pc += 4;

	return data;
}

uint ORI(uint rd, uint rs1, uint imm)
{
	uint data = rs1 | imm;
	//REG.writereg(data, rd);
	if (PRINT) cout << "ori " << " rs1: " << rs1 << " rd: " << rd << " imm: " << imm ;
	//pc += 4;
	return data;
}

uint AND(uint rd, uint rs1, uint rs2)
{
	uint data = rs1 & rs2;
	//REG.writereg(data, rd);
	if (PRINT) cout << "and " << " rs1: " << rs1 << " rs2: " << rs2 << " rd: " << rd ;
	//pc += 4;

	return data;
}

uint ANDI(uint rd, uint rs1, uint imm)
{
	uint data = rs1 & imm;
	//REG.writereg(data, rd);
	if (PRINT) cout << "andi " << " rs1: " << rs1 << " rd: " << rd << " imm: " << imm ;
	//pc += 4;
	return data;
}

uint SLL(uint rd, uint rs1, uint rs2)
{
	uint data = rs1 << (rs2 & (1 << 6 - 1));
	//REG.writereg(data, rd);
	if (PRINT) cout << "sll " << " rs1: " << rs1 << " rs2: " << rs2 << " rd: " << rd ;
	//pc += 4;

	return data;
}

uint SLLI(uint rd, uint rs1, uint shamt)
{
	uint data = rs1 << shamt;
	//REG.writereg(data, rd);
	if (PRINT) cout << "slli " << " rs1: " << rs1 << " rd: " << rd << " shamt: " <<shamt ;
	//pc += 4;

	return data;
}

uint SRL(uint rd, uint rs1, uint rs2)
{
	uint data = rs1 >> (rs2 & (1 << 6 - 1));
	//REG.writereg(data, rd);
	if (PRINT) cout << "srl " << " rs1: " << rs1 << " rs2: " << rs2 << " rd: " << rd ;
	//pc += 4;

	return data;
}

uint SRLI(uint rd, uint rs1, uint shamt)
{
	uint data = rs1 >> shamt;
	//REG.writereg(data, rd);
	if (PRINT) cout << "srli " << " rs1: " << rs1 << " rd: " << rd << " shamt: " << shamt ;
	//pc += 4;

	return data;
}

uint SRA(uint rd, uint rs1, uint rs2)
{
	uint data =  (rs1) >> (rs2 & (1 << 6 - 1));
	//REG.writereg(data, rd);
	if (PRINT) cout << "sra " << " rs1: " << rs1 << " rs2: " << rs2 << " rd: " << rd ;
	//pc += 4;

	return data;
}

uint SRAI(uint rd, uint rs1, uint shamt)
{
	uint data = (rs1) >> shamt;
	//REG.writereg(data, rd);
	if (PRINT) cout << "srai " << " rs1: " << rs1 << " rd: " << rd << " shamt: " << shamt ;
	//pc += 4;

	return data;
}

uint SLT(uint rd, uint rs1, uint rs2)
{
	uint data = 0;
	if (static_cast<int>(rs1) < static_cast<int>(rs2)) data = 1;
	//REG.writereg(data, rd);
	if (PRINT) cout << "slt " << " rs1: " << rs1 << " rs2: " << rs2 << " rd: " << rd ;
	//pc += 4;

	return data;
}

uint SLTI(uint rd, uint rs1, uint imm)
{
	uint data = 0;
	if (static_cast<int>(rs1) < static_cast<int>(imm)) data = 1;
	//REG.writereg(data, rd);
	if (PRINT) cout << "slti " << " rs1: " << rs1 << " rd: " << rd << " imm: " << imm ;
	//pc += 4;

	return data;
}

uint SLTU(uint rd, uint rs1, uint rs2)
{
	uint data = 0;
	if (static_cast<int>(rs1) < static_cast<int>(rs2)) data = 1;
	//REG.writereg(data, rd);
	if (PRINT) cout << "sltu " << " rs1: " << rs1 << " rs2: " << rs2 << " rd: " << rd ;
	//pc += 4;

	return data;
}

uint SLTIU(uint rd, uint rs1, uint imm)
{
	uint data = 0;
	if ((rs1) < imm) data = 1;
	//REG.writereg(data, rd);
	if (PRINT) cout << "sltiu " << " rs1: " << rs1 << " rd: " << rd << " imm: " << imm ;
	//pc += 4;

	return data;
}

uint BEQ(uint rs1, uint rs2, uint imm)
{
	if ((rs1) == (rs2))
	{
		return 1;
	}
	else return 0;
	if (PRINT) cout << "beq " << " rs1: " << rs1 << " rs2: " << rs2 << " imm: " << imm ;
}

uint BNE(uint rs1, uint rs2, uint imm)
{
	if ((rs1) != (rs2))
	{
		return 1;
	}
	else return 0;
	if (PRINT) cout << "bne " << " rs1: " << rs1 << " rs2: " << rs2 << " imm: " << imm ;
}

uint BLT(uint rs1, uint rs2, uint imm)
{
	if (static_cast<int>(rs1) < static_cast<int>(rs2))
	{
		return 1;
	}
	else return 0;
	if (PRINT) cout << "blt " << " rs1: " << rs1 << " rs2: " << rs2 << " imm: " << imm ;
}

uint BGE(uint rs1, uint rs2, uint imm)
{
	if ((static_cast<int>(rs1) > static_cast<int>(rs2)) || (static_cast<int>(rs1) == static_cast<int>(rs2)))
	{
		return 1;
	}
	else return 0;
	if (PRINT) cout << "bge " << " rs1: " << rs1 << " rs2: " << rs2 << " imm: " << imm ;
}

uint BLTU(uint rs1, uint rs2, uint imm)
{
	if ((rs1) < (rs2))
	{
		return 1;
	}
	else return 0;
	if (PRINT) cout << "bltu " << " rs1: " << rs1 << " rs2: " << rs2 << " imm: " << imm ;
}

uint BGEU(uint rs1, uint rs2, uint imm)
{
	if ((rs1) > (rs2) || rs1 == rs2)
	{
		return 1;
	}
	else return 0;
	if (PRINT) cout << "bgeu " << " rs1: " << rs1 << " rs2: " << rs2 << " imm: " << imm ;
}

uint JAL(uint rd, uint imm, uint pc)
{
	uint data = pc + 4;
//	REG.writereg(pc + 4, 1);
//	pc += imm;
	if (PRINT) cout << "jal " << " rd: " << rd << " imm: " << imm ;
	return data;
}

uint JALR(uint rd, uint rs1, uint imm, uint pc)
{
	uint data = pc + 4;
//	pc = ((rs1 +  (imm)) & (~1));
//	REG.writereg(data, rd);
	if (PRINT) cout << "jalr " << " rs1: " << rs1 << " rd: " << rd << " imm: " << imm ;
	return data;
}

uint LB(uint rd, uint rs1, uint imm)
{
	int place =  (rs1 +  (imm));
	uint data = MEM.readdata(place);
	if (data >> 7 == 1) data += 0xffffff00;
//	pc += 4;
	//REG.writereg(data, rd);
	if (PRINT) cout << "lb " << " rs1: " << rs1 << " rd: " << rd << " imm: " << imm ;
	return data;
}

uint LH(uint rd, uint rs1, uint imm)
{
	int place =  (rs1 +  (imm));
	uint data = 0;
	for (int i = 1;i >= 0;--i)
	{
		data <<= 8;
		data += MEM.readdata(place + i);
	}
	if (data >> 15 == 1) data += 0xffff0000;
//	pc += 4;
//	REG.writereg(data, rd);
	if (PRINT) cout << "lh " << " rs1: " << rs1 << " rd: " << rd << " imm: " << imm ;
	return data;
}

uint LW(uint rd, uint rs1, uint imm)
{
	int place =  (rs1 +  (imm));
	uint data = 0;
	for (int i = 3;i >= 0;--i)
	{
		data <<= 8;
		data += MEM.readdata(place + i);
	}
	//REG.writereg(data, rd);
//	pc += 4;
	if (PRINT) cout << "lw " << " rs1: " << rs1 << " rd: " << rd << " imm: " << imm ;
	return data;
}

uint LBU(uint rd, uint rs1, uint imm)
{
	int place = (rs1 + (imm));
	uint data = MEM.readdata(place);
	//REG.writereg(data, rd);
//	pc += 4;
	if (PRINT) cout << "lb " << " rs1: " << rs1 << " rd: " << rd << " imm: " << imm ;
	return data;
}

uint LHU(uint rd, uint rs1, uint imm)
{
	int place = (rs1 + (imm));
	uint data = 0;
	for (int i = 1;i >= 0;--i)
	{
		data <<= 8;
		data += MEM.readdata(place + i);
	}
//	pc += 4;
//	REG.writereg(data, rd);
	if (PRINT) cout << "lh " << " rs1: " << rs1 << " rd: " << rd << " imm: " << imm ;
	return data;
}

void SB(uint rs1, uint rs2, uint imm)
{
	uint place = (rs1 + (imm));
	uint tmp = rs2 & 0xff;
	MEM.writedata(tmp, place);
//	pc += 4;
	if (PRINT) cout << "sb " << " rs1: " << rs1 << " rs2: " << rs2 << " imm: " << imm ;
}

void SH(uint rs1, uint rs2, uint imm)
{
	uint place = (rs1 + (imm));
	uint tmp = rs2 & 0xffff;
	for (int i = 0;i <= 1;++i)
	{
		MEM.writedata(tmp & 0xff, place + i);
		tmp >>= 8;
	}
//	pc += 4;
	if (PRINT) cout << "sh " << " rs1: " << rs1 << " rs2: " << rs2 << " imm: " << imm ;
}


void SW(uint rs1, uint rs2, uint imm)
{
	uint place = (rs1 + (imm));
	uint tmp = rs2 & 0xffffffff;
	for (int i = 0;i <= 3;++i)
	{
		MEM.writedata(tmp & 0xff, place + i);
		tmp >>= 8;
	}
//	pc += 4;
	if (PRINT) cout << "sw " << " rs1: " << rs1 << " rs2: " << rs2 << " imm: " << imm ;
}

#endif