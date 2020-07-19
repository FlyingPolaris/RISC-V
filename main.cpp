#pragma GCC optimize(2)


#include "hardware.hpp"
#include "IF.hpp"
#include "ID.hpp"
#include "EX.hpp"
#include "MEM.hpp"
#include "WB.hpp"
#include "run.hpp"
#include "documentreading.hpp"

#include <iostream>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
//	PRINT = true;
	documentreading();
	run RUN;
//	RUN.series_connection();
	RUN.parallel_connection();
	return 0;
}