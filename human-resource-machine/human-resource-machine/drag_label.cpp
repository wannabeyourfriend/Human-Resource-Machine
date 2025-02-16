#pragma once
#include "humanresourcemachine.h"

QDragLabel::QDragLabel(QWidget* parent) :QLabel(parent) {
    setMouseTracking(true);
}
void QDragLabel::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        emit labelDragged();
        QDrag* drag = new QDrag(this);
        QMimeData* mimeData = new QMimeData;
        string to_be_sent = "_outside_" + text().toStdString();
        mimeData->setText(to_be_sent.c_str());
        drag->setMimeData(mimeData);

        //画光标
        QPixmap pixmap(size());
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        painter.setPen(Qt::black);
        painter.drawText(0, 0, width(), height(), Qt::AlignCenter, text());
        painter.end();
        drag->setPixmap(pixmap);
        drag->setHotSpot(QPoint(pixmap.width() / 2, pixmap.height() / 2));

        drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);
    }
}
void QDragLabel::mouseMoveEvent(QMouseEvent* event) {
    if (!(event->buttons() & Qt::LeftButton)) {
        return;// 如果没有按下左键，不进行拖动
    }
}