#pragma once

#include "stdafx.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "option.h"
#include "ctype.h"
bool M = false;


class core
{
public:

	int sudo_count_init = 0;
	int mode_init = 0;
	int lower_init = 0;
	int upper_init = 0;
	bool unique_init = false;
	char* filename_init;

	int input_deal(int argc, char* argv[]);
	bool isvalid(int sudo[][9]);
	bool isunique(int sudo_count, int result[][81]);

	//生成数独,存在result中
	//create -c
	void generate(int sudo_count, int result[][81]);
	//create -n -m
	_declspec(dllexport) void __stdcall generate(int number, int mode, int result[][81]);
	//create -n -r -u
	void generate(int number, int lower, int upper, bool unique, int result[][81]);

	void hollow(int before[81], int num);
	void combine(int question[81], int solution[81]);


	int matrix_change(int count, int sudo_count, char sudo[9][10], int result[][81]);	//矩阵变换
	void line_range(int init, int n, char mid_sudo[9][10], char sudo[9][10]);				//行交换
	void column_range(int init, int n, char mid_sudo[9][10], char sudo[9][10]);				//列变换

																							//写文件，将result写到文件中
	void print_sudo(int sudo_count, int result[][81], char* filename);//print sudo one time 

																	  //读文件，获取数独书 
	int input(char* filename);
	//读文件，讲数独存在question中
	int input_sudo(int question[][81], char* filename);//read return sudo_count

													   //solve,结果存在result中
	_declspec(dllexport) void __stdcall solve(int sudo_count, int question[][81], int result[][81]);
	//判断是否有解，结果存在solution中
	bool solve(int puzzle[81], int solution[81]);
	int deal(int sudo[9][9], option[9][9]);
	option findshortest(option kexuan[9][9], int sudo[9][9]);
	bool tianman(int sudo[9][9]);


};

int core::input_deal(int argc, char* argv[])
{
	FILE *fp;
	for (int i = 0; i<argc; i++)
	{
		if (strcmp(argv[i], "-c") == 0)
		{
			for (int j = 0; j<strlen(argv[i + 1]); j++)
				if (!isdigit(argv[i + 1][j]))
				{
					printf("the format of -c is illegal,1<=c_num<=1000000");
					return -1;//c_num;
				}
			if (atoi(argv[i + 1]) < 1 || atoi(argv[i + 1]) > 1000000 || argc != 3)
			{
				printf("the format of -c is illegal,1<=c_num<=1000000");
				return -1;
			}
			else
			{
				sudo_count_init = atoi(argv[i + 1]);
				return 1;
			}//-c}
		}
		else if (strcmp(argv[i], "-s") == 0)
		{
			fopen_s(&fp, argv[i + 1], "r");
			if (fp == NULL)
			{
				printf("the file can be opened");
				return -2;//file not open
			}
			if (argc != 3)
			{
				printf("the format of -s is illegal");
				return -1;
			}
			else
			{
				filename_init = argv[i + 1];
				return 2;
			}//-s
		}
		else if (strcmp(argv[i], "-n") == 0)
		{
			for (int j = 0; j<strlen(argv[i + 1]); j++)
				if (!isdigit(argv[i + 1][j]))
				{
					printf("the format of -n is illegal,1<=n_num<=10000");
					return -3;//n_num
				}
			if (atoi(argv[i + 1]) < 1 || atoi(argv[i + 1]) > 10000)
			{
				printf("the format of -n is illegal,1<=n_num<=10000");
				return -3;
			}
			else
			{
				sudo_count_init = atoi(argv[i + 1]);
			}
		}
		else if (strcmp(argv[i], "-m") == 0)
		{
			for (int j = 0; j < strlen(argv[i + 1]); j++)
				if (!isdigit(argv[i + 1][j]))
				{
					printf("the format of -m is illegal,mode=1,2,3");
					return -4;
				}
			if (atoi(argv[i + 1]) < 1 || atoi(argv[i + 1]) > 3)
			{
				printf("the format of -m is illegal,mode=1,2,3");
				return -4;
			}
			else
			{
				mode_init = atoi(argv[i + 1]);
			}
		}
		else if (strcmp(argv[i], "-r") == 0)
		{
			char *first, *second, *third;
			first = strtok_s(argv[i + 1], "~", &second);
			second = strtok_s(second, "~", &third);
			int low = atoi(first);
			int upp = atoi(second);
			if (low < 20)
			{
				printf("the format of -r is illegal,low>=20");
				return -5;
			}
			else if (upp > 55)
			{
				printf("the format of -r is illegal,upp <=55");
				return -5;
			}
			else if (low >upp)
			{
				printf("the format of -r is illegal,low<=upp");
				return -5;
			}
			else
			{
				lower_init = low;
				upper_init = upp;
			}
		}
		else if (strcmp(argv[i], "-u") == 0)
		{
			unique_init = true;
		}
	}
	if (sudo_count_init != 0 && mode_init != 0)
	{
		if (lower_init != 0 && upper_init != 0)
		{
			printf("the format of input is illegal,-m and -r cannot coexist");
			return -6;
		}
		else if (unique_init == true)
		{
			printf("the format of input is illegal,-m and -u cannot coexist");
			return -6;
		}
		return 3; //-m
	}
	else if (sudo_count_init != 0 && lower_init != 0 && upper_init != 0)
	{
		return 4;//-r
	}
	else if (sudo_count_init != 0 && unique_init == true)
	{
		return 4;//-r -u
	}
	else
	{
		printf("the format of input is illegal");
		return -1;
	}
}

