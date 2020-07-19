#include <iostream>
#include "Intermediate_register.hpp"


#ifndef __FORWARDING__
#define __FORWARDING__

bool needforwarding(EX_TOWARDS_MEM& EX_MEM)
{
	uint opcode = EX_MEM.opcode;
	uint func3 = EX_MEM.opcode;
	switch (opcode)
	{
	case 0b0110111:case 0b0010111:case 0b1101111:case 0b1100111:case 0b0110011:case 0b0000011:
		return true;
		break;
	case 0b0010011:
		switch (func3)
		{
		case 0b001:
		case 0b101:
			if (!EX_MEM.imm << 5) return false;
			else return true;
			break;
		default:
			return true;
			break;
		}
	default:
		return false;
		break;
	}
}

bool needforwarding(MEM_TOWARDS_WB& MEM_WB)
{
	uint opcode = MEM_WB.opcode;
	uint func3 = MEM_WB.opcode;
	switch (opcode)
	{
	case 0b0110111:case 0b0010111:case 0b1101111:case 0b1100111:case 0b0110011:case 0b0000011:
		return true;
		break;
	case 0b0010011:
		switch (func3)
		{
		case 0b001:
		case 0b101:
			if (!MEM_WB.imm << 5) return false;
			else return true;
			break;
		default:
			return true;
			break;
		}
	default:
		return false;
		break;
	}
}

void forwarding(ID_TOWARDS_EX& ID_EX, EX_TOWARDS_MEM& EX_MEM)
{
	if (needforwarding(EX_MEM))
	{
		if (ID_EX.rs1 == EX_MEM.rd && ID_EX.rs1 != 0)
		{
			ID_EX.rs1num = EX_MEM.result;
		}
		else if (ID_EX.rs2 == EX_MEM.rd && ID_EX.rs2 != 0)
		{
			ID_EX.rs2num = EX_MEM.result;
		}
	}
}

void forwarding(ID_TOWARDS_EX& ID_EX, MEM_TOWARDS_WB& MEM_WB)
{
	if (needforwarding(MEM_WB))
	{
		if (ID_EX.rs1 == MEM_WB.rd && ID_EX.rs1 != 0)
		{
			ID_EX.rs1num = MEM_WB.result;
		}
		else if (ID_EX.rs2 == MEM_WB.rd && ID_EX.rs2 != 0)
		{
			ID_EX.rs2num = MEM_WB.result;
		}
	}
}

void forwarding(MEM_TOWARDS_WB& MEM_WB, EX_TOWARDS_MEM& EX_MEM)
{
	if (needforwarding(MEM_WB))
	{
		if (EX_MEM.rs1 == MEM_WB.rd && EX_MEM.rs1 != 0)
		{
			EX_MEM.rs1num = MEM_WB.result;
		}
		else if (EX_MEM.rs2 == MEM_WB.rd && EX_MEM.rs2 != 0)
		{
			EX_MEM.rs2num = MEM_WB.result;
		}
	}
}
#endif