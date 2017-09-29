// Sudoku.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;
int inputcheck(int argc, char* argv[]);

void sudo_create(int sudo_count, char sudo[9][10], char changenum_array[70][5]);		//生成数独
int matrix_change(int count, int sudo_count, char sudo[9][10], char output[1000000]);	//矩阵变换
void line_range(int init, int n, char mid_sudo[9][10], char sudo[9][10]);				//行交换
void column_range(int init, int n, char mid_sudo[9][10], char sudo[9][10]);				//列变换

int solve_sudo(char output[], int count);//求解数独
bool solve_blank(int sudo_num);//填空
bool matrix_judge(int line, int column, int choose);//判断合理性

int sudo1[9][9] = { 0 };
int index0 = 0;
char  output[1000000];
int main(int argc, char* argv[])
{
	
	if (inputcheck(argc, argv) == 0) {
		return 0;
	}

	if ((strcmp(argv[1], "-c")) == 0) {
		int sudo_count = 0;								//数独终局数量
		char sudo[9][10] = { "958367124",				//数独种子
			"237451968",
			"146928357",
			"612874593",
			"573619482",
			"489235671",
			"724593816",
			"891746235",
			"365182749" };
		char changenum_array[70][5] = { "1234","1235","1236","1237","1238","1245","1246","1247","1248","1256",
			"1257","1258","1267","1268","1278","1345","1346","1347","1348","1356",
			"1357","1358","1367","1368","1378","1456","1457","1458","1467","1468",
			"1478","1567","1568","1578","1678","2345","2346","2347","2348","2356",
			"2357","2358","2367","2368","2378","2456","2457","2458","2467","2468",
			"2478","2567","2568","2578","2678","3456","3457","3458","3467","3468",
			"3478","3567","3568","3578","3678","4567","4568","4578","4678","5678" };	//交换数字的组合
		ofstream my_file("sudoku.txt", ios::out);
		my_file.close();
		sudo_count = atoi(argv[2]);
		sudo_create(sudo_count, sudo, changenum_array);
	}
	else if ((strcmp(argv[1], "-s")) == 0) {
		int i = 0, j, count = 0;
		char s;
		ofstream my_file("sudoku.txt", ios::out);
		my_file.close();
		ifstream infile(argv[2]);
		if (!infile.is_open()) {
			cout << "file cannot be opened!";
			return 0;
		}
		//	infile.open(argv[2],ios::in);
		while ((s = infile.get()) != EOF) {
			for (i = 0; i < 9; i++) {
				for (j = 0; j < 9; j++) {
					if (isdigit(s)) {
						sudo1[i][j] = (s - '0');
					}
					else {
						j--;
					}
					s = infile.get();
				}
			}
			count = solve_sudo(output, count);
		}
		if (count % 200 != 0) {
			output[index0++] = '\0';
			ofstream my_file("sudoku.txt", ios::app);
			my_file << output;
			my_file.close();
		}
		infile.close();
	}
	else {
		cout << "the second string is illegal!";
	}
	return 0;
}
int inputcheck(int argc, char* argv[]) {
	if (argc != 3) {
		cout << "the num of string is illegal!";
		return 0;
	}
	if (strcmp(argv[1], "-c") == 0) {
		if (atoi(argv[2]) < 1 || atoi(argv[2]) > 1000000) {
			cout << "the third string is illegal!";
			return 0;
		}
	}
	return 1;
}

