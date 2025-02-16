#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>

using namespace std;

// input_and_output.h
const int kMAX_NUMBER_OF_INSTRUCTIONS = 1005;

int input(int *, int *, string[]);
//
// input_and_output.cpp
int input(int *level_number, int *number_of_instructions, string instructions[kMAX_NUMBER_OF_INSTRUCTIONS])
{
    scanf("%d", level_number);
    scanf("%d", number_of_instructions);
    string temp;
    getline(cin,temp);
    for (int i = 0; i < *number_of_instructions; i++)
    {
        string input_str;      // 至多1004长度
        getline(cin,input_str); // 更保守一点
        instructions[i] = input_str;
        int j;
        for (j = instructions[i].length() - 1; j > 0; j--)
            if ((instructions[i][j] >= '0' && instructions[i][j] <= '9') || (instructions[i][j] >= 'a' && instructions[i][j] <= 'z') || (instructions[i][j] >= 'A' && instructions[i][j] <= 'Z'))
                break;
        instructions[i] = instructions[i].substr(0, j + 1);
    }
    return 1;
}
//
// robot_system_generation.h
const int kMAX_BOX_NUMBER = 15;                       // 积木最大数量
const int kMAX_SPARE_NUMBER = 4;                      // 空地最大数量
const int kMAX_NUMBER_OF_AVAILABLE_INSTRUCTIONS = 10; // 最大可用指令数
const int kMAX_NUMBER_OF_LEVEL = 3;                   // 最大关卡数
const int kMAX_INSTRUCTION_LENGTH = 15;               // 最长指令长度

class ROBOTSYSTEM;

class LEVEL
{
private:
    // 注意，为了读取方便且不使用队列，这里的积木输入是反过来的。如：-3,2,1,5在boxes中记为5,1,2,-3；目标输出等的存储就是顺序的了
    int boxes[kMAX_BOX_NUMBER], box_number;                               // 积木及其当前数量
    int aim_outs[kMAX_BOX_NUMBER], aim_out_number;                        // 目标输出及其积木数
    int spare_number;                                                     // 可用空地数
    string available_instructions[kMAX_NUMBER_OF_AVAILABLE_INSTRUCTIONS]; // 可用指令
    int available_instruction_number;                                     // 可用指令数量
public:
    LEVEL(const int boxes_input[], int box_number_input,
          const int aim_outs_input[], int aim_out_number_input,
          int spare_number_input,
          const string available_instructions_input[], int available_instruction_number_input); // 自定义关卡初始化
    LEVEL(int level_num);                                                                   // 默认关卡初始化
    ~LEVEL();
    friend class ROBOTSYSTEM; // 让后一个类可以直接访问关卡信息
};

class ROBOTSYSTEM
{
private:
    LEVEL *level;                                                       // 关卡信息
    int spares[kMAX_SPARE_NUMBER];                                      // 空地上的积木
    bool used_spares[kMAX_SPARE_NUMBER];                                // 所有被占用的空地
    int outs[kMAX_BOX_NUMBER], out_number;                              // 输出及其当前积木数
    int (ROBOTSYSTEM::*instructions[kMAX_NUMBER_OF_INSTRUCTIONS])(int); // 指令
    int instruction_operators[kMAX_NUMBER_OF_INSTRUCTIONS];             // 指令带操作数时
    int instruction_number;                                             // 指令数量
    int robot_number;                                                   // 机器人手上的数字
    bool is_robot_has_number;                                           // 机器人头上是否真的有数字
    int execute_number;                                                 // 指令执行到的位置
public:
    ROBOTSYSTEM(LEVEL *l);                                                              // 初始化
    ~ROBOTSYSTEM();                                                                     // 不太需要写，非指针会在delete时候一并释放
    void instructions_input(int instruction_number_input, string instructions_input[]); // 将用户的程序写入，并转化为函数数组和操作数
    int execution();                                                                    // 合返回0为fail，返回1为success，返回-x为error on instruction x

