#pragma once
#include "input_and_output.h"
using namespace std;

const int kMAX_BOX_NUMBER = 150005;                   // 积木最大数量
const int kMAX_SPARE_NUMBER = 4;                      // 空地最大数量
const int kMAX_NUMBER_OF_AVAILABLE_INSTRUCTIONS = 10; // 最大可用指令数
const int kMAX_NUMBER_OF_LEVEL = 4;                   // 最大关卡数
const int kMAX_INSTRUCTION_LENGTH = 150005;           // 最长指令长度

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
	LEVEL(string level_path);                                                                   // 默认关卡初始化
	int get_box_number();
	int get_boxes(int index);
	int get_aim_out_number();
	int get_aim_outs(int index);
	int get_spare_number();
	string get_available_instructions(int index);
	int get_available_instruction_number();
	friend class ROBOTSYSTEM; // 让后一个类可以直接访问关卡信息
};

class ROBOTSYSTEM
{
private:
	LEVEL* level;                                                        // 关卡信息
	int spares[kMAX_SPARE_NUMBER];                                       // 空地上的积木
	bool used_spares[kMAX_SPARE_NUMBER];                                 // 所有被占用的空地
	int outs[kMAX_BOX_NUMBER], out_number;                               // 输出及其当前积木数
	int (ROBOTSYSTEM::* instructions[kMAX_NUMBER_OF_INSTRUCTIONS])(int); // 指令
	int instruction_operators[kMAX_NUMBER_OF_INSTRUCTIONS];              // 指令带操作数时
	int instruction_number;                                              // 指令数量
	int robot_number;                                                    // 机器人手上的数字
	bool is_robot_has_number;                                            // 机器人头上是否真的有数字
	int execute_number;                                                  // 指令执行到的位置
public:
	ROBOTSYSTEM(LEVEL* l);                                                              // 初始化
	~ROBOTSYSTEM();                                                                     // 不太需要写，非指针会在delete时候一并释放
	void instructions_input(int instruction_number_input, string instructions_input[]); // 将用户的程序写入，并转化为函数数组和操作数
	int execution();                                                                    // 返回0为fail，返回1为success，返回-x为error on instruction x

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