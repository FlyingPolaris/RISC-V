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
	//ifstream fin("expr.data");
	char ch;
	uint nexad;
	//fin >> ch;
	int p = 0;
	while (cin>>ch)
	{
		if (ch == '@')
		{
			p = 0;
			int tmp = 1;
			uint num;
			nexad = 0;
			char s[9];
			for (int i = 1;i <= 8;++i)
			{
				cin >> ch;
				s[i] = ch;
			}
			for (int i = 8;i >= 1;--i)
			{
				num = getnum(s[i]);
				nexad += num * tmp;
				tmp <<= 4;
			}
			while ((~ch) && (!isupper(ch)) && (!isdigit(ch)) && (ch != '@')) 
				cin >> ch;
		}
		else
		{
			int i = nexad;
			uint num1, num2, num;
			num1 = getnum(ch);
			cin >> ch;
			num2 = getnum(ch);
			num = (num1 << 4) + num2;
			MEM.writedata(num, i++);
			nexad += 1;
			while ((~ch) && (!isupper(ch)) && (!isdigit(ch) && (ch != '@'))) 
				cin >> ch;
		}
	}
	//fin.close();
}

#endif




#endif