    int inbox(int); // 指令能执行，且程序不中止，返回1；能执行但中止返回0；不能执行（异常）返回负数，负数的值是异常的内容
    int outbox(int);
    int add(int);
    int sub(int);
    int copyto(int);
    int copyfrom(int);
    int jump(int);
    int jumpifzero(int);
    int undefined(int); // 未定义指令
};
//
// robot_system_generation.cpp
LEVEL::LEVEL(const int boxes_input[], int box_number_input, const int aim_outs_input[], int aim_out_number_input, int spare_number_input, const string available_instructions_input[], int available_instruction_number_input)
{
    box_number = box_number_input;
    for (int i = box_number - 1; i > -1; i--)
        boxes[i] = boxes_input[i];
    aim_out_number = aim_out_number_input;
    for (int i = 0; i < aim_out_number; i++)
        aim_outs[i] = aim_outs_input[i];
    spare_number = spare_number_input;
    available_instruction_number = available_instruction_number_input;
    for (int i = 0; i < available_instruction_number; i++)
        available_instructions[i] = available_instructions_input[i];
}

LEVEL::LEVEL(int level_num)
{
    if (level_num == 1)
    {
        box_number = 2;
        boxes[0] = 2, boxes[1] = 1;
        aim_out_number = 2;
        aim_outs[0] = 1, aim_outs[1] = 2;
        spare_number = 0;
        available_instruction_number = 2;
        available_instructions[0] = "inbox", available_instructions[1] = "outbox";
    }
    else if (level_num == 2)
    {
        box_number = 8;
        boxes[0] = -9,boxes[1] = 9,boxes[2] = -2,boxes[3] = -2;
        boxes[4] = 1,boxes[5] = 5,boxes[6] = 9, boxes[7] = 3;
        aim_out_number = 8;
        aim_outs[0] = -6, aim_outs[1] = 6,aim_outs[2] = 4, aim_outs[3] = -4;
        aim_outs[4] = 0, aim_outs[5] = 0,aim_outs[6] = 18, aim_outs[7] = -18;
        spare_number = 3;
        available_instruction_number = 8;
        available_instructions[0] = "inbox", available_instructions[1] = "outbox";
        available_instructions[2] = "copyfrom", available_instructions[3] = "copyto";
        available_instructions[4] = "add", available_instructions[5] = "sub";
        available_instructions[6] = "jump", available_instructions[7] = "jumpifzero";
    }
    else if (level_num == 3)
    {
        box_number = 8;
        boxes[0] = -3,boxes[1] = -3,boxes[2] = 3,boxes[3] = -9;
        boxes[4] = 7,boxes[5] = 7,boxes[6] = 2, boxes[7] = 6;
        aim_out_number = 2;
        aim_outs[0] = 7, aim_outs[1] = -3;
        spare_number = 3;
        available_instruction_number = 8;
        available_instructions[0] = "inbox", available_instructions[1] = "outbox";
        available_instructions[2] = "copyfrom", available_instructions[3] = "copyto";
        available_instructions[4] = "add", available_instructions[5] = "sub";
        available_instructions[6] = "jump", available_instructions[7] = "jumpifzero";
    }
}

LEVEL::~LEVEL()
{
}

ROBOTSYSTEM::ROBOTSYSTEM(LEVEL *l)
{
    level = l;
    for (int i = 0; i < level->spare_number; i++)
        used_spares[i] = false;
    out_number = 0;
    is_robot_has_number = 0;
    execute_number = 0;
}

ROBOTSYSTEM::~ROBOTSYSTEM()
{
}