bool core::isvalid(int sudo[][9])
{
	bool row[9][9] = { 0 }, column[9][9] = { 0 }, cube[9][9] = { 0 };
	for (int i = 0; i<9; i++)
	{
		for (int j = 0; j<9; j++)
		{
			if (sudo[i][j] == 0)continue;
			int loc = sudo[i][j] - 1;
			if (row[i][loc] || column[j][loc] || cube[(i / 3) * 3 + j / 3][loc])
				return false;
			row[i][loc] = true;
			column[j][loc] = true;
			cube[(i / 3) * 3 + j / 3][loc] = true;
		}
	}
	return true;
}
bool core::isunique(int sudo_count, int result[][81])
{
	for (int i = 0; i < sudo_count - 1; i++)
	{
		for (int j = i + 1; j < sudo_count; j++)
		{
			if (memcmp(result[i], result[j], 81) == 0)
				return false;
		}
	}
	return true;
}

//生成 sudo_count个数独终局存在result中
void core::generate(int sudo_count, int result[][81])
{
	char sudo[9][10] = { "958367124",				//数独种子
		"237451968",
		"146928357",
		"612874593",
		"573619482",
		"489235671",
		"724593816",
		"891746235",
		"365182749" };
	char sudo_middle[9][10];
	int  i, j, m, n;
	int count = 0;							//已生成的数独数
	for (i = 0; i<9; i++)
	{									//初始化
		strcpy_s(sudo_middle[i], sudo[i]);
	}
	count = matrix_change(count, sudo_count, sudo_middle, result);	//根据一个种子转换输出
	while (count < sudo_count)
	{
		if (count == -1) break;
		for (m = 1; m < 9; m++)//change num;
		{
			for (n = m + 1; n <= 9; n++)
			{
				for (i = 0; i < 9; i++)
				{
					for (j = 0; j < 9; j++)
					{
						if (sudo[i][j] == (m + '0'))
							sudo_middle[i][j] = n + '0';
						else if (sudo[i][j] == (n + '0'))
							sudo_middle[i][j] = m + '0';
						else
							sudo_middle[i][j] = sudo[i][j];
					}
				}
				count = matrix_change(count, sudo_count, sudo_middle, result);
				if (count == -1) return;
			}
		}
	}
}

void __stdcall core::generate(int number, int mode, int result[][81])
{
	int que_num = input("sudo_ti.txt");
	int randnum, i;
	int* result0 = new  int[que_num * 81];
	int* result1 = new  int[que_num * 81];
	int(*question)[81] = (int(*)[81])result0;
	int(*solution)[81] = (int(*)[81])result1;
	input_sudo(question, "sudo_ti.txt");
	input_sudo(solution, "sudo_jie.txt");
	for (i = 0; i < number; i++) {
		if (mode == 1)//[11,29)
		{
			randnum = rand() % 18 + 11;
			hollow(solution[i], randnum);
			combine(question[i], solution[i]);
			memcpy(result[i], question[i], sizeof(int) * 81);
		}
		else if (mode == 2)//[29,47)
		{
			randnum = rand() % 18 + 29;
			hollow(solution[i], randnum);
			combine(question[i], solution[i]);
			memcpy(result[i], question[i], sizeof(int) * 81);
		}
		else if (mode == 3)//[47,65)
		{
			randnum = rand() % 18 + 47;
			hollow(solution[i], randnum);
			combine(question[i], solution[i]);
			memcpy(result[i], question[i], sizeof(int) * 81);
		}
		else
		{
			printf("error,mode is 1-3;");
			return;
		}
	}
}

