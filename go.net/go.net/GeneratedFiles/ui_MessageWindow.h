/********************************************************************************
** Form generated from reading UI file 'MessageWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESSAGEWINDOW_H
#define UI_MESSAGEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_MessageWindow
{
public:

    void setupUi(QDialog *MessageWindow)
    {
        if (MessageWindow->objectName().isEmpty())
            MessageWindow->setObjectName(QStringLiteral("MessageWindow"));
        MessageWindow->resize(400, 300);

        retranslateUi(MessageWindow);

        QMetaObject::connectSlotsByName(MessageWindow);
    } // setupUi

    void retranslateUi(QDialog *MessageWindow)
    {
        MessageWindow->setWindowTitle(QApplication::translate("MessageWindow", "MessageWindow", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MessageWindow: public Ui_MessageWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSAGEWINDOW_H