void ROBOTSYSTEM::instructions_input(int instruction_number_input, string instructions_input[])
{
    instruction_number = instruction_number_input;
    // 初始化函数数组
    for (int i = 0; i < instruction_number; i++)
    {
        bool p = false;
        string instruction_name = instructions_input[i];
        for (int j = 0; j < instructions_input[i].length(); j++)
        {
            if (instructions_input[i][j] == ' ')
            {
                instruction_name = instructions_input[i].substr(0, j);
                break;
            }
        }
        for (int j = 0; j < level->available_instruction_number; j++)
        {
            if (instruction_name == level->available_instructions[j])
            {
                p = true;
                break;
            }
        }
        if (!p)
        {
            instructions[i] = &ROBOTSYSTEM::undefined;
            instruction_operators[i] = -1;
        }
        else if (instructions_input[i] == "inbox")
        {
            instructions[i] = &ROBOTSYSTEM::inbox;
            instruction_operators[i] = -1;
        }
        else if (instructions_input[i] == "outbox")
        {
            instructions[i] = &ROBOTSYSTEM::outbox;
            instruction_operators[i] = -1;
        }
        else if (instructions_input[i].substr(0, 4) == "add ")
        {
            instructions[i] = &ROBOTSYSTEM::add;
            instruction_operators[i] = 0;
            int nonspace_position = 4; // 第一个可能不是空格的元素
            for (; nonspace_position < instructions_input[i].length(); nonspace_position++)
            { // 找第一个不是空格的元素
                if (instructions_input[i][nonspace_position] != ' ')
                    break;
            }
            if (nonspace_position == instructions_input[i].length())
            {                                  // 全是空格
                instruction_operators[i] = -1; // 传入-1，在add函数处理
            }
            else
            {
                string operator_str = instructions_input[i].substr(nonspace_position); // 把数字部分子串提取出来
                for (int j = 0; j < operator_str.length(); j++)
                {
                    if (operator_str[j] < '0' || operator_str[j] > '9')
                    {
                        instruction_operators[i] = -1;
                        break;
                    }
                }
                if (instruction_operators[i] != -1) // 的确都是数字
                {
                    instruction_operators[i] = atoi(operator_str.c_str());
                }
            }
        }
        else if (instructions_input[i].substr(0, 4) == "sub ")
        {
            instructions[i] = &ROBOTSYSTEM::sub;
            instruction_operators[i] = 0;
            int nonspace_position = 4; // 第一个可能不是空格的元素
            for (; nonspace_position < instructions_input[i].length(); nonspace_position++)
            { // 找第一个不是空格的元素
                if (instructions_input[i][nonspace_position] != ' ')
                    break;
            }
            if (nonspace_position == instructions_input[i].length())
            {                                  // 全是空格
                instruction_operators[i] = -1; // 传入-1，在sub函数处理
            }
            else
            {
                string operator_str = instructions_input[i].substr(nonspace_position); // 把数字部分子串提取出来
                for (int j = 0; j < operator_str.length(); j++)
                {
                    if (operator_str[j] < '0' || operator_str[j] > '9')
                    {
                        instruction_operators[i] = -1;
                        break;
                    }
                }
                if (instruction_operators[i] != -1) // 的确都是数字
                {
                    instruction_operators[i] = atoi(operator_str.c_str());
                }
            }
        }
        else if (instructions_input[i].substr(0, 7) == "copyto ")
        {
            instructions[i] = &ROBOTSYSTEM::copyto;
            instruction_operators[i] = 0;
            int nonspace_position = 7; // 第一个可能不是空格的元素
            for (; nonspace_position < instructions_input[i].length(); nonspace_position++)
            { // 找第一个不是空格的元素
                if (instructions_input[i][nonspace_position] != ' ')
                    break;
            }
            if (nonspace_position == instructions_input[i].length())
            {                                  // 全是空格
                instruction_operators[i] = -1; // 传入-1，在copyto函数处理
            }
            else
            {
                string operator_str = instructions_input[i].substr(nonspace_position); // 把数字部分子串提取出来
                for (int j = 0; j < operator_str.length(); j++)
                {
                    if (operator_str[j] < '0' || operator_str[j] > '9')
                    {
                        instruction_operators[i] = -1;
                        break;
                    }
                }
                if (instruction_operators[i] != -1) // 的确都是数字
                {
                    instruction_operators[i] = atoi(operator_str.c_str());
                }
            }
        }
        else if (instructions_input[i].substr(0, 9) == "copyfrom ")
        {
            instructions[i] = &ROBOTSYSTEM::copyfrom;
            instruction_operators[i] = 0;
            int nonspace_position = 9; // 第一个可能不是空格的元素
            for (; nonspace_position < instructions_input[i].length(); nonspace_position++)
            { // 找第一个不是空格的元素
                if (instructions_input[i][nonspace_position] != ' ')
                    break;
            }
            if (nonspace_position == instructions_input[i].length())
            {                                  // 全是空格
                instruction_operators[i] = -1; // 传入-1，在copyfrom函数处理
            }
            else
            {
                string operator_str = instructions_input[i].substr(nonspace_position); // 把数字部分子串提取出来
                for (int j = 0; j < operator_str.length(); j++)
                {
                    if (operator_str[j] < '0' || operator_str[j] > '9')
                    {
                        instruction_operators[i] = -1;
                        break;
                    }
                }
                if (instruction_operators[i] != -1) // 的确都是数字
                {
                    instruction_operators[i] = atoi(operator_str.c_str());
                }
            }
        }
        else if (instructions_input[i].substr(0, 5) == "jump ")
        {
            instructions[i] = &ROBOTSYSTEM::jump;
            instruction_operators[i] = 0;
            int nonspace_position = 5; // 第一个可能不是空格的元素
            for (; nonspace_position < instructions_input[i].length(); nonspace_position++)
            { // 找第一个不是空格的元素
                if (instructions_input[i][nonspace_position] != ' ')
                    break;
            }
            if (nonspace_position == instructions_input[i].length())
            {                                  // 全是空格
                instruction_operators[i] = -1; // 传入-1，在jump函数处理
            }
            else
            {
                string operator_str = instructions_input[i].substr(nonspace_position); // 把数字部分子串提取出来
                for (int j = 0; j < operator_str.length(); j++)
                {
                    if (operator_str[j] < '0' || operator_str[j] > '9')
                    {
                        instruction_operators[i] = -1;
                        break;
                    }
                }
                if (instruction_operators[i] != -1) // 的确都是数字
                {
                    instruction_operators[i] = atoi(operator_str.c_str());
                }
            }
        }
        else if (instructions_input[i].substr(0, 11) == "jumpifzero ")
        {
            instructions[i] = &ROBOTSYSTEM::jumpifzero;
            instruction_operators[i] = 0;
            int nonspace_position = 11; // 第一个可能不是空格的元素
            for (; nonspace_position < instructions_input[i].length(); nonspace_position++)
            { // 找第一个不是空格的元素
                if (instructions_input[i][nonspace_position] != ' ')
                    break;
            }
            if (nonspace_position == instructions_input[i].length())
            {                                  // 全是空格
                instruction_operators[i] = -1; // 传入-1，在sub函数处理
            }
            else
            {
                string operator_str = instructions_input[i].substr(nonspace_position); // 把数字部分子串提取出来
                for (int j = 0; j < operator_str.length(); j++)
                {
                    if (operator_str[j] < '0' || operator_str[j] > '9')
                    {
                        instruction_operators[i] = -1;
                        break;
                    }
                }
                if (instruction_operators[i] != -1) // 的确都是数字
                {
                    instruction_operators[i] = atoi(operator_str.c_str());
                }
            }
        }
    }
}

