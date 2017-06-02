/********************************************************************************
** Form generated from reading UI file 'ResultNotification.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESULTNOTIFICATION_H
#define UI_RESULTNOTIFICATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_ResultNotification
{
public:

    void setupUi(QDialog *ResultNotification)
    {
        if (ResultNotification->objectName().isEmpty())
            ResultNotification->setObjectName(QStringLiteral("ResultNotification"));
        ResultNotification->resize(400, 300);

        retranslateUi(ResultNotification);

        QMetaObject::connectSlotsByName(ResultNotification);
    } // setupUi

    void retranslateUi(QDialog *ResultNotification)
    {
        ResultNotification->setWindowTitle(QApplication::translate("ResultNotification", "ResultNotification", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ResultNotification: public Ui_ResultNotification {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESULTNOTIFICATION_H
