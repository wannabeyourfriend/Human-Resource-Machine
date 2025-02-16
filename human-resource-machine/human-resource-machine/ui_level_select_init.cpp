/*
完成了ui_level_select_init函数，该函数用于初始化选关界面。

该函数创建了3个按钮，分别对应3个级别，并设置了不同的颜色和文本。
*/
#include "humanresourcemachine.h"

void humanresourcemachine::ui_level_select_init()
{
    // 排版：图片在页面的上方，按钮在页面下方排布
    ui_level_select = new QVBoxLayout;

    //定义背景图片地址
    QString background_image_path = "../../img/level_select_background.png";
    // 创建并设置背景图片
    QPixmap background_image = QPixmap(background_image_path);
    QLabel* background_label = new QLabel;
    background_label->setPixmap(background_image);
    background_label->setScaledContents(true); // 图片自适应大小
    background_label->setAlignment(Qt::AlignCenter); // 使图片居中
    // 将背景图片添加到ui_level_select布局中
    ui_level_select->addWidget(background_label, 0, Qt::AlignCenter);

    //创建背景和按钮的父容器
    QWidget* containerWidget = new QWidget;
    containerWidget->setLayout(ui_level_select);



    // 水平布局用于放置各个级别按钮和返回按钮
    QHBoxLayout* buttonLayout = new QHBoxLayout;

    // 定义按钮的颜色和文本
    string levelText[kMAX_NUMBER_OF_LEVEL];
    for (int i = 0; i < kMAX_NUMBER_OF_LEVEL; i++) {
        levelText[i] = "Level " + to_string(i + 1);
    }
    const QString buttonStyles[] = {
        //留下三种颜色即可：绿色表示已解锁已经通关，蓝色表示正在的关卡，灰色表示未解锁，红色为回退的按钮
        "background-color: #4CAF50; color: white;",//绿色
        "background-color: #2196F3; color: white;",//蓝色
        "background-color: #9E9E9E; color: white;",//灰色
        "background-color: #F44336; color: white;" //红色
    };

    // 获取最大级别数目（硬编码为3）
    const int levelCount = sizeof(levelText) / sizeof(levelText[0]);

    // 退出按钮
    QPushButton* btn_exit_in_game = new QPushButton("Back");
    btn_exit_in_game->setFixedSize(150, 50);
    btn_exit_in_game->setStyleSheet(buttonStyles[3]);

    // 连接退出按钮的信号槽
    connect(btn_exit_in_game, &QPushButton::clicked, this, &humanresourcemachine::exit_level);

    // 将退出按钮添加到水平布局
    buttonLayout->addWidget(btn_exit_in_game);


    // 创建和配置关卡选择按钮
    for (int i = 0; i < levelCount; ++i) {
        btn_levels[i] = new QPushButton(QString::fromStdString(levelText[i]));
        btn_levels[i]->setFixedSize(150, 50);
        //利用progress对未解锁关卡进行标记和禁用
        if (i + 1 == player_progress->currentLevel && player_progress->isCompleted == false) { // 当前且未通过的关卡设为蓝色
            //设置为蓝色
            btn_levels[i]->setStyleSheet(buttonStyles[1]);
        }
        else if (i + 1 > player_progress->currentLevel) {
            btn_levels[i]->setEnabled(false);  // 关卡未解锁，禁用按钮
            //设置为灰色
            btn_levels[i]->setStyleSheet(buttonStyles[2]);
        }
        else {
            // 设置按钮的颜色为绿色
            btn_levels[i]->setStyleSheet(buttonStyles[0]);
        }
        // 连接信号槽，使用通用的方式简化代码
        connect(btn_levels[i], &QPushButton::clicked, this, [this, i]() {
            enter_level(i + 1); // i从0开始，传递对应的级别
            });
        // 将按钮添加到布局中
        buttonLayout->addWidget(btn_levels[i]);
    }

    QWidget* buttonWidget = new QWidget;
    buttonWidget->setLayout(buttonLayout);
    buttonWidget->setStyleSheet("background: transparent;"); // 设置背景透明
    buttonWidget->setGeometry(0, this->height() - 100, this->width(), 100); // 设置按钮容器的位置

    ui_level_select->addWidget(buttonWidget);

    setLayout(ui_level_select);
}

void humanresourcemachine::enter_level(int level_index)
{

    //这里弹出关卡提示卡，提示本关卡要达到的输出目标
    show_level_tip(level_index);
    // 假设level_index从1开始，所以加1调整堆栈位置
    stackedWidget->setCurrentIndex(1 + level_index);
}

void humanresourcemachine::exit_level() {
    // 退出时返回到首页（index为0）
    stackedWidget->setCurrentIndex(0);
}
