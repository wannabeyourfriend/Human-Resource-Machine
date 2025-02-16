/********************************************************************************
** Form generated from reading UI file 'humanresourcemachine.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HUMANRESOURCEMACHINE_H
#define UI_HUMANRESOURCEMACHINE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_humanresourcemachineClass
{
public:
    QWidget *centralWidget;
    /*
    QMenuBar* menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    */

    void setupUi(QMainWindow *humanresourcemachineClass)
    {
        if (humanresourcemachineClass->objectName().isEmpty())
            humanresourcemachineClass->setObjectName("humanresourcemachineClass");
        humanresourcemachineClass->resize(600, 400);
        centralWidget = new QWidget(humanresourcemachineClass);
        centralWidget->setObjectName("centralWidget");
        humanresourcemachineClass->setCentralWidget(centralWidget);
        /*
        menuBar = new QMenuBar(humanresourcemachineClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        humanresourcemachineClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(humanresourcemachineClass);
        mainToolBar->setObjectName("mainToolBar");
        humanresourcemachineClass->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(humanresourcemachineClass);
        statusBar->setObjectName("statusBar");
        humanresourcemachineClass->setStatusBar(statusBar);
        */

        retranslateUi(humanresourcemachineClass);

        QMetaObject::connectSlotsByName(humanresourcemachineClass);
    } // setupUi

    void retranslateUi(QMainWindow *humanresourcemachineClass)
    {
        humanresourcemachineClass->setWindowTitle(QCoreApplication::translate("humanresourcemachineClass", "Human-Resource-Machine", nullptr));
    } // retranslateUi

};

namespace Ui {
    class humanresourcemachineClass: public Ui_humanresourcemachineClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HUMANRESOURCEMACHINE_H
