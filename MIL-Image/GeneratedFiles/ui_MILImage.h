/********************************************************************************
** Form generated from reading UI file 'MILImage.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MILIMAGE_H
#define UI_MILIMAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MILImageClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MILImageClass)
    {
        if (MILImageClass->objectName().isEmpty())
            MILImageClass->setObjectName(QStringLiteral("MILImageClass"));
        MILImageClass->resize(600, 400);
        menuBar = new QMenuBar(MILImageClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        MILImageClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MILImageClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MILImageClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(MILImageClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MILImageClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MILImageClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MILImageClass->setStatusBar(statusBar);

        retranslateUi(MILImageClass);

        QMetaObject::connectSlotsByName(MILImageClass);
    } // setupUi

    void retranslateUi(QMainWindow *MILImageClass)
    {
        MILImageClass->setWindowTitle(QApplication::translate("MILImageClass", "MILImage", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MILImageClass: public Ui_MILImageClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MILIMAGE_H