void core::generate(int number, int lower, int upper, bool unique, int result[][81])
{
	int que_num = input("sudo_ti.txt");
	int* result0 = new  int[que_num * 81];
	int* result1 = new  int[que_num * 81];
	int(*question)[81] = (int(*)[81])result0;
	int(*solution)[81] = (int(*)[81])result1;
	int randnum, i;
	input_sudo(question, "sudo_ti.txt");
	input_sudo(solution, "sudo_jie.txt");
	for (i = 0; i < number; i++)
	{
		randnum = rand() % (upper - lower + 1) + lower;
		hollow(solution[i], randnum);
		combine(question[i], solution[i]);
		memcpy(result[i], question[i], sizeof(int) * 81);
	}
}

//将question和solution结合起来放在question中
void core::combine(int question[81], int solution[81])
{
	for (int i = 0; i < 81; i++)
	{
		if (question[i] == 0 && solution[i] != 0)
			question[i] = solution[i];
	}
}

//在before中挖去num个数
void core::hollow(int before[81], int num)
{
	int flag[81];
	for (int j = 0; j<81; j++)
	{
		if (before[j] != 0)
			flag[j] = 1;
		else
			flag[j] = 0;
	}
	while (num != 0)
	{
		int randnum = rand() % 81 + 0;
		if (before[randnum] != 0)
		{
			before[randnum] = 0;
			flag[randnum] = 0;
			num--;
		}
	}
}

//返回已生成数独数量，一次最多生成36*36*36个数独
int core::matrix_change(int count, int sudo_count, char sudo[9][10], int result[][81]) {
	int line0, line1, line2, column0, column1, column2;
	int  i = 0, j, k;
	int single_result[81];
	char mid_sudo[9][10], mid_sudo1[9][10];
	for (line0 = 0; line0 < 6; line0++)
	{
		line_range(0, line0, mid_sudo, sudo);
		for (line1 = 0; line1 < 6; line1++)
		{
			line_range(3, line1, mid_sudo, sudo);
			for (line2 = 0; line2 < 6; line2++)
			{
				line_range(6, line2, mid_sudo, sudo);
				for (column0 = 0; column0 < 6; column0++)
				{
					column_range(0, column0, mid_sudo1, mid_sudo);
					for (column1 = 0; column1 < 6; column1++)
					{
						column_range(3, column1, mid_sudo1, mid_sudo);
						for (column2 = 0; column2< 6; column2++)
						{
							column_range(6, column2, mid_sudo1, mid_sudo);
							for (j = 0; j < 9; j++)
							{
								for (k = 0; k < 9; k++)
								{
									single_result[i++] = int(mid_sudo1[j][k] - '0');
								}
							}
							i = 0;
							memcpy(result[count], single_result, sizeof(int) * 81);
							count++;
							if (count < sudo_count)
								;
							else
								return -1;
						}
					}
				}
			}
		}
	}
	return count;
}

void core::line_range(int init, int n, char mid_sudo1[9][10], char sudo[9][10])
{
	if (n == 0)
	{
		strcpy_s(mid_sudo1[init], sudo[init]);
		strcpy_s(mid_sudo1[init + 1], sudo[init + 1]);
		strcpy_s(mid_sudo1[init + 2], sudo[init + 2]);
	}
	if (n == 1)
	{
		strcpy_s(mid_sudo1[init], sudo[init]);
		strcpy_s(mid_sudo1[init + 2], sudo[init + 1]);
		strcpy_s(mid_sudo1[init + 1], sudo[init + 2]);
	}
	if (n == 2)
	{
		strcpy_s(mid_sudo1[init + 1], sudo[init]);
		strcpy_s(mid_sudo1[init], sudo[init + 1]);
		strcpy_s(mid_sudo1[init + 2], sudo[init + 2]);
	}
	if (n == 3)
	{
		strcpy_s(mid_sudo1[init + 1], sudo[init]);
		strcpy_s(mid_sudo1[init + 2], sudo[init + 1]);
		strcpy_s(mid_sudo1[init], sudo[init + 2]);
	}
	if (n == 4)
	{
		strcpy_s(mid_sudo1[init + 2], sudo[init]);
		strcpy_s(mid_sudo1[init], sudo[init + 1]);
		strcpy_s(mid_sudo1[init + 1], sudo[init + 2]);
	}
	if (n == 5)
	{
		strcpy_s(mid_sudo1[init + 2], sudo[init]);
		strcpy_s(mid_sudo1[init + 1], sudo[init + 1]);
		strcpy_s(mid_sudo1[init], sudo[init + 2]);
	}
}

