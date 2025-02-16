#pragma once
#include "humanresourcemachine.h"
BackgroundWidget::BackgroundWidget(string img_path, QWidget* parent) : QWidget(parent) {
    setBackgroundImage(img_path.c_str());
}
void BackgroundWidget::setBackgroundImage(const QString& imagePath) {
    backgroundImage = QPixmap(imagePath);
}
void BackgroundWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    QSize scaledSize = backgroundImage.size();
    scaledSize.scale(size(), Qt::KeepAspectRatio);
    QPoint topLeft((width() - scaledSize.width()) / 2, (height() - scaledSize.height()) / 2);
    painter.drawPixmap(topLeft, backgroundImage.scaled(scaledSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}