#pragma once
#include "humanresourcemachine.h"

void QMainGame::on_btn_back_clicked()
{
	ui_dlg_pause->accept();
}

void QMainGame::on_btn_restart_clicked()
{//这里还需要把所有的进程中断，并重新初始化，具体是要实现stop_threads函数，并且在每个正在进行的进程进行保护
	is_paused = -1;
	lt_inbox_init(level_info);
	lt_robot_n_spare_init(level_info);
	lt_outbox_init(level_info);
	ui_dlg_pause->accept();
}

void QMainGame::on_btn_accl_clicked()
{
	if (sleep_time > 1)
		sleep_time = sleep_time / 2;
}

void QMainGame::on_btn_exit_clicked()
{
	//humanresourcemachine::ui_level_select_init();
	on_btn_restart_clicked();//退出时自动重置关卡；不过似乎也不必要？
	emit exit_signal();
}

void QMainGame::on_pause_dialog_closed()
{
	if (is_paused == 1)
		is_paused = 0;
}