void core::column_range(int init, int n, char mid_sudo[9][10], char sudo[9][10])
{
	int j;
	if (n == 0)
	{
		for (j = 0; j < 9; j++)
		{
			mid_sudo[j][init] = sudo[j][init];
			mid_sudo[j][init + 1] = sudo[j][init + 1];
			mid_sudo[j][init + 2] = sudo[j][init + 2];
		}
	}
	if (n == 1)
	{
		for (j = 0; j < 9; j++)
		{
			mid_sudo[j][init] = sudo[j][init];
			mid_sudo[j][init + 2] = sudo[j][init + 1];
			mid_sudo[j][init + 1] = sudo[j][init + 2];
		}
	}
	if (n == 2)
	{
		for (j = 0; j < 9; j++)
		{
			mid_sudo[j][init + 1] = sudo[j][init];
			mid_sudo[j][init] = sudo[j][init + 1];
			mid_sudo[j][init + 2] = sudo[j][init + 2];
		}
	}
	if (n == 3)
	{
		for (j = 0; j < 9; j++)
		{
			mid_sudo[j][init + 1] = sudo[j][init];
			mid_sudo[j][init + 2] = sudo[j][init + 1];
			mid_sudo[j][init] = sudo[j][init + 2];
		}
	}
	if (n == 4)
	{
		for (j = 0; j < 9; j++)
		{
			mid_sudo[j][init + 2] = sudo[j][init];
			mid_sudo[j][init] = sudo[j][init + 1];
			mid_sudo[j][init + 1] = sudo[j][init + 2];
		}
	}
	if (n == 5)
	{
		for (j = 0; j < 9; j++)
		{
			mid_sudo[j][init + 2] = sudo[j][init];
			mid_sudo[j][init + 1] = sudo[j][init + 1];
			mid_sudo[j][init] = sudo[j][init + 2];
		}
	}
}

//打印sudo_count个数独终局（在result中）
void core::print_sudo(int sudo_count, int result[][81], char* filename)//输出数独
{
	char* output = new char[163 * sudo_count + 1];
	int i, j, index = 0;
	FILE *fp;
	for (i = 0; i < sudo_count; i++)
	{
		for (j = 0; j < 81; j++)
		{
			output[index++] = result[i][j] + '0';
			if (j != 80)
			{
				if ((j + 1) % 9 == 0)
					output[index++] = '\n';
				else
					output[index++] = ' ';
			}
			else
			{
				output[index++] = '\n';
				output[index++] = '\n';
			}
		}
	}
	fopen_s(&fp, filename, "w");
	fwrite(output, 163, sudo_count, fp);
	fclose(fp);
}

int core::input(char* filename)
{
	FILE *fp;
	char s;
	int count = 0, sudonum = 0;
	fopen_s(&fp, filename, "r");
	while ((s = getc(fp)) != EOF)
	{
		if (isdigit(s))
		{
			count++;
		}
		if (count == 81)
		{
			count = 0;
			sudonum++;
		}
	}
	return sudonum;
}

//文件读取数独问题，返回数独数量，将数独存在question中
int core::input_sudo(int question[][81], char* filename)
{
	FILE *fp;
	char s;
	int count = 0, sudonum = 0;
	fopen_s(&fp, filename, "r");
	while ((s = getc(fp)) != EOF)
	{
		if (isdigit(s))
		{
			question[sudonum][count++] = (s - '0');
		}
		if (count == 81)
		{
			count = 0;
			sudonum++;
		}
	}
	return sudonum;
}

