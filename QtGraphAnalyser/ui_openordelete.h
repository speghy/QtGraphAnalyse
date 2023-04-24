/********************************************************************************
** Form generated from reading UI file 'openordelete.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPENORDELETE_H
#define UI_OPENORDELETE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_OpenOrDelete
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;

    void setupUi(QDialog *OpenOrDelete)
    {
        if (OpenOrDelete->objectName().isEmpty())
            OpenOrDelete->setObjectName(QStringLiteral("OpenOrDelete"));
        OpenOrDelete->resize(400, 131);
        pushButton = new QPushButton(OpenOrDelete);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(30, 70, 161, 41));
        pushButton_2 = new QPushButton(OpenOrDelete);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(200, 70, 161, 41));
        label = new QLabel(OpenOrDelete);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 30, 271, 31));
        QFont font;
        font.setPointSize(16);
        label->setFont(font);

        retranslateUi(OpenOrDelete);

        QMetaObject::connectSlotsByName(OpenOrDelete);
    } // setupUi

    void retranslateUi(QDialog *OpenOrDelete)
    {
        OpenOrDelete->setWindowTitle(QApplication::translate("OpenOrDelete", "Dialog", 0));
        pushButton->setText(QApplication::translate("OpenOrDelete", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", 0));
        pushButton_2->setText(QApplication::translate("OpenOrDelete", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", 0));
        label->setText(QApplication::translate("OpenOrDelete", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \321\204\320\260\320\271\320\273 \320\270\320\273\320\270 \321\203\320\264\320\260\320\273\320\270\321\202\321\214?", 0));
    } // retranslateUi

};

namespace Ui {
    class OpenOrDelete: public Ui_OpenOrDelete {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPENORDELETE_H