int ROBOTSYSTEM::execution() // 返回0为fail，返回1为success，返回-x为error on instruction x
{
    // 执行运算
    int execute_count = 0; // 统计指令执行了多少条，为了防止死循环
    for (execute_number = 0; execute_number < instruction_number; execute_number++)
    {
        int p = (this->*(instructions[execute_number]))(instruction_operators[execute_number]); // 调用函数，获取返回值
        // 返回值为1，表示正常执行；返回值为0，表示结束执行；返回值为-1，表示出错
        if (p == 0) // 程序终止了
            break;
        if (p == -1) // 程序异常
            return -(execute_number + 1);
        execute_count++;
        if (execute_count > 100000)
            return 0; // 死循环，直接返回fail
    }
    // 判断合法
    if (level->aim_out_number == out_number)
    {
        for (int i = 0; i < out_number; i++)
        {
            if (level->aim_outs[i] != outs[i]) // 如果有一个不一样
                return 0;
        }
        return 1; // 都一样
    }
    else
    { // 数量都不一样，肯定错了
        return 0;
    }
}

int ROBOTSYSTEM::inbox(int op) // op是操作数
{
    if (level->box_number == 0)                         // 输入传送带上没有积木
        return 0;                                       // 符合“能执行但中止”，返回0
    robot_number = level->boxes[level->box_number - 1]; // 拿起积木
    level->box_number--;                                // 积木数量-1
    is_robot_has_number = true;                         // 机器人手上有积木
    return 1;                                           // 符合“能执行未中止”，返回1
}

