#include <iostream>
#include <fstream>
#include <string>
#include "IF.hpp"
#include "ID.hpp"
#include "EX.hpp"
#include "MEM.hpp"
#include "WB.hpp"

#ifndef __INTERMEIDATE_REGISTER__
#define __INTERMEIDATE_REGISTER__

using namespace std;

struct IF_TOWARDS_ID
{
	uint data, pc, opcode, func3, func7;
	char type;
	//bool error;
	void getfromIF(IF& _IF)
	{
		data = _IF.data;
		pc = _IF.pc;
		opcode = _IF.opcode;
		func3 = _IF.func3;
		func7 = _IF.func7;
		type = _IF.type;
		//error = _IF.error;
	}
	void sendtoID(ID& _ID)
	{
		_ID.data = data;
		_ID.pc = pc;
		_ID.opcode = opcode;
		_ID.func3 = func3;
		_ID.func7 = func7;
		_ID.type = type;
		//_ID.error = error;
	}
}IF_ID;

struct ID_TOWARDS_EX
{
	uint opcode, imm, rs1, rs2, rd, func3, func7, rs1num, rs2num, pc, data;
	bool jumppredict;
	char type;
	void getfromID(ID& _ID)
	{
		opcode = _ID.opcode;
		imm = _ID.imm;
		rs1 = _ID.rs1;
		rs2 = _ID.rs2;
		rd = _ID.rd;
		func3 = _ID.func3;
		func7 = _ID.func7;
		rs1num = _ID.rs1num;
		rs2num = _ID.rs2num;
		pc = _ID.pc;
		data = _ID.data;
		jumppredict = _ID.jumppredict;
		//error = _ID.error;
		type = _ID.type;
	}
	void sendtoEX(EX &_EX)
	{
		_EX.opcode = opcode;
		_EX.imm = imm;
		_EX.rs1 = rs1;
		_EX.rs2 = rs2;
		_EX.rd = rd;
		_EX.func3 = func3;
		_EX.func7 = func7;
		_EX.rs1num = rs1num;
		_EX.rs2num = rs2num;
		_EX.pc = pc;
		_EX.data = data;
		_EX.jumppredict = jumppredict;
		//_EX.error = error;
		_EX.type = type;
	}
}ID_EX;

struct EX_TOWARDS_MEM
{
	uint opcode, imm, rs1, rs2, rd, func3, func7, rs1num, rs2num, pc, result, data;
	bool jumppredict, jumpresult;
	char type;
	void getfromEX(EX& _EX)
	{
		opcode = _EX.opcode;
		imm = _EX.imm;
		rs1 = _EX.rs1;
		rs2 = _EX.rs2;
		rd = _EX.rd;
		func3 = _EX.func3;
		func7 = _EX.func7;
		rs1num = _EX.rs1num;
		rs2num = _EX.rs2num;
		pc = _EX.pc;
		result = _EX.result;
		data = _EX.data;
		jumppredict = _EX.jumppredict;
		jumpresult = _EX.jumpresult;
		//error = _EX.error;
		type = _EX.type;
	}
	void sendtoMEM(MEm& _MEM)
	{
		_MEM.opcode = opcode;
		_MEM.imm = imm;
		_MEM.rs1 = rs1;
		_MEM.rs2 = rs2;
		_MEM.rd = rd;
		_MEM.func3 = func3;
		_MEM.func7 = func7;
		_MEM.rs1num = rs1num;
		_MEM.rs2num = rs2num;
		_MEM.pc = pc;
		_MEM.result = result;
		_MEM.data = data;
		_MEM.jumppredict = jumppredict;
		_MEM.jumpresult = jumpresult;
		//_MEM.error = error;
		_MEM.type = type;
	}
}EX_MEM;


struct MEM_TOWARDS_WB
{
	uint opcode, imm, rs1, rs2, rd, func3, func7, rs1num, rs2num, pc, result, data;
	bool jumppredict, jumpresult;
	char type;
	void getfromMEM(MEm& _MEM)
	{
		opcode = _MEM.opcode;
		imm = _MEM.imm;
		rs1 = _MEM.rs1;
		rs2 = _MEM.rs2;
		rd = _MEM.rd;
		func3 = _MEM.func3;
		func7 = _MEM.func7;
		rs1num = _MEM.rs1num;
		rs2num = _MEM.rs2num;
		pc = _MEM.pc;
		result = _MEM.result;
		data = _MEM.data;
		jumppredict = _MEM.jumppredict;
		jumpresult = _MEM.jumpresult;
		//error = _MEM.error;
		type = _MEM.type;
	}
	void sendtoWB(WB& _WB)
	{
		_WB.opcode = opcode;
		_WB.imm = imm;
		_WB.rs1 = rs1;
		_WB.rs2 = rs2;
		_WB.rd = rd;
		_WB.func3 = func3;
		_WB.func7 = func7;
		_WB.rs1num = rs1num;
		_WB.rs2num = rs2num;
		_WB.pc = pc;
		_WB.result = result;
		_WB.data = data;
		_WB.jumppredict = jumppredict;
		_WB.jumpresult = jumpresult;
		//_WB.error = error;
		_WB.type = type;
	}
}MEM_WB;

#endif
