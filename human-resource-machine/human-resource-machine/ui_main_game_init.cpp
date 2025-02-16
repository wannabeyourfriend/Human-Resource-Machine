/*
完成关卡的初始化
*/
#include "humanresourcemachine.h"
QMainGame::QMainGame(int level_index, QWidget* parent) : QWidget(parent) {
	//setParent(parent);
	sleep_time = kDEFAULT_SLEEP_TIME;
	cur_line = -1;
	is_paused = 0;

	// 关卡信息初始化
	level_info.level_num = level_index;
	string level_path = "../../levels/" + to_string(level_index) + ".dat";
	LEVEL* level = new LEVEL(level_path);
	level_info.box_number = level->get_box_number();
	for (int i = 0; i < level_info.box_number; i++)
		level_info.boxes.push_back(level->get_boxes(i));
	level_info.aim_out_number = level->get_aim_out_number();
	for (int i = 0; i < level_info.aim_out_number; i++)
		level_info.aim_outs.push_back(level->get_aim_outs(i));
	level_info.spare_number = level->get_spare_number();
	level_info.available_instruction_number = level->get_available_instruction_number();
	for (int i = 0; i < level_info.available_instruction_number; i++)
		level_info.available_instructions.push_back(level->get_available_instructions(i));
	delete level;
	lt_game = new QHBoxLayout();
	setLayout(lt_game);

	lt_inbox_init(level_info);
	lt_robot_n_spare_init(level_info);
	lt_outbox_init(level_info);
	lt_code_choice_init(level_info);
	lt_code_init(level_info);
	lt_pause_init();

	lt_game->addLayout(lt_inbox);
	lt_game->addStretch(1);
	lt_game->addLayout(lt_robot_n_spare);
	lt_game->addStretch(1);
	lt_game->addLayout(lt_outbox);
	lt_game->addStretch(1);
	lt_game->addLayout(lt_code_choice);
	lt_game->addStretch(1);
	lt_game->addLayout(lt_code);
	lt_game->addStretch(2);
}