int ROBOTSYSTEM::outbox(int op)
{
    if (!is_robot_has_number)        // 如果机器人手上没有积木
        return -1;                   // 异常：没有当前积木
    outs[out_number] = robot_number; // 输出积木
    out_number++;                    // 输出积木数量+1
    is_robot_has_number = false;     // 机器人手上没有积木
    return 1;                        // 符合“能执行未中止”，返回1
}

int ROBOTSYSTEM::add(int op)
{
    if (op < 0 || op >= level->spare_number || !is_robot_has_number) // 空地为负编号或者超过空地数的编号；或机器人头上没有数字
        return -1;                                                   // 操作数都没有/范围外，不能执行，返回-1
    if (!used_spares[op])                                            // 如果空地上没有积木
        return -1;
    robot_number += spares[op];
    return 1;
}

int ROBOTSYSTEM::sub(int op)
{
    if (op < 0 || op >= level->spare_number || !is_robot_has_number) // 空地为负编号或者超过空地数的编号；或机器人头上没有数字
        return -1;                                                   // 操作数都没有/范围外，不能执行，返回-1
    if (!used_spares[op])                                            // 如果空地上没有积木
        return -1;
    robot_number -= spares[op];
    return 1;
}

int ROBOTSYSTEM::copyto(int op)
{
    if (op < 0 || op >= level->spare_number || !is_robot_has_number) // 空地为负编号（也就是特殊字符的-1）或者超过空地数的编号；或机器人头上没有数字
        return -1;                                                   // 操作数都没有/范围外，不能执行，返回-1
    used_spares[op] = true;
    spares[op] = robot_number;
    return 1;
}

int ROBOTSYSTEM::copyfrom(int op)
{
    if (op < 0 || op >= level->spare_number) // 空地为负编号（也就是特殊字符的-1）或者超过空地数的编号
        return -1;                           // 操作数都没有/范围外，不能执行，返回-1
    if (!used_spares[op])                    // 如果空地没有积木
        return -1;
    is_robot_has_number = true;
    robot_number = spares[op];
    return 1;
}

int ROBOTSYSTEM::jump(int op)
{
    if (op <= 0 || op > instruction_number || op == execute_number + 1) // 没得跳转或自跳转
        return -1;
    execute_number = op - 2; // 注意这里的op很复杂，op表示的是第x条指令，对应的指令数是x-1，而马上executr_number会++，于是要再-1
    return 1;
}

int ROBOTSYSTEM::jumpifzero(int op)
{
    if (!is_robot_has_number || op <= 0 || op > instruction_number || op == execute_number + 1)
        return -1;
    if (robot_number != 0)
        return 1; // 直接返回
    execute_number = op - 2;
    return 1;
}

int ROBOTSYSTEM::undefined(int op)
{
    return -1; // 不合法指令
}
//
// main.cpp
int main()
{
    int *level_number = new int;
    int *instruction_number = new int;
    string instructions[kMAX_NUMBER_OF_INSTRUCTIONS];
    int p = input(level_number, instruction_number, instructions);
    if (*level_number < 1 || *level_number > 3)
        cout << "Failed to fetch level file!" << endl;
    else
    {
        LEVEL *level = new LEVEL(*level_number);                            // 初始化
        ROBOTSYSTEM robot_system(level);                                    // 初始化系统
        robot_system.instructions_input(*instruction_number, instructions); // 读取用户指令
        int isSuccess = robot_system.execution();                           // 运行
        if (isSuccess == 1)
            cout << "Success" << endl;
        else if (isSuccess == 0)
            cout << "Fail" << endl;
        else if (isSuccess < 0)
            cout << "Error on instruction " << (-isSuccess) << endl;
    }
    return 0;
}