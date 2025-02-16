#pragma once
#include <QStackedWidget> // add this .h file
#include <QMainWindow>
#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QDialog> // add this .h file
#include <QListWidget>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDrag>
#include <QMimeData>
#include <QMessageBox>
#include <QWidget>
#include <QDebug>
#include <QThread>
#include <QRect>
#include <QPropertyAnimation>
#include <QGraphicsBlurEffect>
#include "ui_humanresourcemachine.h"
#include "../../BasicFunctions/robot_system_generation.h"
#include "progress.h"
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <cmath>

const int kDEFAULT_SLEEP_TIME = 1000;

class QDialogSpare : public QDialog {
    Q_OBJECT
private:
    int spare_no;
    int spares_number;
    QPushButton** btn_spares;
    QVBoxLayout* lt_dlg_spare;
public:
    QDialogSpare(int spares_number);
    int get_spare_no();
	void closeEvent(QCloseEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
public slots:
    void onButtonClicked();
};

class BackgroundWidget : public QWidget {
public:
    BackgroundWidget(string img_path, QWidget* parent = nullptr);
    void setBackgroundImage(const QString& imagePath);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QPixmap backgroundImage;
};

class QDragListWidget : public QListWidget {
    Q_OBJECT
private:
    int level_spare_num;
    vector<pair< QListWidgetItem*, QListWidgetItem*> > friends;//保存jump到的位置
public:
    QDragListWidget(int level_spare_number);
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void dragLeaveEvent(QDragLeaveEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    vector<pair< QListWidgetItem*, QListWidgetItem*> > get_friends();
public slots:
    void onItemClicked(QListWidgetItem* new_item);
    void onLabelDragged();
    void on_btn_restart_clicked();
};

class QDragLabel : public QLabel {
    Q_OBJECT
public:
    QDragLabel(QWidget* parent = nullptr);
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
signals:
    void labelDragged();
};

struct LevelInfo { // 因为LEVEL类会被ROBOTSYSTEM类修改，所以把信息都暂存到这里
	int level_num;                                                        // 关卡号
    int box_number;                                                       // 积木当前数量
	vector<int> boxes;					                            	  // 积木
    int aim_out_number;                                                   // 目标输出积木数
	vector<int> aim_outs;				                                  // 目标输出
    int spare_number;                                                     // 可用空地数
    int available_instruction_number;                                     // 可用指令数量
    vector<string> available_instructions;                                // 可用指令
};

class QMainGame : public QWidget {
    Q_OBJECT
private:
    QHBoxLayout* lt_game;
    QVBoxLayout* lt_inbox;
    QVBoxLayout* lt_outbox;
    QVBoxLayout* lt_robot_n_spare;
    QVBoxLayout* lt_code_choice;
    QVBoxLayout* lt_code;

    QVBoxLayout* lt_robot;
    QHBoxLayout* lt_spare;

    vector<QLabel*> lb_inboxes;
    vector<QLabel*> lb_outboxes;
    QLabel* lb_robox;//机器人头上的积木
    BackgroundWidget* wdg_robot_pic;//机器人的图像
    QLabel* lb_spare_boxes[kMAX_SPARE_NUMBER];
    QDragLabel* lb_code_choices[kMAX_NUMBER_OF_AVAILABLE_INSTRUCTIONS];
    QPushButton* btn_run;//运行按钮
    QPushButton* btn_pause_in_game;//游戏界面的暂停

    QDialog* ui_dlg_pause;
    QHBoxLayout* lt_pause;
    QPushButton* btn_back;//返回按钮
    QPushButton* btn_restart;//重开按钮
    QPushButton* btn_accl;//加速按钮
    QPushButton* btn_exit_in_pause;//暂停界面的退出，要返回到选关界面

    QDragListWidget* lst_code;

    LevelInfo level_info;
    int sleep_time;
    int cur_line;

    int is_paused;

public:
    QMainGame(int level_index, QWidget* parent = nullptr);
    void lt_inbox_init(LevelInfo);
    void lt_outbox_init(LevelInfo);
    void lt_robot_n_spare_init(LevelInfo);
    void lt_code_choice_init(LevelInfo);
    void lt_code_init(LevelInfo);
    void lt_robot_init();
    void lt_space_init(LevelInfo);
    void lt_pause_init();
    void ui_dlg_pause_init();

    void robot_execute_animate(int instr_num, string* instrs, int stop_num);
    void on_fail_exe();
    void on_inbox_exe(int op);
    void on_outbox_exe(int op);
    void on_add_exe(int op);
    void on_sub_exe(int op);
    void on_copyto_exe(int op);
    void on_copyfrom_exe(int op);

    void paintEvent(QPaintEvent* event) override;
    void paint_cursor(int cur_line);

    //美化数字积木
    void standardize_blocks(QLabel* lb_block);
    //美化代码块
    void standardize_code_blocks(QDragLabel* lb_code_block);
    //写一些返回组建坐标的函数
    //返回inbox,outbox,robot,spare的坐标
    QPoint get_inbox_pos(int index);
    QPoint get_outbox_pos(int index);
    QPoint get_robot_pos();
    QPoint get_spare_pos(int index);
    QPoint get_robot_pic_pos();
    //更新机器人以及它拿着的积木的位置
    void update_robot_pos(QPoint qPoint);

private slots:
    void robot_execute();//按下run时运行
    void on_btn_pause_clicked();
    void on_btn_back_clicked();
    void on_btn_restart_clicked();
    void on_btn_accl_clicked();
    void on_btn_exit_clicked();
	void on_pause_dialog_closed();
signals:
    void exit_signal();
    void game_result(int p, int level_num);
};


class humanresourcemachine : public QMainWindow
{
    Q_OBJECT

public:
    humanresourcemachine(QWidget* parent = nullptr);
    ~humanresourcemachine();

public:
    void ui_start_menu_init();
private slots:
    void start_game();
    void exit_game();
    void start_game_from_continue();
public:
    void ui_level_select_init();
private slots:
    void enter_level(int level_num);
    void exit_level();
public:
    void show_level_tip(int level_num);
public:
    void on_game_exit(int level_num, bool completed);
public slots:
    void update_progress(int p, int level_num);
    void ui_level_select_re_init();
private:
    //userProgress progress;
    PlayerProgress* player_progress;
    //Ui::humanresourcemachineClass ui;
    QStackedWidget* stackedWidget;
    QVBoxLayout* ui_start_menu;
    QVBoxLayout* ui_level_select;
    QMainGame* ui_main_games[kMAX_NUMBER_OF_LEVEL];

    QPushButton* btn_start;//点击后进入选关界面
    QPushButton* btn_exit_in_start;//开始界面的退出
    QPushButton* btn_continue;//点击后进入当前关卡(根据progress)

    QPushButton* btn_levels[kMAX_NUMBER_OF_LEVEL];//点击后进入当前关卡
    QPushButton* btn_exit_in_game;//选关界面的退出
};