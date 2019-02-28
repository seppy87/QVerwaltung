/********************************************************************************
** Form generated from reading UI file 'QV_Users.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QV_USERS_H
#define UI_QV_USERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QV_Users
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QTableWidget *tbl_users;
    QWidget *tab_details;
    QLabel *label;
    QLabel *label_2;
    QCheckBox *cb_root;
    QLineEdit *tb_name;
    QLineEdit *tb_password;
    QPushButton *btn_abort;
    QPushButton *btn_Save;
    QPushButton *btn_add;

    void setupUi(QWidget *QV_Users)
    {
        if (QV_Users->objectName().isEmpty())
            QV_Users->setObjectName(QString::fromUtf8("QV_Users"));
        QV_Users->resize(976, 553);
        tabWidget = new QTabWidget(QV_Users);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 971, 471));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tbl_users = new QTableWidget(tab);
        if (tbl_users->columnCount() < 4)
            tbl_users->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tbl_users->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tbl_users->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tbl_users->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tbl_users->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tbl_users->setObjectName(QString::fromUtf8("tbl_users"));
        tbl_users->setGeometry(QRect(10, 10, 951, 421));
        tbl_users->setSelectionBehavior(QAbstractItemView::SelectRows);
        tabWidget->addTab(tab, QString());
        tab_details = new QWidget();
        tab_details->setObjectName(QString::fromUtf8("tab_details"));
        label = new QLabel(tab_details);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 30, 47, 13));
        label_2 = new QLabel(tab_details);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 60, 47, 13));
        cb_root = new QCheckBox(tab_details);
        cb_root->setObjectName(QString::fromUtf8("cb_root"));
        cb_root->setGeometry(QRect(40, 90, 91, 17));
        tb_name = new QLineEdit(tab_details);
        tb_name->setObjectName(QString::fromUtf8("tb_name"));
        tb_name->setGeometry(QRect(140, 30, 113, 20));
        tb_password = new QLineEdit(tab_details);
        tb_password->setObjectName(QString::fromUtf8("tb_password"));
        tb_password->setGeometry(QRect(140, 60, 113, 20));
        btn_abort = new QPushButton(tab_details);
        btn_abort->setObjectName(QString::fromUtf8("btn_abort"));
        btn_abort->setGeometry(QRect(120, 150, 75, 23));
        btn_Save = new QPushButton(tab_details);
        btn_Save->setObjectName(QString::fromUtf8("btn_Save"));
        btn_Save->setEnabled(false);
        btn_Save->setGeometry(QRect(250, 150, 75, 23));
        btn_add = new QPushButton(tab_details);
        btn_add->setObjectName(QString::fromUtf8("btn_add"));
        btn_add->setGeometry(QRect(390, 150, 75, 23));
        tabWidget->addTab(tab_details, QString());

        retranslateUi(QV_Users);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QV_Users);
    } // setupUi

    void retranslateUi(QWidget *QV_Users)
    {
        QV_Users->setWindowTitle(QApplication::translate("QV_Users", "Benutzereinstellungen", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tbl_users->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("QV_Users", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tbl_users->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("QV_Users", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tbl_users->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("QV_Users", "Passwort", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tbl_users->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("QV_Users", "Administrator", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("QV_Users", "\303\234bersicht", nullptr));
        label->setText(QApplication::translate("QV_Users", "Name:", nullptr));
        label_2->setText(QApplication::translate("QV_Users", "Passwort:", nullptr));
        cb_root->setText(QApplication::translate("QV_Users", "Administrator", nullptr));
        btn_abort->setText(QApplication::translate("QV_Users", "Zur\303\274cksetzen", nullptr));
        btn_Save->setText(QApplication::translate("QV_Users", "\303\234bernehmen", nullptr));
        btn_add->setText(QApplication::translate("QV_Users", "Hinzuf\303\274gen", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_details), QApplication::translate("QV_Users", "Details", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QV_Users: public Ui_QV_Users {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QV_USERS_H
