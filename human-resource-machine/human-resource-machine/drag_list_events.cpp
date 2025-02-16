#pragma once
#include "humanresourcemachine.h"

QDragListWidget::QDragListWidget(int level_spare_number)
{
	level_spare_num = level_spare_number;
	setAcceptDrops(true);
	setDragEnabled(true);
	setSelectionMode(QAbstractItemView::SingleSelection);
	setDragDropMode(QAbstractItemView::InternalMove);
	setDropIndicatorShown(true);
	friends.clear();

	connect(this, &QListWidget::itemClicked, this, &QDragListWidget::onItemClicked);
}

void QDragListWidget::dragEnterEvent(QDragEnterEvent* event)
{
	event->acceptProposedAction();
}

void QDragListWidget::dragMoveEvent(QDragMoveEvent* event)
{
	event->acceptProposedAction();
}

void QDragListWidget::dropEvent(QDropEvent* event)
{
	const QMimeData* mimeData = event->mimeData();
	if (mimeData->hasText()) {
		string mime_data_text = mimeData->text().toStdString();
		if (mime_data_text.substr(0, 11) != "_drag_list_") {//如果不是内部移动，要去掉_outside_关键字
			string mime_data = mimeData->text().toStdString();
			mime_data = mime_data.substr(9, mime_data.length());
			if (mime_data == "add" || mime_data == "sub" || mime_data == "copyto" || mime_data == "copyfrom") {//添加空地指令数
				QDialogSpare* dlg_spare = new QDialogSpare(level_spare_num);
				if (dlg_spare->exec() == QDialog::Accepted) {
					int spare_no = dlg_spare->get_spare_no();
					mime_data += " " + to_string(spare_no);
				}
			}
			QListWidgetItem* item = new QListWidgetItem(mime_data.c_str());
			addItem(item);
			if (mime_data == "jump" || mime_data == "jumpifzero") {//添加空白条和连接符号
				QListWidgetItem* jump_item = new QListWidgetItem();
				addItem(jump_item);
				friends.push_back(make_pair(item, jump_item));
			}

			QListWidgetItem* sourceItem;
			if (mime_data == "jump" || mime_data == "jumpifzero") {
				sourceItem = this->item(count() - 2);
			}
			else {
				sourceItem = this->item(count() - 1);
			}
			QPoint pos = event->position().toPoint();
			QListWidgetItem* targetItem = itemAt(pos);
			int sourceRow = row(sourceItem);
			int targetRow;
			if (targetItem == nullptr)
				targetRow = count() - 1;
			else
				targetRow = row(targetItem);
			QListWidgetItem* movedItem = takeItem(sourceRow);
			insertItem(targetRow, movedItem);
			setCurrentItem(movedItem);
			/*QMessageBox::information(this, tr("Congrats!"), tr(to_string(this->count()).c_str()));
			for(int i=0;i<this->count();i++)
				QMessageBox::information(this, tr("Congrats!"), tr(this->item(i)->text().toStdString().c_str()));*/
			event->acceptProposedAction();
		}
		else {//两端代码部分重复，后面可以考虑删一段
			QListWidgetItem* sourceItem = currentItem();
			QPoint pos = event->position().toPoint();
			QListWidgetItem* targetItem = itemAt(pos);
			if (targetItem == sourceItem) {
				event->ignore();
				return;
			}
			int sourceRow = row(sourceItem);
			int targetRow;
			if (targetItem == nullptr)
				targetRow = count() - 1;
			else
				targetRow = row(targetItem);
			QListWidgetItem* it_friend_first = NULL, * it_friend_second = NULL;
			for (vector<pair<QListWidgetItem*, QListWidgetItem*> >::iterator it = friends.begin(); it != friends.end(); it++) {
				if (it->first == sourceItem) {
					it_friend_second = it->second;
					friends.erase(it);
					break;
				}
				if (it->second == sourceItem) {
					it_friend_first = it->first;
					friends.erase(it);
					break;
				}
			}
			QListWidgetItem* movedItem = takeItem(sourceRow);
			insertItem(targetRow, movedItem);
			setCurrentItem(movedItem);
			if (it_friend_first != NULL) {
				friends.push_back(make_pair(it_friend_first, movedItem));
			}
			else if (it_friend_second != NULL) {
				friends.push_back(make_pair(movedItem, it_friend_second));
			}
			event->acceptProposedAction();
		}
	}
}

void QDragListWidget::mouseMoveEvent(QMouseEvent* event) {
	if (event->buttons() & Qt::LeftButton) {
		QDrag* drag = new QDrag(this);
		QMimeData* mimeData = new QMimeData;
		string mime_data_input = "_drag_list_" + this->currentItem()->text().toStdString();
		mimeData->setText(mime_data_input.c_str());
		drag->setMimeData(mimeData);

		//画光标
		QPixmap pixmap(size());
		pixmap.fill(Qt::transparent);
		QPainter painter(&pixmap);
		painter.setPen(Qt::black);
		painter.drawText(0, 0, width(), height(), Qt::AlignCenter, this->currentItem()->text());
		painter.end();
		drag->setPixmap(pixmap);
		drag->setHotSpot(QPoint(pixmap.width() / 2, pixmap.height() / 2));

		drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);
	}
}

