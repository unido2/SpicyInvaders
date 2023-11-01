/********************************************************************************
** Form generated from reading UI file 'SpicyInvaders.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPICYINVADERS_H
#define UI_SPICYINVADERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SpicyInvadersClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SpicyInvadersClass)
    {
        if (SpicyInvadersClass->objectName().isEmpty())
            SpicyInvadersClass->setObjectName(QString::fromUtf8("SpicyInvadersClass"));
        SpicyInvadersClass->resize(600, 400);
        menuBar = new QMenuBar(SpicyInvadersClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        SpicyInvadersClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SpicyInvadersClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        SpicyInvadersClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(SpicyInvadersClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        SpicyInvadersClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(SpicyInvadersClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        SpicyInvadersClass->setStatusBar(statusBar);

        retranslateUi(SpicyInvadersClass);

        QMetaObject::connectSlotsByName(SpicyInvadersClass);
    } // setupUi

    void retranslateUi(QMainWindow *SpicyInvadersClass)
    {
        SpicyInvadersClass->setWindowTitle(QCoreApplication::translate("SpicyInvadersClass", "SpicyInvaders", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SpicyInvadersClass: public Ui_SpicyInvadersClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPICYINVADERS_H
