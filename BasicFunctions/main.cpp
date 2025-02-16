#include <iostream>
#include <fstream>
#include <string>
#include "robot_system_generation.h"

using namespace std;

int main()
{
    ofstream report_out = ofstream("../test/report.txt");
    for (int i = 0; i < 30; i++)
    {
        report_out << "On test " << to_string(i) << endl;
        string file_path = "../test/" + to_string(i) + ".in";
        int *level_number = new int;
        int *instruction_number = new int;
        string instructions[kMAX_NUMBER_OF_INSTRUCTIONS];
        int p = input(0, file_path, level_number, instruction_number, instructions);
        if (p == 0)
            report_out << "Failed to fetch test file!" << endl;
        else
        {
            if (*level_number < 1 || *level_number > kMAX_NUMBER_OF_LEVEL)
                report_out << "Failed to fetch level file!" << endl;
            else
            {
                string level_file_path = "../levels/" + to_string(*level_number) + ".dat";
                LEVEL *level = new LEVEL(level_file_path);                          // 初始化
                ROBOTSYSTEM robot_system(level);                                    // 初始化系统
                robot_system.instructions_input(*instruction_number, instructions); // 读取用户指令
                int isSuccess = robot_system.execution();                           // 运行
                if (isSuccess == 0)
                    report_out << "Success" << endl;
                else if (isSuccess > 0)
                    report_out << "Fail with execution times "
                         << isSuccess << endl;
                else if (isSuccess < 0)
                    report_out << "Error on instruction " << (-isSuccess) << endl;
            }
        }
        file_path = "../test/" + to_string(i) + ".out";
        FILE *f = fopen(file_path.c_str(), "r");
        char c = 0;
        while (1)
        {
            c = fgetc(f);
            if (c == EOF)
            {
                report_out << endl;
                break;
            }
            report_out << c;
        }
        fclose(f);
    }
    report_out.close();
    /* 键盘/文件输入交互
    cout << "选择键盘输入按1，选择文件输入按0：" << endl;
    int is_keyboard;
    cin >> is_keyboard;
    string file_path = "";
    if (is_keyboard == 0)
    {
        cout << "请输入文件路径：" << endl;
        cin >> file_path;
    }
    int *level_number = new int;
    int *instruction_number = new int;
    string instructions[kMAX_NUMBER_OF_INSTRUCTIONS];
    int p = input(is_keyboard, file_path, level_number, instruction_number, instructions);
    if (p == 0)
        cout << "Failed to fetch test file!" << endl;
    else
    {
        if (*level_number < 1 || *level_number > kMAX_NUMBER_OF_LEVEL)
            cout << "Failed to fetch level file!" << endl;
        else
        {
            string level_file_path = "../levels/" + to_string(*level_number) + ".dat";
            LEVEL *level = new LEVEL(level_file_path);                          // 初始化
            ROBOTSYSTEM robot_system(level);                                    // 初始化系统
            robot_system.instructions_input(*instruction_number, instructions); // 读取用户指令
            int isSuccess = robot_system.execution();                           // 运行
            if (isSuccess == 0)
                cout << "Success" << endl;
            else if (isSuccess > 0)
                cout << "Fail with execution times "
                     << isSuccess << endl;
            else if (isSuccess < 0)
                cout << "Error on instruction " << (-isSuccess) << endl;
        }
    }*/
    return 0;
}