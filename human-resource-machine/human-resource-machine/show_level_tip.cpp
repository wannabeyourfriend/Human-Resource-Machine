#pragma once
#include <QWidget>
#include "humanresourcemachine.h"
#include <QMessageBox>
#include <cstring>
#include <sstream>
#include <QTextEdit>
/*
从关卡的.dat文件中读取关卡信息，并输出提示信息
*/
/*
第1关：复印楼层
### 在这一层中，你将运用inbox outbox熟悉基本操作，将输入原封不动地输出到输出箱中。
2
1 2
2
1 2
0
2
inbox outbox
第2关：左右相减器
### 在这一层中，你将要实现左右相减器：输入两个数字a和b，就要输出他们的差a-b和b-a，你将有2个空地用来寄存中间结果。
8
3 8 5 1 -2 -2 9 -9
8
-5 5 4 -4 0 0 18 -18
3
8
inbox outbox copyfrom copyto add sub jump jumpifzero
第2.b关：
8
3 9 5 1 -2 -2 9 -9
8
-6 6 4 -4 0 0 18 -18
3
8
inbox outbox copyfrom copyto add sub jump jumpifzero
@第3关：相等过滤器
### 在这一层中，你将要实现相等过滤器，输入一串数字，你将输出其中连续重复了两次的数字，你将有3个空地用来寄存中间结果。
8
6 2 7 7 -9 3 -3 -3
2
7 -3
3
8
inbox outbox copyfrom copyto add sub jump jumpifzero
第4关：
### 在这一层中，你将实现一个实现乘法器，你将输出两个数字的乘积，将有4个空地来存储中间结果
9
1 3 5 9 8 7 3 4 4
4
15 72 21 16
4
8
inbox outbox copyfrom copyto add sub jump jumpifzero
*/
//void on_show_aimout(LEVEL* level, int aim_out_number) {
//    std::stringstream aim_out_info;
//    for (int i = 0; i < aim_out_number; i++) {
//        aim_out_info << level->get_aim_outs(i) << " ";
//    }
//
//    // 弹出信息框显示目标输出
//    QMessageBox::information(nullptr, "Aim Out Information", QString::fromStdString(aim_out_info.str()));
//}


void on_close(QWidget* window) {
    window->close();
}

void humanresourcemachine::show_level_tip(int level_num) {
    string level_path = "../../levels/" + to_string(level_num) + ".dat";
    // 创建 LEVEL 对象，使用路径构造器加载关卡数据
    LEVEL* level = new LEVEL(level_path);
    // 获取关卡信息
    int box_number = level->get_box_number();
    int spare_number = level->get_spare_number();
    int aim_out_number = level->get_aim_out_number();
    int available_instruction_number = level->get_available_instruction_number();

    // 获取关卡的积木、目标输出和可用指令
    std::stringstream box_info;
    for (int i = box_number - 1; i >= 0; i--) {
        box_info << level->get_boxes(i) << " ";
    }

    /*std::stringstream aim_out_info;
    for (int i = 0; i < aim_out_number; i++) {
        aim_out_info << level.get_aim_outs(i) << " ";
    }*/

    std::stringstream instruction_info;
    for (int i = 0; i < available_instruction_number; i++) {
        instruction_info << level->get_available_instructions(i) << " ";
    }

    // 关卡描述信息
    std::vector<std::string> instructions = {
        "In this level, you will use inbox and outbox to familiarize yourself with basic operations, where the input will be output unchanged.",
        "In this level, you will implement a subtractor: input two numbers, a and b, and output their differences a-b and b-a. You will have 2 empty spaces to store intermediate results.",
        "In this level, you will implement an equality filter. Input a series of numbers, and you will output the numbers that appear consecutively twice. You will have 3 empty spaces to store intermediate results.",
        "In this level, you will implement a multiplier. You will output the product of two numbers, and you will have 4 empty spaces to store intermediate results.\nNOTICE: You will be given a \"1\" first, and we will restrict the first element of every pair is positive."
    };

    // 构建提示信息
    std::stringstream tip_message;
    tip_message << "Level " << level_num << " Information:\n";
    tip_message << "Instructions: " << instructions[level_num - 1] << "\n";
    tip_message << "Boxes: " << box_info.str() << "\n";
    tip_message << "Available Instructions: " << instruction_info.str() << "\n";
    tip_message << "Spare Spaces: " << spare_number << "\n";

    // 创建窗口
    QWidget* window = new QWidget;
    window->setWindowTitle("Level Info");

    // 创建布局管理器
    QVBoxLayout* layout = new QVBoxLayout(window);

    // 创建文本框来显示提示信息
    QTextEdit* tipTextBox = new QTextEdit(window);
    tipTextBox->setText(QString::fromStdString(tip_message.str())); // 将提示信息传入文本框
    tipTextBox->setReadOnly(true); // 设置为只读模式
    tipTextBox->setFont(QFont("Comic Sans MS", 12)); // 设置字体为微软雅黑，大小为12
    tipTextBox->setStyleSheet("background-color: #f0f0f0; border: 1px solid #cccccc; padding: 10px;");

    // 创建关闭按钮
    QPushButton* closeButton = new QPushButton("OK", window);

    // 添加控件到布局
    layout->addWidget(tipTextBox);
    layout->addWidget(closeButton);

    // 连接关闭按钮的事件处理函数
    QObject::connect(closeButton, &QPushButton::clicked, [=]() { on_close(window); });

    // 清除掉之前的所有窗口
    foreach (QWidget * widget, QApplication::topLevelWidgets()) {
        if (widget != this)
            widget->close();
    }

    // 设置布局并显示窗口
    window->setLayout(layout);
    window->show();
}