#include <iostream>
#include "IF.hpp"
#include "ID.hpp"
#include "EX.hpp"
#include "MEM.hpp"
#include "WB.hpp"
#include "hardware.hpp"
#include "typedef.hpp"
#include "forwarding.hpp"
#include "Intermediate_register.hpp"

#ifndef __RUN__
#define __RUN__


class run
{
private:
	IF _IF;
	ID _ID;
	EX _EX;
	MEm _MEM;
	WB _WB;
	int count = 0;
public:
	/*void series_connection()
	{
		while (true)
		{
			if (PRINT) cout << ++count << ' ';
			_IF.instructionfetch();
			if (_IF.data == 0x0ff00513u) break;
			_ID.get(_IF);
			_ID.instructiondecode();
			_EX.get(_ID);
			_EX.execute();
			_EX.jumpcheck();
			_MEM.get(_EX);
			_MEM.memoryaccess();
			_WB.get(_MEM);
			_WB.writeback();
		}
		uint rd = getrd(0x0ff00513u);
		uint num = REG.readreg(rd);
		cout << (num & 255u);
	}*/
	void parallel_connection()
	{
		bool jal_or_jalr = false;
		bool type_b = false;
		bool predictresult = true;
		bool waitforresult = false;
		while (true)
		{
			WB_();
			MEM_();
			EX_();
			ID_();
			IF_();
			if (PRINT) cout << '\n';
			forward();
			if (!_ID.error && !_EX.error)
			{
				if (EX_MEM.opcode == 0b0000011)
				{
					if ((EX_MEM.rd == ID_EX.rs1 || EX_MEM.rd == ID_EX.rs2) && EX_MEM.rd != 0)
					{
						errorpass();
						WB_();
						MEM_();
						_EX.error = true;
						forward();
					}
				}
			}

			jal_or_jalr = jumpping();
			type_b = makingprediction();
			predictresult = jumpcheck();

			errorpass();


			if (_IF.data == 0x0ff00513u)
			{
				if (jal_or_jalr || type_b) continue;
				if (!predictresult) continue;
				else break;
			}
			//break;
		/*	if (_IF.data == 0x0ff00513u && !jal_or_jalr && !type_b) 
				_IF.error = true;
			if (predictresult && waitforresult) 
				_IF.error = _ID.error = true;
			else waitforresult = false;
			if (_IF.data == 0x0ff00513u && type_b) 
				waitforresult = true;*/
			//_WB.get(_MEM);
			//_MEM.get(_EX);
			//_EX.get(_ID);
			//_ID.get(_IF);

			//if (end()) break;
		}
		uint rd = getrd(0x0ff00513u);
		uint num = REG.readreg(rd);
		//if (history.totalcount != 0)
		//{
		//	cout << "successful: "<<(history.successfulcount) << "  total: " << (history.totalcount)<<'\n';
		//	cout << 100 * (double)(history.successfulcount) / (double)(history.totalcount) << '%' << '\n';
		//}
		cout << (num & 255u);
	}
	bool end();

	void IF_();
	void ID_();
	void EX_();
	void MEM_();
	void WB_();

	void forward();

	bool jumpping();
	bool makingprediction();
	bool jumpcheck();
	void errorpass();
};

bool run::makingprediction()
{
	if (!_ID.error)
	{
		uint jpc;
		if (ID_EX.type == 'B')
		{
			history.totalcount++;
			ID_EX.jumppredict = history.getprediction();
			if (ID_EX.jumppredict)
			{
				jpc = ID_EX.pc + ID_EX.imm;
				REG.writepc(jpc);
				_IF.error = true;
			}
			return true;
		}
		return false;
	}
	return false;
}

bool run::jumpping()
{
	if (!_ID.error)
	{
		uint jpc;
		switch (ID_EX.opcode)
		{
		case 0b1100111://JALR
			jpc = (ID_EX.rs1num + ID_EX.imm) & (~1);
			REG.writepc(jpc);
			_IF.error = true;
			return true;
			break;
		case 0b1101111://JAL
			jpc = ID_EX.pc + ID_EX.imm;
			REG.writepc(jpc);
			_IF.error = true;
			return true;
			break;
		default:
			return false;
			break;
		}
	}
	return false;
}

void run::IF_()
{
	if (!_IF.error)
	{
		_IF.instructionfetch();
		IF_ID.getfromIF(_IF);
	}
}

void run::ID_()
{
	if (!_ID.error)
	{
		IF_ID.sendtoID(_ID);
		_ID.instructiondecode();
		//_ID.makingprediction();
		ID_EX.getfromID(_ID);
	}
}

void run::EX_()
{
	if (!_EX.error)
	{
		ID_EX.sendtoEX(_EX);
		_EX.execute();
		//if (!_EX.jumpcheck())
		//{
		//	_IF.error = false;
		//	_ID.error = true;
		//}
		EX_MEM.getfromEX(_EX);
	}
}

void run::MEM_()
{
	if (!_MEM.error)
	{
		EX_MEM.sendtoMEM(_MEM);
		_MEM.memoryaccess();
		MEM_WB.getfromMEM(_MEM);
	}
}

void run::WB_()
{
	if (!_WB.error)
	{
		MEM_WB.sendtoWB(_WB);
		_WB.writeback();
	}
}

void run::forward()
{
	if (!_MEM.error) forwarding(ID_EX, MEM_WB);
	//if (!_MEM.error) forwarding(MEM_WB, EX_MEM);
	if (!_EX.error) forwarding(ID_EX, EX_MEM);
}

void run::errorpass()
{
	_WB.error = _MEM.error;
	_MEM.error = _EX.error;
	_EX.error = _ID.error;
	_ID.error = _IF.error;
	_IF.error = false;
}

bool run::end()
{
	if (!_WB.error) return false;
	else if (!_MEM.error) return false;
	else if (!_EX.error) return false;
	else if (!_ID.error) return false;
	else if (!_IF.error) return false;
	else return true;
}

bool run::jumpcheck()
{
	if (!_EX.error)
	{
		if (EX_MEM.type == 'B')
		{
			history.update(EX_MEM.jumpresult);
			if (EX_MEM.jumppredict == EX_MEM.jumpresult)
			{
				history.successfulcount++;
				return true;
			}
			else
			{
				//error = true;
				if (EX_MEM.jumppredict) REG.writepc(EX_MEM.pc + 4);
				else REG.writepc(EX_MEM.pc + EX_MEM.imm);
				_IF.error = _ID.error = true;
				return false;
			}
		}
	}
	return true;
}
#endif