//求解sudo_count个数独（question中），将结果存在result中
void __stdcall core::solve(int sudo_count, int question[][81], int result[][81])
{
	for (int i = 0; i < sudo_count; i++)
	{
		solve(question[i], result[i]);
	}
}

//判断数独puzzle是否有解，若有解存在solution中
bool core::solve(int puzzle[81], int solution[81])
{
	//init
	int sudo[9][9], count = 0;
	option kexuan[9][9];
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			sudo[i][j] = puzzle[count++];
		}
	}
	count = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			option* xuan = new option();
			xuan->set(i, j);
			kexuan[i][j] = *xuan; //?
		}
	}
	for (int i = 0; i<9; i++)
	{
		for (int j = 0; j<9; j++)
		{
			if (sudo[i][j] != 0)
			{
				int xmin, xmax;
				int ymin, ymax;
				xmin = (i / 3) * 3;
				xmax = (i / 3 + 1) * 3;
				ymin = (j / 3) * 3;
				ymax = (j / 3 + 1) * 3;
				//remove its hang,lie
				for (int temp = 0; temp < 9; temp++)
				{
					kexuan[temp][j].remove(sudo[i][j]);
					kexuan[i][temp].remove(sudo[i][j]);

				}
				//remove its 9gongge
				for (int tempx = xmin; tempx < xmax; tempx++)
				{
					for (int tempy = ymin; tempy<ymax; tempy++)
					{
						kexuan[tempx][tempy].remove(sudo[i][j]);
					}
				}
			}
		}
	}
	//slove
	int if_solve = deal(sudo, kexuan);
	if (if_solve == -1)
		return false;
	else
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				solution[count++] = sudo[i][j];
			}
		}
		return true;
	}
}

int core::deal(int sudo[9][9], option kexuan[9][9])
{
	M = tianman(sudo);
	if (M == true)
	{
		return 1;
	}
	option jihe = findshortest(kexuan, sudo);
	int len = jihe.length();
	for (int i = 0; i < len; i++)
	{
		int number = jihe.choose(i + 1);
		sudo[jihe.x][jihe.y] = number;
		int list[22];
		for (int p = 0; p < 22; p++)
		{
			list[p] = -1;
		}
		int z = 0;
		int xmin, xmax;
		int ymin, ymax;
		xmin = (jihe.x / 3) * 3;
		xmax = (jihe.x / 3 + 1) * 3;
		ymin = (jihe.y / 3) * 3;
		ymax = (jihe.y / 3 + 1) * 3;
		//remove its hang,lie
		for (int temp = 0; temp < 9; temp++)
		{
			if (kexuan[temp][jihe.y].remove(number) == true)
			{
				list[z] = temp * 9 + jihe.y;
				z++;
			}
			if (kexuan[jihe.x][temp].remove(number) == true)
			{
				list[z] = jihe.x * 9 + temp;
				z++;
			}
		}
		//remove its 9gongge
		for (int tempx = xmin; tempx < xmax; tempx++)
		{
			for (int tempy = ymin; tempy<ymax; tempy++)
			{
				if (kexuan[tempx][tempy].remove(number) == true)
				{
					list[z] = tempx * 9 + tempy;
					z++;
				}
			}
		}
		//next solve
		int s = deal(sudo, kexuan);
		//add back
		if (s == -1) {
			int tempi = 0;
			while (list[tempi] != -1)
			{
				int xx = list[tempi] / 9;
				int yy = list[tempi] % 9;
				kexuan[xx][yy].add(number);
				tempi++;
			}
		}
		else if (s == 1)
			return 1;
	}
	if (M == false) {
		sudo[jihe.x][jihe.y] = 0;
		return -1;
	}
}

option core::findshortest(option kexuan[9][9], int sudo[9][9])
{
	int shortest = 9;
	option p;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (sudo[i][j] == 0)
			{
				int temp = kexuan[i][j].length();
				if (temp < shortest)
				{
					shortest = temp;
					p = kexuan[i][j];
				}
			}
		}
	}
	return p;
}

bool core::tianman(int sudo[9][9])
{
	for (int x = 0; x < 9; x++)
	{
		for (int y = 0; y<9; y++)
		{
			if (sudo[x][y] == 0)
			{
				return false;
			}
		}
	}
	return true;
}