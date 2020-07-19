#include <iostream>
#include <cstring>
#include <fstream>

#include "hardware.hpp"
using namespace std;

#ifndef __DOCUMENTREADING__
#define __DOCUMENTREADING__

uint getnum(char ch)
{
	uint num;
	if (ch >= '0' && ch <= '9') num = ch - '0';
	else if (ch >= 'A' && ch <= 'Z') num = ch - 'A' + 10;
	return num;
}

void documentreading()
{
	//ifstream fin("pi.data");
	char s[50];
	uint nexad;
	int p = 0;
	while (cin.getline(s, sizeof(s)))
	{
		if (s[0] == '@')
		{
			p = 0;
			int tmp = 1;
			uint num;
			nexad = 0;
			for (int i = 8;i >= 1;--i)
			{
				num = getnum(s[i]);
				nexad += num * tmp;
				tmp <<= 4;
			}
		}
		else
		{
			p = 0;
			int i = nexad;
			while (s[p] != '\0')
			{
				uint num1, num2, num;
				num1 = getnum(s[p++]);
				num2 = getnum(s[p++]);
				if (s[p] == ' ') p++;
				num = (num1 << 4) + num2;
				MEM.writedata(num, i++);
				nexad += 1;
			}
		}
	}
	//fin.close();
}




#endif
