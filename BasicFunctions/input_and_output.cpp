#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <string>
#include "input_and_output.h"

using namespace std;

int input(int is_keyboard, string file_path, int *level_number, int *number_of_instructions, string instructions[kMAX_NUMBER_OF_INSTRUCTIONS])
{
	if (is_keyboard == 1)
	{
		cout << "请输入关卡编号：" << endl;
		cin >> *level_number;
		cout << "请输入指令数量：" << endl;
		cin >> *number_of_instructions;
		cin.get();
		cout << "请输入指令：" << endl;
		for (int i = 0; i < *number_of_instructions; i++)
		{
			getline(cin, instructions[i]);
			int j;
			for (j = instructions[i].length() - 1; j > 0; j--)
				if ((instructions[i][j] >= '0' && instructions[i][j] <= '9') || (instructions[i][j] >= 'a' && instructions[i][j] <= 'z') || (instructions[i][j] >= 'A' && instructions[i][j] <= 'Z'))
					break;
			instructions[i] = instructions[i].substr(0, j + 1);
			for (j = 0; j < instructions[i].length(); j++)
				if ((instructions[i][j] >= '0' && instructions[i][j] <= '9') || (instructions[i][j] >= 'a' && instructions[i][j] <= 'z') || (instructions[i][j] >= 'A' && instructions[i][j] <= 'Z'))
					break;
			instructions[i] = instructions[i].substr(j, instructions[i].length());
		}
		return 1;
	}
	else if (is_keyboard == 0)
	{
		FILE *f = fopen(file_path.c_str(), "r");
		if (f == NULL) // 读取不到文件
			return 0;
		fscanf(f, "%d", level_number);
		fscanf(f, "%d", number_of_instructions);
		fgetc(f);
		for (int i = 0; i < *number_of_instructions; i++)
		{
			char input_str[1005];	   // 至多1004长度
			fgets(input_str, 1002, f); // 更保守一点
			instructions[i] = input_str;
			int j;
			for (j = instructions[i].length() - 1; j > 0; j--)
				if ((instructions[i][j] >= '0' && instructions[i][j] <= '9') || (instructions[i][j] >= 'a' && instructions[i][j] <= 'z') || (instructions[i][j] >= 'A' && instructions[i][j] <= 'Z'))
					break;
			instructions[i] = instructions[i].substr(0, j + 1);
			for (j = 0; j < instructions[i].length(); j++)
				if ((instructions[i][j] >= '0' && instructions[i][j] <= '9') || (instructions[i][j] >= 'a' && instructions[i][j] <= 'z') || (instructions[i][j] >= 'A' && instructions[i][j] <= 'Z'))
					break;
			instructions[i] = instructions[i].substr(j, instructions[i].length());
		}
		fclose(f);
		return 1;
	}
	else // 接收了不合法的输入
		return 0;
}