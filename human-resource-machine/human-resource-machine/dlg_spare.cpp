#pragma once
#include "humanresourcemachine.h"

QDialogSpare::QDialogSpare(int spares_number)
{
	setWindowTitle("Select a Spare");
	setModal(true);
	setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);
	spare_no = 1;
	this->spares_number = spares_number;
	lt_dlg_spare = new QVBoxLayout();
	btn_spares = new QPushButton * [spares_number];
	for (int i = 0; i < spares_number; i++) {
		btn_spares[i] = new QPushButton(("Spare " + to_string(i)).c_str());
		lt_dlg_spare->addWidget(btn_spares[i]);
		connect(btn_spares[i], &QPushButton::clicked, this, &QDialogSpare::onButtonClicked);
	}
	setLayout(lt_dlg_spare);
}

int QDialogSpare::get_spare_no()
{
	return spare_no;
}

void QDialogSpare::onButtonClicked() {
	for (int i = 0; i < spares_number; i++) {
		if (sender() == btn_spares[i]) {
			spare_no = i;
			accept();
			return;
		}
	}
	spare_no = 1;
	accept();
}

void QDialogSpare::closeEvent(QCloseEvent* event) {
	// 忽略关闭事件，防止通过 Alt + F4 关闭
	event->ignore();
}

void QDialogSpare::keyPressEvent(QKeyEvent* event) {
	// 如果按下 Alt + F4，不做任何处理
	if (event->key() == Qt::Key_F4 && event->modifiers() == Qt::AltModifier) {
		event->ignore();
	}
	else {
		QDialog::keyPressEvent(event);
	}
}