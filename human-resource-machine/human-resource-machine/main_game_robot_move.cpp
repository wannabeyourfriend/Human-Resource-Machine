#pragma once
#include "humanresourcemachine.h"

void QMainGame::on_fail_exe()
{
    //机器人做出fail动作；在fail之后，从robot_system中会阻挡剩下动作的emit；robot_system本身也会不再运行，所以不会有emit
}
void QMainGame::on_inbox_exe(int op)
{
    qDebug() << "INBOX";
    qDebug() << "inbox:";
    for (int i = 0; i < lb_inboxes.size(); i++)
        qDebug() << lb_inboxes[i]->text();
    qDebug() << "spare:";
    for (int i = 0; i < level_info.spare_number; i++)
        qDebug() << lb_spare_boxes[i]->text();

    vector<QLabel*>::iterator it = lb_inboxes.begin();
    standardize_blocks(*it);
    //机器人左转取件放到自己头上，走到中间
    update_robot_pos(get_inbox_pos(0));

    QCoreApplication::processEvents();
    lb_robox->setText((*it)->text());
    //若手中是不空的，就标准化
    if (lb_robox->text() != "")
        standardize_blocks(lb_robox);
    lt_inbox->removeWidget(*it);
    delete (*it);

    lb_inboxes.erase(it);
    //lt_inbox->update();
    //lb_robox->update();
    //lt_game->update();
    QThread::msleep(sleep_time);
}
void QMainGame::on_outbox_exe(int op)
{
    qDebug() << "OUTBOX";


    QLabel* tmp = new QLabel(lb_robox->text());
    standardize_blocks(tmp);

    lb_outboxes.insert(lb_outboxes.begin(), tmp);
    lb_robox->setText("");
    lb_robox->setStyleSheet("");
    lt_outbox->insertWidget(0, tmp);
    //机器人右转放到输出
    update_robot_pos(get_outbox_pos(0));

    /*lt_inbox->update();
    lb_robox->update();
    lt_game->update();*/
    QThread::msleep(sleep_time);
}
void QMainGame::on_add_exe(int op)
{
    qDebug() << "ADD";
    //机器人走到空格并加
    update_robot_pos(get_spare_pos(1));

    qDebug() << "robox:";
    qDebug() << lb_robox->text();
    qDebug() << "spare:";
    for (int i = 0; i < level_info.spare_number; i++)
        qDebug() << lb_spare_boxes[i]->text();
    int robox_num = stoi(lb_robox->text().toStdString());
    int spare_num = stoi(lb_spare_boxes[op]->text().toStdString());


    robox_num += spare_num;
    lb_robox->setText(to_string(robox_num).c_str());
    standardize_blocks(lb_robox);
    QThread::msleep(sleep_time);
}
void QMainGame::on_sub_exe(int op)
{
    qDebug() << "SUB";
    //机器人走到空格并减
    update_robot_pos(get_spare_pos(op));
    qDebug() << "robox:";
    qDebug() << lb_robox->text();
    qDebug() << "spare:";
    for (int i = 0; i < level_info.spare_number; i++)
        qDebug() << lb_spare_boxes[i]->text();
    int robox_num = stoi(lb_robox->text().toStdString());
    int spare_num = stoi(lb_spare_boxes[op]->text().toStdString());
    robox_num -= spare_num;
    lb_robox->setText(to_string(robox_num).c_str());
    standardize_blocks(lb_robox);
    QThread::msleep(sleep_time);
}
void QMainGame::on_copyto_exe(int op)
{
    qDebug() << "COPYTO";
    //机器人走到空格并复制到空格
    update_robot_pos(get_spare_pos(op));
    qDebug() << "robox:";
    qDebug() << lb_robox->text();
    qDebug() << "spare:";
    for (int i = 0; i < level_info.spare_number; i++)
        qDebug() << lb_spare_boxes[i]->text();

    lb_spare_boxes[op]->setText(lb_robox->text());
    standardize_blocks(lb_spare_boxes[op]);
    QThread::msleep(sleep_time);
}
void QMainGame::on_copyfrom_exe(int op)
{
    qDebug() << "COPYFROM";
    //机器人走到空格并取件
    update_robot_pos(get_spare_pos(op));

    qDebug() << "robox:";
    qDebug() << lb_robox->text();
    qDebug() << "spare:";
    for (int i = 0; i < level_info.spare_number; i++)
        qDebug() << lb_spare_boxes[i]->text();
    lb_robox->setText(lb_spare_boxes[op]->text());
    standardize_blocks(lb_robox);
    QThread::msleep(sleep_time);
}

void QMainGame::standardize_blocks(QLabel* tmp)
{
    tmp->setAlignment(Qt::AlignCenter);
    QString backgroundColor = "lightblue";
    QString style = "QLabel {"
        "background-color: " + backgroundColor + ";"
        "border: 2px solid black;"
        "border-radius: 5px;"
        "padding: 5px; }";
    tmp->setStyleSheet(style);
    int labelSize = 30;
    tmp->setFixedSize(labelSize, labelSize);
    return;
}

void QMainGame::standardize_code_blocks(QDragLabel* lb_code_block)
{
    int width = 150;
    int height = 40;
    lb_code_block->setFixedSize(width, height);
    lb_code_block->setAlignment(Qt::AlignCenter);

    QString labelStyle = "QLabel {"
        "background-color: #f0f0f0;"
        "border: 2px solid #0078d7;"
        "border-radius: 5px;"
        "padding: 10px;"
        "font-size: 14px;"
        "font-weight: bold;"
        "color: #333333;"
        "}";

    lb_code_block->setStyleSheet(labelStyle);
    lb_code_block->setAlignment(Qt::AlignCenter);
    return;
}

void QMainGame::update_robot_pos(QPoint qPoint) {
    QPoint delta = QPoint(30, 0);
    wdg_robot_pic->move(mapFromGlobal(qPoint));
}

QPoint QMainGame::get_inbox_pos(int index) {
    QPoint widgetGlobalPos = lb_inboxes[index]->mapToGlobal(QPoint(0, 0));
    return widgetGlobalPos;
}
QPoint QMainGame::get_outbox_pos(int index) {
    QPoint widgetGlobalPos = lb_outboxes[index]->mapToGlobal(QPoint(0, 0));
    return widgetGlobalPos;
}
QPoint QMainGame::get_spare_pos(int index) {
    QPoint widgetGlobalPos = lb_spare_boxes[index]->mapToGlobal(QPoint(0, 0));
    return widgetGlobalPos;
}
QPoint QMainGame::get_robot_pos() {
    QPoint widgetGlobalPos = lb_robox->mapToGlobal(QPoint(0, 0));
    return widgetGlobalPos;
}
QPoint QMainGame::get_robot_pic_pos() {
    QPoint widgetGlobalPos = wdg_robot_pic->mapToGlobal(QPoint(0, 0));
    return widgetGlobalPos;
}