#pragma once
#include "humanresourcemachine.h"

void QMainGame::paintEvent(QPaintEvent* event)
{
	QWidget::paintEvent(event);
	paint_cursor(cur_line);
}

void QMainGame::paint_cursor(int curr_line) {
	if (curr_line != -1) {
		int cur_line = curr_line - 1;
		qDebug() << cur_line;
		QListWidgetItem* cur_item = lst_code->item(cur_line);
		QRect cur_rect = lst_code->visualItemRect(cur_item); // 运行到这一行
		QPoint p1 = lst_code->mapTo(this, QPoint(cur_rect.topLeft().x(), (cur_rect.topLeft().y() + cur_rect.bottomLeft().y()) / 2));
		QPoint arrowPoint1(p1.x() + 10 * cos(5 * M_PI / 6), p1.y() - 10 * sin(5 * M_PI / 6));
		QPoint arrowPoint2(p1.x() + 10 * cos(7 * M_PI / 6), p1.y() - 10 * sin(7 * M_PI / 6));
		QPainter painter(this);
		painter.setPen(QPen(Qt::green, 1));
		painter.setRenderHint(QPainter::Antialiasing);
		painter.setBrush(QBrush(Qt::green));  // 设置填充颜色为绿色
		painter.drawPolygon(QPolygon() << QPoint(p1.x(), p1.y()) << arrowPoint1 << arrowPoint2);
	}
}