void sudo_create(int sudo_count, char sudo[9][10], char changenum_array[70][5]) {
	int index_changenum[70] = { 0 };	//是否随机到标识符	
	char sudo_middle[9][10];				//中间种子数独
	int randnum = 0, i, j;
	int count = 0;							//已生成的数独数
	char a, b, c, d;
	for (i = 0; i<9; i++) {									//初始化
		strcpy_s(sudo_middle[i], sudo[i]);
	}
	count = matrix_change(count, sudo_count, sudo_middle, output);	//根据一个种子转换输出
	while (count < sudo_count) {
		if (count == -1) break;
		randnum = rand() % 70 + 0;
		if (index_changenum[randnum] == 0) {				//未随机到
			a = changenum_array[randnum][0];
			b = changenum_array[randnum][1];
			c = changenum_array[randnum][2];
			d = changenum_array[randnum][3];
			for (i = 0; i < 9; i++) {
				for (j = 0; j < 9; j++) {
					if (sudo[i][j] == a) {
						sudo_middle[i][j] = b;
					}
					else if (sudo[i][j] == b) {
						sudo_middle[i][j] = a;
					}
					else if (sudo[i][j] == c) {
						sudo_middle[i][j] = d;
					}
					else if (sudo[i][j] == d) {
						sudo_middle[i][j] = c;
					}
					else
						sudo_middle[i][j] = sudo[i][j];
				}
			}
			count = matrix_change(count, sudo_count, sudo_middle, output);
			if (count == -1) break;

			for (i = 0; i < 9; i++) {
				for (j = 0; j < 9; j++) {
					if (sudo[i][j] == a) {
						sudo_middle[i][j] = c;
					}
					else if (sudo[i][j] == b) {
						sudo_middle[i][j] = d;
					}
					else if (sudo[i][j] == c) {
						sudo_middle[i][j] = a;
					}
					else if (sudo[i][j] == d) {
						sudo_middle[i][j] = b;
					}
					else
						sudo_middle[i][j] = sudo[i][j];
				}
			}
			count = matrix_change(count, sudo_count, sudo_middle, output);
			if (count == -1) break;
			for (i = 0; i < 9; i++) {
				for (j = 0; j < 9; j++) {
					if (sudo[i][j] == a) {
						sudo_middle[i][j] = d;
					}
					else if (sudo[i][j] == b) {
						sudo_middle[i][j] = c;
					}
					else if (sudo[i][j] == c) {
						sudo_middle[i][j] = b;
					}
					else if (sudo[i][j] == d) {
						sudo_middle[i][j] = a;
					}
					else
						sudo_middle[i][j] = sudo[i][j];
				}
			}
			count = matrix_change(count, sudo_count, sudo_middle, output);
			if (count == -1) break;
		}
	}
	//cout << output;
}

int matrix_change(int count, int sudo_count, char sudo[9][10], char output[1000000]) {
	int line0, line1, line2, column0, column1, column2;
	int i = 3, j, k, index = 0;
	char mid_sudo[9][10];
	for (line0 = 0; line0 < 2; line0++) {
		if (line0 == 0) {
			strcpy_s(mid_sudo[0], sudo[0]);
			strcpy_s(mid_sudo[1], sudo[1]);
			strcpy_s(mid_sudo[2], sudo[2]);
		}
		if (line0 == 1) {
			strcpy_s(mid_sudo[0], sudo[0]);
			strcpy_s(mid_sudo[2], sudo[1]);
			strcpy_s(mid_sudo[1], sudo[2]);
		}
		for (line1 = 0; line1 < 6; line1++) {
			line_range(3, line1, mid_sudo, sudo);
			for (line2 = 0; line2 < 6; line1++) {
				line_range(6, line2, mid_sudo, sudo);
				for (column0 = 0; column0 < 2; column0++) {
					if (column0 == 0) {
						for (j = 0; j < 9; j++) {
							mid_sudo[j][0] = sudo[j][0];
							mid_sudo[j][1] = sudo[j][1];
							mid_sudo[j][2] = sudo[j][2];
						}
					}
					if (column0 == 1) {
						for (j = 0; j < 9; j++) {
							mid_sudo[j][0] = sudo[j][0];
							mid_sudo[j][2] = sudo[j][1];
							mid_sudo[j][1] = sudo[j][2];
						}
					}
					for (column1 = 0; column1 < 6; column1++) {
						column_range(3, column1, mid_sudo, sudo);
						for (column2 = 0; column2< 6; column2++) {
							column_range(6, column2, mid_sudo, sudo);
							for (j = 0; j < 9; j++) {
								for (k = 0; k < 9; k++) {
									output[index++] = mid_sudo[j][k];
									if (k == 8 && j != 8) {
										output[index++] = '\n';
									}
									else if (k < 8) {
										output[index++] = ' ';
									}
								}
							}
							count++;
							if (count < sudo_count) {
								output[index++] = '\n';
								output[index++] = '\n';
								if (count % 200 == 0) {
									output[index++] = '\0';
									ofstream my_file("sudoku.txt", ios::app);
									my_file << output;
									my_file.close();
									index = 0;
								}
							}
							else {
								output[index++] = '\0';
								ofstream my_file("sudoku.txt", ios::app);
								my_file << output;
								my_file.close();
								return -1;
							}
						}
					}
				}
			}
		}
	}
	return count;
}

