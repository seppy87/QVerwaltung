/********************************************************************************
** Form generated from reading UI file 'QVerwaltung.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QVERWALTUNG_H
#define UI_QVERWALTUNG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QVerwaltungClass
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QComboBox *cb_choose;
    QLineEdit *tb_search;
    QTableWidget *tbl_overview;
    QPushButton *btn_search;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QVerwaltungClass)
    {
        if (QVerwaltungClass->objectName().isEmpty())
            QVerwaltungClass->setObjectName(QString::fromUtf8("QVerwaltungClass"));
        QVerwaltungClass->resize(945, 856);
        centralWidget = new QWidget(QVerwaltungClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 941, 111));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());
        cb_choose = new QComboBox(centralWidget);
        cb_choose->addItem(QString());
        cb_choose->addItem(QString());
        cb_choose->setObjectName(QString::fromUtf8("cb_choose"));
        cb_choose->setGeometry(QRect(20, 120, 291, 22));
        tb_search = new QLineEdit(centralWidget);
        tb_search->setObjectName(QString::fromUtf8("tb_search"));
        tb_search->setGeometry(QRect(350, 120, 411, 20));
        tbl_overview = new QTableWidget(centralWidget);
        tbl_overview->setObjectName(QString::fromUtf8("tbl_overview"));
        tbl_overview->setGeometry(QRect(20, 160, 831, 481));
        btn_search = new QPushButton(centralWidget);
        btn_search->setObjectName(QString::fromUtf8("btn_search"));
        btn_search->setGeometry(QRect(770, 120, 75, 23));
        QVerwaltungClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QVerwaltungClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 945, 21));
        QVerwaltungClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QVerwaltungClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QVerwaltungClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QVerwaltungClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QVerwaltungClass->setStatusBar(statusBar);

        retranslateUi(QVerwaltungClass);

        QMetaObject::connectSlotsByName(QVerwaltungClass);
    } // setupUi

    void retranslateUi(QMainWindow *QVerwaltungClass)
    {
        QVerwaltungClass->setWindowTitle(QApplication::translate("QVerwaltungClass", "QVerwaltung", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("QVerwaltungClass", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("QVerwaltungClass", "Tab 2", nullptr));
        cb_choose->setItemText(0, QApplication::translate("QVerwaltungClass", "Objekte", nullptr));
        cb_choose->setItemText(1, QApplication::translate("QVerwaltungClass", "Mieter", nullptr));

        btn_search->setText(QApplication::translate("QVerwaltungClass", ">>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QVerwaltungClass: public Ui_QVerwaltungClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QVERWALTUNG_H
