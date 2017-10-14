#include "stdafx.h"
#include "CppUnitTest.h"
#include "../sudoku/Core.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(generate1)
		{
			// TODO: 在此输入测试代码
			core core0;
			int result[100][81];
			int sudo[9][9];
			core0.generate(100, result);
			for (int i = 0; i < 100; i++)
			{
				memcpy(sudo, result[i], sizeof(sudo));
				Assert::AreEqual(core0.isvalid(sudo), true);
			}
			Assert::AreEqual(core0.isunique(100, result), true);
		}
		TEST_METHOD(generate2)
		{
			// TODO: 在此输入测试代码
			core core0;
			int result[100][81];
			int sudo[9][9];
			for (int i = 1; i <= 3; i++)
			{
				core0.generate(100, i, result);
				for (int k = 0; k < 100; k++)
				{
					memcpy(sudo, result[k], sizeof(sudo));
					Assert::AreEqual(core0.isvalid(sudo), true);
					int count = 0;
					for (int j = 0; j < 81; j++)
					{
						if (result[k][j] == 0) count++;
					}
					if (i == 1)
					{
						Assert::AreEqual(count >= 11 && count<29, true);
					}
					if (i == 2)
					{
						Assert::AreEqual(count >= 29 && count <47, true);
					}
					if (i == 3)
					{
						Assert::AreEqual(count >= 47 && count <65, true);
					}
				}
			}
		}
		TEST_METHOD(generate3)
		{
			// TODO: 在此输入测试代码
			core core0;
			int result[100][81];
			int sudo[9][9];
			int lower = 22, upper = 45;
			core0.generate(100, lower, upper, false, result);
			for (int i = 0; i < 100; i++)
			{
				memcpy(sudo, result[i], sizeof(sudo));
				Assert::AreEqual(core0.isvalid(sudo), true);
				int count = 0;
				for (int j = 0; j < 81; j++)
				{
					if (result[i][j] == 0) count++;
				}
				Assert::AreEqual(count >= lower&&count <= upper, true);
			}
			core0.generate(100, lower, upper, true, result);
			for (int i = 0; i < 100; i++)
			{
				memcpy(sudo, result[i], sizeof(sudo));
				Assert::AreEqual(core0.isvalid(sudo), true);
				int count = 0;
				for (int j = 0; j < 81; j++)
				{
					if (result[i][j] == 0) count++;
				}
				Assert::AreEqual(count >= lower&&count <= upper, true);
			}
		}
		TEST_METHOD(solve)
		{
			// TODO: 在此输入测试代码
			core core0;
			int result[1][81];
			int sudo[81];
			int lower = 22, upper = 45;
			core0.generate(1, 1, result);
			Assert::AreEqual(core0.solve(result[0], sudo), true);
			core0.generate(1, 2, result);
			Assert::AreEqual(core0.solve(result[0], sudo), true);
			core0.generate(1, 3, result);
			Assert::AreEqual(core0.solve(result[0], sudo), true);
			core0.generate(1, lower, upper, false, result);
			Assert::AreEqual(core0.solve(result[0], sudo), true);
		}
		TEST_METHOD(isvalid)
		{
			// TODO: 在此输入测试代码
			core core0;
			int sudo[9][9] = { 9,5,8,3,6,7,1,2,4,
				2,3,7,4,5,1,9,6,8,
				1,4,6,9,2,8,3,5,7,
				6,1,2,8,7,4,5,9,3,
				5,7,3,6,1,9,4,8,2,
				4,8,9,2,3,5,6,7,1,
				7,2,4,5,9,3,8,1,6,
				8,9,1,7,4,6,2,3,5,
				3,6,5,1,8,2,7,4,9
			};
			bool s = core0.isvalid(sudo);
			Assert::IsTrue(s);
		}
		TEST_METHOD(input_sudo)
		{
			// TODO: 在此输入测试代码
			core core0;
			int sudo[9][9] = { 9,5,8,3,6,7,1,2,4,
				2,3,7,4,5,1,9,6,8,
				1,4,6,9,2,8,3,5,7,
				6,1,2,8,7,4,5,9,3,
				5,7,3,6,1,9,4,8,2,
				4,8,9,2,3,5,6,7,1,
				7,2,4,5,9,3,8,1,6,
				8,9,1,7,4,6,2,3,5,
				3,6,5,1,8,2,7,4,9
			};
			int result[1][81];
			int result1[1][81];
			memcpy(result1[0], sudo, sizeof(result1[0]));
			core0.input_sudo(result, "su.txt");
			for (int i = 0; i<81; i++)
				Assert::AreEqual(result[0][i], result1[0][i]);
		}
		TEST_METHOD(print_sudo)
		{
			// TODO: 在此输入测试代码
			core core0;
			int sudo[9][9] = { 9,5,8,3,6,7,1,2,4,
				2,3,7,4,5,1,9,6,8,
				1,4,6,9,2,8,3,5,7,
				6,1,2,8,7,4,5,9,3,
				5,7,3,6,1,9,4,8,2,
				4,8,9,2,3,5,6,7,1,
				7,2,4,5,9,3,8,1,6,
				8,9,1,7,4,6,2,3,5,
				3,6,5,1,8,2,7,4,9
			};
			int result[1][81];
			int result1[1][81];
			memcpy(result[0], sudo, sizeof(result[0]));
			core0.print_sudo(1, result, "su1.txt");
			core0.input_sudo(result1, "su1.txt");
			for (int i = 0; i < 81; i++) {
				Assert::AreEqual(result[0][i], result1[0][i]);
			}
		}


		TEST_METHOD(input_deal)
		{
			// TODO: 在此输入测试代码
			core core0;
			char *s_c0[2] = { "-c","dgh" };//-1  -C num 
			char *s_c1[2] = { "-c","1000001" };//-1
			char *s_s[2] = { "-s","fhdfjh" };//-2  -S file
			char *s_n[4] = { "-n","10001","-m","1" };//-3 -n num
			char *s_m[4] = { "-n","1","-m","4" };//-4 -m num
			char *s_r[4] = { "-n","1","-r","20~56" };//-5 -r num
			char *s_rm[6] = { "-n","1","-r","20~56","-m","1" }; //-6 -m -r
			Assert::AreEqual(core0.input_deal(2, s_c0), -1);
			Assert::AreEqual(core0.input_deal(2, s_c1), -1);
			Assert::AreEqual(core0.input_deal(2, s_s), -2);
			Assert::AreEqual(core0.input_deal(4, s_n), -3);
			Assert::AreEqual(core0.input_deal(4, s_m), -4);
			//	Assert::AreEqual(core0.input_deal(4, s_r), -5);
			//	Assert::AreEqual(core0.input_deal(6, s_rm), -6);
		}
	};
}