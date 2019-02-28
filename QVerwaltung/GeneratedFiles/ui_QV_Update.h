/********************************************************************************
** Form generated from reading UI file 'QV_Update.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QV_UPDATE_H
#define UI_QV_UPDATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QV_Update
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *tb_current;
    QLineEdit *tb_recent;
    QTextEdit *tb_changelog;
    QPushButton *btn_close;
    QPushButton *btn_update;

    void setupUi(QWidget *QV_Update)
    {
        if (QV_Update->objectName().isEmpty())
            QV_Update->setObjectName(QString::fromUtf8("QV_Update"));
        QV_Update->resize(734, 593);
        label = new QLabel(QV_Update);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 30, 47, 13));
        label_2 = new QLabel(QV_Update);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(50, 60, 101, 16));
        tb_current = new QLineEdit(QV_Update);
        tb_current->setObjectName(QString::fromUtf8("tb_current"));
        tb_current->setEnabled(false);
        tb_current->setGeometry(QRect(180, 30, 113, 20));
        tb_recent = new QLineEdit(QV_Update);
        tb_recent->setObjectName(QString::fromUtf8("tb_recent"));
        tb_recent->setEnabled(false);
        tb_recent->setGeometry(QRect(180, 60, 113, 20));
        tb_changelog = new QTextEdit(QV_Update);
        tb_changelog->setObjectName(QString::fromUtf8("tb_changelog"));
        tb_changelog->setGeometry(QRect(40, 110, 651, 381));
        tb_changelog->setReadOnly(true);
        btn_close = new QPushButton(QV_Update);
        btn_close->setObjectName(QString::fromUtf8("btn_close"));
        btn_close->setGeometry(QRect(150, 530, 75, 23));
        btn_update = new QPushButton(QV_Update);
        btn_update->setObjectName(QString::fromUtf8("btn_update"));
        btn_update->setEnabled(false);
        btn_update->setGeometry(QRect(360, 530, 75, 23));

        retranslateUi(QV_Update);

        QMetaObject::connectSlotsByName(QV_Update);
    } // setupUi

    void retranslateUi(QWidget *QV_Update)
    {
        QV_Update->setWindowTitle(QApplication::translate("QV_Update", "Auf Updates pr\303\274fen", nullptr));
        label->setText(QApplication::translate("QV_Update", "Version:", nullptr));
        label_2->setText(QApplication::translate("QV_Update", "Verf\303\274gbare Version:", nullptr));
        tb_current->setText(QApplication::translate("QV_Update", "02/27/2019", nullptr));
        btn_close->setText(QApplication::translate("QV_Update", "Schlie\303\237en", nullptr));
        btn_update->setText(QApplication::translate("QV_Update", "Aktualisieren", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QV_Update: public Ui_QV_Update {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QV_UPDATE_H
