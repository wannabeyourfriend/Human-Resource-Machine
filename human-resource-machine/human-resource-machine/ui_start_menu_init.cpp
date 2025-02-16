/*
实现游戏启动界面，包括游戏介绍、游戏操作说明、游戏开始按钮等。

 QVBoxLayout* ui_start_menu;
 QPushButton* btn_start;
 QPushButton* btn_exit_in_start;

*/
#include "humanresourcemachine.h"
void humanresourcemachine::ui_start_menu_init() {

    ui_start_menu = new QVBoxLayout();
    //加载背景组件
    QString background_image_path = "../../img/start_menu_background.png";
    QPixmap background_image = QPixmap(background_image_path);
    QLabel* background_label = new QLabel;
    background_label->setPixmap(background_image);
    background_label->setScaledContents(true); // 图片自适应大小
    background_label->setAlignment(Qt::AlignCenter); // 使图片居中
    ui_start_menu->addWidget(background_label);


    //创建背景和按钮的父容器
    QWidget* containerWidget = new QWidget;
    containerWidget->setLayout(ui_level_select);


    // 水平布局用于放置各个级别按钮和返回按钮
    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->setAlignment(Qt::AlignCenter);

    const QString buttonStyles[] = {
        "background-color: #E67E5D; color: white;", // Start in Green
        "background-color: #7DBE6C; color: white;", // Exit in Red
        "background-color: #F39C12; color: white;" // continue in Yellow
    };
    // 从样式创建按钮
    //start
    btn_start = new QPushButton(tr("Start"));
    btn_start->setStyleSheet(buttonStyles[0]);
    buttonLayout->addWidget(btn_start);
    //exit
    btn_exit_in_start = new QPushButton(tr("Exit"));
    btn_exit_in_start->setStyleSheet(buttonStyles[1]);
    buttonLayout->addWidget(btn_exit_in_start);
    //conntinue
    btn_continue = new QPushButton(tr("Continue"));
    btn_continue->setStyleSheet(buttonStyles[2]);
    buttonLayout->addWidget(btn_continue);
    // 设置按钮间距
    buttonLayout->setSpacing(20);

    QWidget* buttonWidget = new QWidget;
    buttonWidget->setLayout(buttonLayout);
    buttonWidget->setStyleSheet("background: transparent;"); // 设置背景透明
    buttonWidget->setGeometry(0, this->height() - 100, this->width(), 100); // 设置按钮容器的位置

    ui_start_menu->addWidget(buttonWidget);


    //connect signal and slot
    connect(btn_start, SIGNAL(clicked()), this, SLOT(start_game()));
    connect(btn_exit_in_start, SIGNAL(clicked()), this, SLOT(exit_game()));
    connect(btn_continue, SIGNAL(clicked()), this, SLOT(start_game_from_continue()));

    return;
}

void humanresourcemachine::start_game() {
    // 切换到关卡选择界面
    if (stackedWidget != nullptr) {
        stackedWidget->setCurrentIndex(1);
    }
    else {
        // Handle the error appropriately
        std::cout << "stackedWidget is not initialized." << std::endl;
    }

}
void humanresourcemachine::start_game_from_continue() {
    if (player_progress->isCompleted) {
        QMessageBox::information(this, "Game Complete", "Congratulations! You have completed all levels.");
        // 切换到关卡选择界面
        if (stackedWidget != nullptr) {
            stackedWidget->setCurrentIndex(1);
        }
        else {
            // Handle the error appropriately
            std::cout << "stackedWidget is not initialized." << std::endl;
        }
    }
    else {
        int current_level = player_progress->currentLevel;
        // 切换到当前关卡
        enter_level(current_level);
    }
}

void humanresourcemachine::exit_game() {
    // 弹出退出确认对话框
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Exit", "Are you sure you want to exit?",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // 保存玩家进度
        on_game_exit(player_progress->currentLevel, player_progress->isCompleted);

        // 退出应用程序
        qApp->quit();
    }
}
