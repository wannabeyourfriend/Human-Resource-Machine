#define _CRT_SECURE_NO_WARNINGS
#include "robot_system_generation.h"

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

LEVEL::LEVEL(string level_path)
{
    FILE* f = fopen(level_path.c_str(), "r");
    if (f != NULL)
    {
        fscanf(f, "%d", &box_number);
        for (int i = box_number - 1; i > -1; i--) // 倒序输入
            fscanf(f, "%d", &boxes[i]);
        fscanf(f, "%d", &aim_out_number);
        for (int i = 0; i < aim_out_number; i++) // 顺序输入
            fscanf(f, "%d", &aim_outs[i]);
        fscanf(f, "%d", &spare_number);
        fscanf(f, "%d", &available_instruction_number);
        for (int i = 0; i < available_instruction_number; i++)
        {
            char temp[kMAX_INSTRUCTION_LENGTH];
            fscanf(f, "%s", temp);
            available_instructions[i] = temp;
        }
        fclose(f);
        /* for (int i = 0; i < available_instruction_number; i++)
            cout << available_instructions[i] << endl; */
    }
}

int LEVEL::get_box_number()
{
    return box_number;
}

int LEVEL::get_boxes(int index)
{
    return boxes[index];
}

int LEVEL::get_aim_out_number()
{
    return aim_out_number;
}

int LEVEL::get_aim_outs(int index)
{
    return aim_outs[index];
}

int LEVEL::get_spare_number()
{
    return spare_number;
}

string LEVEL::get_available_instructions(int index)
{
    return available_instructions[index];
}

int LEVEL::get_available_instruction_number()
{
    return available_instruction_number;
}

ROBOTSYSTEM::ROBOTSYSTEM(LEVEL* l)
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
	delete level;
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
            if (instruction_name == level->available_instructions[j]) {
                p = true;
                break;
            }
        }
        if (!p) {
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

int ROBOTSYSTEM::execution() // 返回0为success，返回-x为严重的指令错误，不可运行动画；返回+x为fail或轻微的指令错误，且一共执行了x次
{
    // 先重启一下，把inbox和outbox重置了
    for (int i = 0; i < kMAX_SPARE_NUMBER; i++)
        used_spares[i] = false;
    out_number = 0;
    is_robot_has_number = false;
    // 执行运算
    int execute_count = 0; // 统计指令执行了多少条，为了防止死循环
    for (execute_number = 0; execute_number < instruction_number; execute_number++)
    {
        int p = (this->*(instructions[execute_number]))(instruction_operators[execute_number]); // 调用函数，获取返回值
        // 返回值为1，表示正常执行；返回值为0，表示结束执行；返回值为-1，表示出错
        if (p == 0) { // 程序终止了
            execute_count++;
            break;
        }
        else if (p == -2) {// 程序严重异常
            return -(execute_number + 1);
        }
        else if (p == -1) {// 程序轻微异常
            return execute_count + 1;
        }
        if (out_number > level->aim_out_number || (out_number != 0 && outs[out_number - 1] != level->aim_outs[out_number - 1])) { // 第一次输出不合法
            return execute_count + 1; // 为了给没运行过留个位置
        }
        execute_count++;
        if (execute_count > 100000)
            return execute_count + 1; // 死循环，直接返回fail
    }
    // 判断合法
    if (level->aim_out_number == out_number)
    {
        for (int i = 0; i < out_number; i++)
        {
            if (level->aim_outs[i] != outs[i]) // 如果有一个不一样
                return execute_count + 1; // 为了给没运行过留个位置
        }
        return 0; // 都一样
    }
    else
    { // 数量都不一样，肯定错了
        return execute_count + 1; // 为了给没运行过留个位置
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
    if (!is_robot_has_number) {      // 如果机器人手上没有积木
        return -1;                   // 异常：没有当前积木
    }
    outs[out_number] = robot_number; // 输出积木
    out_number++;                    // 输出积木数量+1
    is_robot_has_number = false;     // 机器人手上没有积木
    return 1;                        // 符合“能执行未中止”，返回1
}

int ROBOTSYSTEM::add(int op)
{
    if (op < 0 || op >= level->spare_number || !is_robot_has_number) { // 空地为负编号或者超过空地数的编号；或机器人头上没有数字
        return -1;                                                     // 操作数都没有/范围外，不能执行，返回-1
    }
    if (!used_spares[op]) {                                            // 如果空地上没有积木
        return -1;
    }
    robot_number += spares[op];
    return 1;
}

int ROBOTSYSTEM::sub(int op)
{
    if (op < 0 || op >= level->spare_number || !is_robot_has_number) { // 空地为负编号或者超过空地数的编号；或机器人头上没有数字
        return -1;                                                     // 操作数都没有/范围外，不能执行，返回-1
    }
    if (!used_spares[op]) {                                            // 如果空地上没有积木
        return -1;
    }
    robot_number -= spares[op];
    return 1;
}

int ROBOTSYSTEM::copyto(int op)
{
    if (op < 0 || op >= level->spare_number || !is_robot_has_number) { // 空地为负编号（也就是特殊字符的-1）或者超过空地数的编号；或机器人头上没有数字
        return -1;                                                     // 操作数都没有/范围外，不能执行，返回-1
    }
    used_spares[op] = true;
    spares[op] = robot_number;
    return 1;
}

int ROBOTSYSTEM::copyfrom(int op)
{
    if (op < 0 || op >= level->spare_number) { // 空地为负编号（也就是特殊字符的-1）或者超过空地数的编号
        return -1;                             // 操作数都没有/范围外，不能执行，返回-1
    }
    if (!used_spares[op]) {                    // 如果空地没有积木
        return -1;
    }
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
    return -2; // 不合法指令
}