void line_range(int init, int n, char mid_sudo[9][10], char sudo[9][10]) {
	if (n == 0) {
		strcpy_s(mid_sudo[init], sudo[init]);
		strcpy_s(mid_sudo[init + 1], sudo[init + 1]);
		strcpy_s(mid_sudo[init + 2], sudo[init + 2]);
	}
	if (n == 1) {
		strcpy_s(mid_sudo[init], sudo[init]);
		strcpy_s(mid_sudo[init + 2], sudo[init + 1]);
		strcpy_s(mid_sudo[init + 1], sudo[init + 2]);
	}
	if (n == 2) {
		strcpy_s(mid_sudo[init + 1], sudo[init]);
		strcpy_s(mid_sudo[init], sudo[init + 1]);
		strcpy_s(mid_sudo[init + 2], sudo[init + 2]);
	}
	if (n == 3) {
		strcpy_s(mid_sudo[init + 1], sudo[init]);
		strcpy_s(mid_sudo[init + 2], sudo[init + 1]);
		strcpy_s(mid_sudo[init], sudo[init + 2]);
	}
	if (n == 4) {
		strcpy_s(mid_sudo[init + 2], sudo[init]);
		strcpy_s(mid_sudo[init], sudo[init + 1]);
		strcpy_s(mid_sudo[init + 1], sudo[init + 2]);
	}
	if (n == 5) {
		strcpy_s(mid_sudo[init + 2], sudo[init]);
		strcpy_s(mid_sudo[init + 1], sudo[init + 1]);
		strcpy_s(mid_sudo[init], sudo[init + 2]);
	}
}

void column_range(int init, int n, char mid_sudo[9][10], char sudo[9][10]) {
	int j;
	if (n == 0) {
		for (j = 0; j < 9; j++) {
			mid_sudo[j][init] = sudo[j][init];
			mid_sudo[j][init + 1] = sudo[j][init + 1];
			mid_sudo[j][init + 2] = sudo[j][init + 2];
		}
	}
	if (n == 1) {
		for (j = 0; j < 9; j++) {
			mid_sudo[j][init] = sudo[j][init];
			mid_sudo[j][init + 2] = sudo[j][init + 1];
			mid_sudo[j][init + 1] = sudo[j][init + 2];
		}
	}
	if (n == 2) {
		for (j = 0; j < 9; j++) {
			mid_sudo[j][init + 1] = sudo[j][init];
			mid_sudo[j][init] = sudo[j][init + 1];
			mid_sudo[j][init + 2] = sudo[j][init + 2];
		}
	}
	if (n == 3) {
		for (j = 0; j < 9; j++) {
			mid_sudo[j][init + 1] = sudo[j][init];
			mid_sudo[j][init + 2] = sudo[j][init + 1];
			mid_sudo[j][init] = sudo[j][init + 2];
		}
	}
	if (n == 4) {
		for (j = 0; j < 9; j++) {
			mid_sudo[j][init + 2] = sudo[j][init];
			mid_sudo[j][init] = sudo[j][init + 1];
			mid_sudo[j][init + 1] = sudo[j][init + 2];
		}
	}
	if (n == 5) {
		for (j = 0; j < 9; j++) {
			mid_sudo[j][init + 2] = sudo[j][init];
			mid_sudo[j][init + 1] = sudo[j][init + 1];
			mid_sudo[j][init] = sudo[j][init + 2];
		}
	}
}


//求解（暴力求解）
int solve_sudo(char output[], int count) {
	int i, j;
	if (solve_blank(0)) {
		if (count != 0) {
			output[index0++] = '\n';
			output[index0++] = '\n';
		}
		for (i = 0; i < 9; i++) {
			for (j = 0; j < 9; j++) {
				output[index0++] = sudo1[i][j] + '0';
				if (j == 8 && i != 8) {
					output[index0++] = '\n';
				}
				else if (j < 8) {
					output[index0++] = ' ';
				}
			}
		}
		count++;
		if (count % 200 == 0) {
			output[index0++] = '\0';
			ofstream my_file("sudoku.txt", ios::app);
			my_file << output;
			my_file.close();
			index0 = 0;
		}
		return count;
	}
	cout << "no answer!";
	return 0;

}

//填数
bool solve_blank(int sudo_num) {
	int line, column, i;
	line = sudo_num / 9;
	column = sudo_num % 9;
	if (sudo_num >= 81)
		return true;
	if (sudo1[line][column] == 0) {
		for (i = 1; i <= 9; i++) {
			sudo1[line][column] = i;
			if (matrix_judge(line, column, i)) {
				if (solve_blank(sudo_num + 1)) return true;
			}
			sudo1[line][column] = 0;
		}
	}
	else {
		return solve_blank(sudo_num + 1);
	}
	return false;
}

//是否符合规则，行列块
bool matrix_judge(int line, int column, int choose) {
	int i, j, line_block, column_block;
	line_block = line / 3;
	column_block = column / 3;
	for (i = 0; i < 9; i++) {
		if (((sudo1[line][i] == choose) && i != column) || ((sudo1[i][column] == choose) && i != line))
			return false;
	}
	for (i = line_block * 3; i < line_block * 3 + 3; i++) {
		for (j = column_block * 3; j < column_block * 3 + 3; j++) {
			if (sudo1[i][j] == choose && (i != line || j != column))
				return false;
		}
	}
	return true;
}

