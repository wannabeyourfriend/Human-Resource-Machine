#include "humanresourcemachine.h"
#include "progress.h"
humanresourcemachine::humanresourcemachine(QWidget* parent)
	: QMainWindow(parent)
{
	// 设置主窗口的标题和默认大小
	setWindowTitle("Human Resource Machine");
	setFixedSize(800, 600);  // 假设窗口大小为 800x600 

	// 创建 QStackedWidget 并设置为中心部件
	stackedWidget = new QStackedWidget(this);
	setCentralWidget(stackedWidget);

	// 初始化进度管理
	player_progress = new PlayerProgress();
	player_progress->loadProgress("../../log/player_progress.json");
	//用QMessage输出一下player_progress储存了什么信息
	//QMessageBox::information(this, "Player Information", "Name: " + player_progress->name + "\nAge: " + QString::number(player_progress->age) + "\nGender: " + player_progress->gender + "\nLevel: " + QString::number(player_progress->currentLevel) + "\nCompleted: " + QString::number(player_progress->isCompleted));

	QWidget* startMenuPage = new QWidget();
	QWidget* levelSelectPage = new QWidget();


	// 初始化各个页面的 UI 部件
	ui_start_menu_init();
	ui_level_select_init();

	for (int i = 0; i < kMAX_NUMBER_OF_LEVEL; i++) {
		ui_main_games[i] = new QMainGame(i + 1, this);
		connect(ui_main_games[i], &QMainGame::exit_signal, this, &humanresourcemachine::start_game);
		//p值连接到进程管理器中
		connect(ui_main_games[i], &QMainGame::game_result, this, &humanresourcemachine::update_progress);
		//将levelselect页面刷新函数连接到返回值的按下信号
		connect(ui_main_games[i], &QMainGame::exit_signal, this, &humanresourcemachine::ui_level_select_re_init);
	}

	// 将各个页面的 UI 部件设置为布局并设置到各个页面中
	startMenuPage->setLayout(ui_start_menu);
	levelSelectPage->setLayout(ui_level_select);

	// 将各个页面添加到 QStackedWidget 中
	stackedWidget->addWidget(startMenuPage);
	stackedWidget->addWidget(levelSelectPage);
	for (int i = 0; i < kMAX_NUMBER_OF_LEVEL; i++)
		stackedWidget->addWidget(ui_main_games[i]);

	stackedWidget->setCurrentIndex(0);  // 显示起始页面
}

humanresourcemachine::~humanresourcemachine()
{
	delete player_progress;
}

void humanresourcemachine::on_game_exit(int level, bool completed) {
	// 更新玩家的进度
	player_progress->currentLevel = level + 1;  // 假设关卡从1开始，level是0基索引
	player_progress->isCompleted = completed;

	// 保存进度
	player_progress->saveProgress("../../log/player_progress.json");

}

void humanresourcemachine::ui_level_select_re_init()
{
	// 初始化一个指针指向stackedWidget中的第二个页面，即关卡选择页面
	QWidget* oldWidget = stackedWidget->widget(1);
	// 移除旧控件
	stackedWidget->removeWidget(oldWidget);
	// 初始化新控件
	ui_level_select_init();
	QWidget* newWidget = new QWidget(stackedWidget); // 创建新控件
	newWidget->setLayout(ui_level_select); // 设置新控件的布局

	stackedWidget->insertWidget(1, newWidget);
	// 切换到新控件
	stackedWidget->setCurrentIndex(1);

	//debug:弹出一个消息框
	//QMessageBox::information(this, "Congratulations", "Congratulations! You have completed the game.");

}

void humanresourcemachine::update_progress(int p, int level_num) {
	if (p == 0) {
		//如果这一局玩家之前没有完成，则通关数量+1
		if (player_progress->currentLevel == level_num) {
			player_progress->currentLevel += 1;
			if (player_progress->currentLevel > 4) {
				player_progress->isCompleted = true;
				player_progress->currentLevel = 4;
				ui_level_select_re_init(); // 自动回到选关界面
			}
			else {
				player_progress->isCompleted = false;
				enter_level(player_progress->currentLevel); // 自动进入下一关
			}
		}
	}
	player_progress->saveProgress("../../log/player_progress.json");
}