void QDragListWidget::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Delete) { // 检测 Delete 键
		QListWidgetItem* currentItem = this->currentItem();
		if (currentItem) {
			for (vector<pair<QListWidgetItem*, QListWidgetItem*> >::iterator it = friends.begin(); it != friends.end(); it++) {
				if (it->first == currentItem) {
					delete it->second;
					friends.erase(it);
					break;
				}
				if (it->second == currentItem) {
					delete it->first;
					friends.erase(it);
					break;
				}
			}
			delete currentItem; // 删除选中的项目
			setCurrentItem(NULL);
		}
	}
	else {
		QListWidget::keyPressEvent(event); // 调用基类处理其他按键
	}
}

void QDragListWidget::dragLeaveEvent(QDragLeaveEvent* event)
{
	QListWidgetItem* currentItem = this->currentItem();
	if (currentItem) {
		for (vector<pair<QListWidgetItem*, QListWidgetItem*> >::iterator it = friends.begin(); it != friends.end(); it++) {
			if (it->first == currentItem) {
				delete it->second;
				friends.erase(it);
				break;
			}
			if (it->second == currentItem) {
				delete it->first;
				friends.erase(it);
				break;
			}
		}
		delete currentItem; // 删除选中的项目
		setCurrentItem(NULL);
	}
	event->accept();
}

void QDragListWidget::paintEvent(QPaintEvent* event)
{
	QListWidget::paintEvent(event); // 先绘制正常的项

	QPainter painter(viewport());
	painter.setPen(QPen(Qt::black, 1));
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setBrush(QBrush(Qt::black));  // 设置填充颜色为黑色

	// 获取所有的项，并计算连线
	for (vector<pair<QListWidgetItem*, QListWidgetItem*> >::iterator it = friends.begin(); it != friends.end(); it++) {
		QListWidgetItem* item1 = it->first;
		QListWidgetItem* item2 = it->second;

		// 画圆弧
		QRect rect1 = visualItemRect(item1);
		QPoint p1 = QPoint((rect1.topLeft().x() + rect1.bottomRight().x()) / 2, (rect1.topRight().y() + rect1.bottomRight().y()) / 2);
		QRect rect2 = visualItemRect(item2);
		QPoint p2 = QPoint((rect2.topLeft().x() + rect2.bottomRight().x()) / 2, (rect2.topRight().y() + rect2.bottomRight().y()) / 2);
		QPoint circle_center = QPoint((p1.x() + p2.x()) / 2, (p1.y() + p2.y()) / 2);
		int circle_radius = (p1.y() - p2.y()) / 2;
		int start_angle = 270 * 16, span_angle = 180 * 16;
		QRect rect(circle_center.x() - circle_radius, circle_center.y() - circle_radius, 2 * circle_radius, 2 * circle_radius);
		painter.drawArc(rect, start_angle, span_angle);
		
		// 画箭头
		double arrowAngleRad = 0; // 箭头的方向与圆弧的终点角度一致
		QPoint p3 = QPoint(p2.x() - 10, p2.y()); // 箭头末端的坐标
		QPoint arrowPoint1(p3.x() + 10 * cos(arrowAngleRad - M_PI / 6), p3.y() - 10 * sin(arrowAngleRad - M_PI / 6));
		QPoint arrowPoint2(p3.x() + 10 * cos(arrowAngleRad + M_PI / 6), p3.y() - 10 * sin(arrowAngleRad + M_PI / 6));

		// 绘制箭头
		painter.drawLine(QPoint(p2.x(), p2.y()), QPoint(p3.x(), p3.y()));  // 绘制箭头线

		// 绘制箭头的两侧（三角形部分）
		painter.drawPolygon(QPolygon() << QPoint(p3.x(), p3.y()) << arrowPoint1 << arrowPoint2);
	}
}

vector<pair<QListWidgetItem*, QListWidgetItem*>> QDragListWidget::get_friends()
{
	return friends;
}

void QDragListWidget::onLabelDragged()
{
	setCurrentItem(NULL);
}

void QDragListWidget::on_btn_restart_clicked()
{
	friends.clear();
	clear();
}

void QDragListWidget::onItemClicked(QListWidgetItem* item) {
	if (!item)
		return;
	if (!(item->text().toStdString().substr(0, 3) == "add" || item->text().toStdString().substr(0, 3) == "sub" || item->text().toStdString().substr(0, 6) == "copyto" || item->text().toStdString().substr(0, 8) == "copyfrom"))
		return;
	QDialogSpare* dlg_spare = new QDialogSpare(level_spare_num);
	if (dlg_spare->exec() == QDialog::Accepted) {
		int spare_no = dlg_spare->get_spare_no();
		string item_instr = item->text().toStdString();
		size_t pos = item_instr.find(' ');
		if (pos == string::npos) {
			return;
		}
		item_instr = item_instr.substr(0, pos) + ' ' + to_string(spare_no);
		item->setText(item_instr.c_str());
	}
}