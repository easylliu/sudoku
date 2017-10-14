// sudoku.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "Core.h"

using namespace std;

int main(int argc, char* argv[])
{
	core core0;
	int n = core0.input_deal(argc, argv);
	if (n == 1)//-c
	{
		int* result = new  int[core0.sudo_count_init * 81];
		int(*sudo_result)[81] = (int(*)[81])result;
		core0.generate(core0.sudo_count_init, sudo_result);
		core0.print_sudo(core0.sudo_count_init, sudo_result, "sudoku.txt");
	}
	else if (n == 2) //-s
	{
		int sudo_count = core0.input(core0.filename_init);
		int* result = new  int[sudo_count * 81];
		int(*sudo_result)[81] = (int(*)[81])result;
		int n = core0.input_sudo(sudo_result, core0.filename_init);
		core0.solve(n, sudo_result, sudo_result);
		core0.print_sudo(n, sudo_result, "sudoku.txt");
	}
	else if (n == 3)//-m
	{
		int* result = new  int[core0.sudo_count_init * 81];
		int(*sudo_result)[81] = (int(*)[81])result;
		core0.generate(core0.sudo_count_init, core0.mode_init, sudo_result);
		core0.print_sudo(core0.sudo_count_init, sudo_result, "sudoku.txt");
	}
	else if (n == 4)//-r 
	{
		int* result = new  int[core0.sudo_count_init * 81];
		int(*sudo_result)[81] = (int(*)[81])result;
		core0.generate(core0.sudo_count_init, core0.lower_init, core0.upper_init, core0.unique_init, sudo_result);
		core0.print_sudo(core0.sudo_count_init, sudo_result, "sudoku.txt");
	}
	return 0;
}
