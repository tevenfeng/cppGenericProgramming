/********************************************************************************
** Form generated from reading UI file 'gonet.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GONET_H
#define UI_GONET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gonetClass
{
public:
    QWidget *centralWidget;

    void setupUi(QMainWindow *gonetClass)
    {
        if (gonetClass->objectName().isEmpty())
            gonetClass->setObjectName(QStringLiteral("gonetClass"));
        gonetClass->resize(600, 480);
        centralWidget = new QWidget(gonetClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gonetClass->setCentralWidget(centralWidget);

        retranslateUi(gonetClass);

        QMetaObject::connectSlotsByName(gonetClass);
    } // setupUi

    void retranslateUi(QMainWindow *gonetClass)
    {
        gonetClass->setWindowTitle(QApplication::translate("gonetClass", "\345\274\200\345\247\213\346\270\270\346\210\217", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class gonetClass: public Ui_gonetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GONET_H
