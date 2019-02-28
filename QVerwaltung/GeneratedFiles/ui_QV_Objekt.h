/********************************************************************************
** Form generated from reading UI file 'QV_Objekt.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QV_OBJEKT_H
#define UI_QV_OBJEKT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QV_Objekt
{
public:
    QTabWidget *tabWidget;
    QWidget *tab_object;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLineEdit *tb_object_id;
    QLineEdit *tb_object_name;
    QLineEdit *tb_object_street;
    QLineEdit *tb_object_zip;
    QLineEdit *tb_object_city;
    QLineEdit *tb_object_etage;
    QLineEdit *tb_object_year;
    QLineEdit *tb_object_size;
    QLineEdit *tb_object_zimmer;
    QWidget *tab_equipment;
    QTableWidget *tbl_equipment;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_21;
    QLabel *label_22;
    QLineEdit *tb_e_id;
    QLineEdit *tb_e_objectid;
    QLineEdit *tb_e_creation;
    QLineEdit *tb_e_fussboden;
    QLineEdit *tb_e_fusevalue;
    QLineEdit *tb_e_waschmaschine;
    QLineEdit *tb_e_bad;
    QLineEdit *tb_e_balkon;
    QLineEdit *tb_e_kabelanschluss;
    QLineEdit *tb_ftth;
    QLineEdit *tb_heizung;
    QTextEdit *tb_weiteres;
    QComboBox *cb_sicherung;
    QPushButton *btn_reset;
    QPushButton *btn_save;
    QPushButton *btn_add;
    QWidget *tab_tennant;
    QTableWidget *tbl_tennant;
    QLabel *label_23;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *label_26;
    QLabel *label_27;
    QLabel *label_28;
    QLabel *label_29;
    QLabel *label_30;
    QLineEdit *tb_t_id;
    QLineEdit *tb_ob_id;
    QLineEdit *tb_t_aid;
    QLineEdit *tb_t_vorname;
    QLineEdit *tb_t_nachname;
    QLineEdit *tb_t_geburtstag;
    QLineEdit *tb_t_einzug;
    QLineEdit *tb_t_auszug;
    QPushButton *btn_t_reset;
    QPushButton *btn_t_save;
    QPushButton *btn_t_add;
    QPushButton *btn_accept;
    QPushButton *btn_close;

    void setupUi(QWidget *QV_Objekt)
    {
        if (QV_Objekt->objectName().isEmpty())
            QV_Objekt->setObjectName(QString::fromUtf8("QV_Objekt"));
        QV_Objekt->resize(1038, 668);
        tabWidget = new QTabWidget(QV_Objekt);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 961, 591));
        tab_object = new QWidget();
        tab_object->setObjectName(QString::fromUtf8("tab_object"));
        label = new QLabel(tab_object);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 20, 51, 16));
        label_2 = new QLabel(tab_object);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(50, 60, 47, 13));
        label_3 = new QLabel(tab_object);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(50, 90, 47, 13));
        label_4 = new QLabel(tab_object);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(50, 130, 47, 13));
        label_5 = new QLabel(tab_object);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(250, 130, 47, 13));
        label_6 = new QLabel(tab_object);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(50, 160, 47, 13));
        label_7 = new QLabel(tab_object);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(50, 190, 47, 13));
        label_8 = new QLabel(tab_object);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(50, 230, 47, 13));
        label_9 = new QLabel(tab_object);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(300, 220, 47, 13));
        tb_object_id = new QLineEdit(tab_object);
        tb_object_id->setObjectName(QString::fromUtf8("tb_object_id"));
        tb_object_id->setEnabled(false);
        tb_object_id->setGeometry(QRect(120, 20, 113, 20));
        tb_object_name = new QLineEdit(tab_object);
        tb_object_name->setObjectName(QString::fromUtf8("tb_object_name"));
        tb_object_name->setGeometry(QRect(120, 60, 341, 20));
        tb_object_street = new QLineEdit(tab_object);
        tb_object_street->setObjectName(QString::fromUtf8("tb_object_street"));
        tb_object_street->setGeometry(QRect(120, 90, 341, 20));
        tb_object_zip = new QLineEdit(tab_object);
        tb_object_zip->setObjectName(QString::fromUtf8("tb_object_zip"));
        tb_object_zip->setGeometry(QRect(120, 120, 113, 20));
        tb_object_city = new QLineEdit(tab_object);
        tb_object_city->setObjectName(QString::fromUtf8("tb_object_city"));
        tb_object_city->setGeometry(QRect(280, 120, 181, 20));
        tb_object_etage = new QLineEdit(tab_object);
        tb_object_etage->setObjectName(QString::fromUtf8("tb_object_etage"));
        tb_object_etage->setGeometry(QRect(120, 160, 113, 20));
        tb_object_year = new QLineEdit(tab_object);
        tb_object_year->setObjectName(QString::fromUtf8("tb_object_year"));
        tb_object_year->setGeometry(QRect(120, 190, 113, 20));
        tb_object_size = new QLineEdit(tab_object);
        tb_object_size->setObjectName(QString::fromUtf8("tb_object_size"));
        tb_object_size->setGeometry(QRect(120, 220, 113, 20));
        tb_object_zimmer = new QLineEdit(tab_object);
        tb_object_zimmer->setObjectName(QString::fromUtf8("tb_object_zimmer"));
        tb_object_zimmer->setGeometry(QRect(350, 220, 113, 20));
        tabWidget->addTab(tab_object, QString());
        tab_equipment = new QWidget();
        tab_equipment->setObjectName(QString::fromUtf8("tab_equipment"));
        tbl_equipment = new QTableWidget(tab_equipment);
        if (tbl_equipment->columnCount() < 13)
            tbl_equipment->setColumnCount(13);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tbl_equipment->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tbl_equipment->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tbl_equipment->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tbl_equipment->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tbl_equipment->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tbl_equipment->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tbl_equipment->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tbl_equipment->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tbl_equipment->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tbl_equipment->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tbl_equipment->setHorizontalHeaderItem(10, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tbl_equipment->setHorizontalHeaderItem(11, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tbl_equipment->setHorizontalHeaderItem(12, __qtablewidgetitem12);
        tbl_equipment->setObjectName(QString::fromUtf8("tbl_equipment"));
        tbl_equipment->setGeometry(QRect(10, 10, 931, 192));
        label_10 = new QLabel(tab_equipment);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(50, 230, 47, 13));
        label_11 = new QLabel(tab_equipment);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(300, 230, 47, 13));
        label_12 = new QLabel(tab_equipment);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(50, 250, 91, 16));
        label_13 = new QLabel(tab_equipment);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(300, 250, 71, 16));
        label_14 = new QLabel(tab_equipment);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(50, 280, 61, 16));
        label_15 = new QLabel(tab_equipment);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(310, 280, 121, 16));
        label_16 = new QLabel(tab_equipment);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(50, 310, 81, 16));
        label_17 = new QLabel(tab_equipment);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(300, 310, 141, 16));
        label_18 = new QLabel(tab_equipment);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(60, 340, 47, 13));
        label_19 = new QLabel(tab_equipment);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(310, 340, 81, 16));
        label_20 = new QLabel(tab_equipment);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(60, 370, 47, 13));
        label_21 = new QLabel(tab_equipment);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(310, 370, 71, 16));
        label_22 = new QLabel(tab_equipment);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(50, 400, 47, 13));
        tb_e_id = new QLineEdit(tab_equipment);
        tb_e_id->setObjectName(QString::fromUtf8("tb_e_id"));
        tb_e_id->setEnabled(false);
        tb_e_id->setGeometry(QRect(140, 230, 113, 20));
        tb_e_objectid = new QLineEdit(tab_equipment);
        tb_e_objectid->setObjectName(QString::fromUtf8("tb_e_objectid"));
        tb_e_objectid->setEnabled(false);
        tb_e_objectid->setGeometry(QRect(390, 230, 113, 20));
        tb_e_creation = new QLineEdit(tab_equipment);
        tb_e_creation->setObjectName(QString::fromUtf8("tb_e_creation"));
        tb_e_creation->setGeometry(QRect(140, 250, 113, 20));
        tb_e_fussboden = new QLineEdit(tab_equipment);
        tb_e_fussboden->setObjectName(QString::fromUtf8("tb_e_fussboden"));
        tb_e_fussboden->setGeometry(QRect(390, 250, 171, 20));
        tb_e_fusevalue = new QLineEdit(tab_equipment);
        tb_e_fusevalue->setObjectName(QString::fromUtf8("tb_e_fusevalue"));
        tb_e_fusevalue->setGeometry(QRect(430, 280, 131, 20));
        tb_e_waschmaschine = new QLineEdit(tab_equipment);
        tb_e_waschmaschine->setObjectName(QString::fromUtf8("tb_e_waschmaschine"));
        tb_e_waschmaschine->setGeometry(QRect(440, 310, 121, 20));
        tb_e_bad = new QLineEdit(tab_equipment);
        tb_e_bad->setObjectName(QString::fromUtf8("tb_e_bad"));
        tb_e_bad->setGeometry(QRect(130, 310, 151, 20));
        tb_e_balkon = new QLineEdit(tab_equipment);
        tb_e_balkon->setObjectName(QString::fromUtf8("tb_e_balkon"));
        tb_e_balkon->setGeometry(QRect(130, 340, 151, 20));
        tb_e_kabelanschluss = new QLineEdit(tab_equipment);
        tb_e_kabelanschluss->setObjectName(QString::fromUtf8("tb_e_kabelanschluss"));
        tb_e_kabelanschluss->setGeometry(QRect(400, 340, 161, 20));
        tb_ftth = new QLineEdit(tab_equipment);
        tb_ftth->setObjectName(QString::fromUtf8("tb_ftth"));
        tb_ftth->setGeometry(QRect(130, 370, 151, 20));
        tb_heizung = new QLineEdit(tab_equipment);
        tb_heizung->setObjectName(QString::fromUtf8("tb_heizung"));
        tb_heizung->setGeometry(QRect(400, 370, 161, 20));
        tb_weiteres = new QTextEdit(tab_equipment);
        tb_weiteres->setObjectName(QString::fromUtf8("tb_weiteres"));
        tb_weiteres->setGeometry(QRect(130, 400, 431, 91));
        cb_sicherung = new QComboBox(tab_equipment);
        cb_sicherung->addItem(QString());
        cb_sicherung->addItem(QString());
        cb_sicherung->setObjectName(QString::fromUtf8("cb_sicherung"));
        cb_sicherung->setGeometry(QRect(130, 280, 151, 22));
        btn_reset = new QPushButton(tab_equipment);
        btn_reset->setObjectName(QString::fromUtf8("btn_reset"));
        btn_reset->setGeometry(QRect(100, 510, 75, 23));
        btn_save = new QPushButton(tab_equipment);
        btn_save->setObjectName(QString::fromUtf8("btn_save"));
        btn_save->setEnabled(false);
        btn_save->setGeometry(QRect(260, 510, 75, 23));
        btn_add = new QPushButton(tab_equipment);
        btn_add->setObjectName(QString::fromUtf8("btn_add"));
        btn_add->setGeometry(QRect(440, 510, 75, 23));
        tabWidget->addTab(tab_equipment, QString());
        tab_tennant = new QWidget();
        tab_tennant->setObjectName(QString::fromUtf8("tab_tennant"));
        tbl_tennant = new QTableWidget(tab_tennant);
        if (tbl_tennant->columnCount() < 8)
            tbl_tennant->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tbl_tennant->setHorizontalHeaderItem(0, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tbl_tennant->setHorizontalHeaderItem(1, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tbl_tennant->setHorizontalHeaderItem(2, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tbl_tennant->setHorizontalHeaderItem(3, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tbl_tennant->setHorizontalHeaderItem(4, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tbl_tennant->setHorizontalHeaderItem(5, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tbl_tennant->setHorizontalHeaderItem(6, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tbl_tennant->setHorizontalHeaderItem(7, __qtablewidgetitem20);
        tbl_tennant->setObjectName(QString::fromUtf8("tbl_tennant"));
        tbl_tennant->setGeometry(QRect(10, 10, 911, 192));
        label_23 = new QLabel(tab_tennant);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(40, 220, 47, 13));
        label_24 = new QLabel(tab_tennant);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(360, 220, 47, 13));
        label_25 = new QLabel(tab_tennant);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(630, 220, 47, 13));
        label_26 = new QLabel(tab_tennant);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(40, 250, 47, 13));
        label_27 = new QLabel(tab_tennant);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(360, 250, 47, 13));
        label_28 = new QLabel(tab_tennant);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setGeometry(QRect(630, 250, 61, 16));
        label_29 = new QLabel(tab_tennant);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setGeometry(QRect(40, 290, 47, 13));
        label_30 = new QLabel(tab_tennant);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setGeometry(QRect(370, 290, 47, 13));
        tb_t_id = new QLineEdit(tab_tennant);
        tb_t_id->setObjectName(QString::fromUtf8("tb_t_id"));
        tb_t_id->setEnabled(false);
        tb_t_id->setGeometry(QRect(110, 220, 113, 20));
        tb_ob_id = new QLineEdit(tab_tennant);
        tb_ob_id->setObjectName(QString::fromUtf8("tb_ob_id"));
        tb_ob_id->setEnabled(false);
        tb_ob_id->setGeometry(QRect(420, 220, 113, 20));
        tb_t_aid = new QLineEdit(tab_tennant);
        tb_t_aid->setObjectName(QString::fromUtf8("tb_t_aid"));
        tb_t_aid->setGeometry(QRect(700, 220, 113, 20));
        tb_t_vorname = new QLineEdit(tab_tennant);
        tb_t_vorname->setObjectName(QString::fromUtf8("tb_t_vorname"));
        tb_t_vorname->setGeometry(QRect(110, 250, 113, 20));
        tb_t_nachname = new QLineEdit(tab_tennant);
        tb_t_nachname->setObjectName(QString::fromUtf8("tb_t_nachname"));
        tb_t_nachname->setGeometry(QRect(420, 250, 113, 20));
        tb_t_geburtstag = new QLineEdit(tab_tennant);
        tb_t_geburtstag->setObjectName(QString::fromUtf8("tb_t_geburtstag"));
        tb_t_geburtstag->setGeometry(QRect(700, 250, 113, 20));
        tb_t_einzug = new QLineEdit(tab_tennant);
        tb_t_einzug->setObjectName(QString::fromUtf8("tb_t_einzug"));
        tb_t_einzug->setGeometry(QRect(110, 290, 113, 20));
        tb_t_auszug = new QLineEdit(tab_tennant);
        tb_t_auszug->setObjectName(QString::fromUtf8("tb_t_auszug"));
        tb_t_auszug->setGeometry(QRect(420, 290, 113, 20));
        btn_t_reset = new QPushButton(tab_tennant);
        btn_t_reset->setObjectName(QString::fromUtf8("btn_t_reset"));
        btn_t_reset->setGeometry(QRect(110, 360, 75, 23));
        btn_t_save = new QPushButton(tab_tennant);
        btn_t_save->setObjectName(QString::fromUtf8("btn_t_save"));
        btn_t_save->setEnabled(false);
        btn_t_save->setGeometry(QRect(360, 360, 75, 23));
        btn_t_add = new QPushButton(tab_tennant);
        btn_t_add->setObjectName(QString::fromUtf8("btn_t_add"));
        btn_t_add->setGeometry(QRect(620, 360, 75, 23));
        tabWidget->addTab(tab_tennant, QString());
        btn_accept = new QPushButton(QV_Objekt);
        btn_accept->setObjectName(QString::fromUtf8("btn_accept"));
        btn_accept->setGeometry(QRect(864, 630, 101, 23));
        btn_close = new QPushButton(QV_Objekt);
        btn_close->setObjectName(QString::fromUtf8("btn_close"));
        btn_close->setGeometry(QRect(110, 630, 75, 23));

        retranslateUi(QV_Objekt);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(QV_Objekt);
    } // setupUi

    void retranslateUi(QWidget *QV_Objekt)
    {
        QV_Objekt->setWindowTitle(QApplication::translate("QV_Objekt", "QV_Objekt", nullptr));
        label->setText(QApplication::translate("QV_Objekt", "Objekt ID:", nullptr));
        label_2->setText(QApplication::translate("QV_Objekt", "Name:", nullptr));
        label_3->setText(QApplication::translate("QV_Objekt", "Stra\303\237e:", nullptr));
        label_4->setText(QApplication::translate("QV_Objekt", "PLZ:", nullptr));
        label_5->setText(QApplication::translate("QV_Objekt", "Ort:", nullptr));
        label_6->setText(QApplication::translate("QV_Objekt", "Etage:", nullptr));
        label_7->setText(QApplication::translate("QV_Objekt", "Baujahr:", nullptr));
        label_8->setText(QApplication::translate("QV_Objekt", "Gr\303\266\303\237e:", nullptr));
        label_9->setText(QApplication::translate("QV_Objekt", "Zimmer:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_object), QApplication::translate("QV_Objekt", "Objekt", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tbl_equipment->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("QV_Objekt", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tbl_equipment->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("QV_Objekt", "Objekt ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tbl_equipment->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("QV_Objekt", "Erstellungsdatum", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tbl_equipment->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("QV_Objekt", "Fu\303\237boden", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tbl_equipment->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("QV_Objekt", "Sicherung", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tbl_equipment->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("QV_Objekt", "Absicherung [A]", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tbl_equipment->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("QV_Objekt", "Bad|Dusche", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tbl_equipment->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("QV_Objekt", "Waschmaschinenanschl.", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tbl_equipment->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QApplication::translate("QV_Objekt", "Balkon vorhanden", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tbl_equipment->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QApplication::translate("QV_Objekt", "Kabelanschluss", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tbl_equipment->horizontalHeaderItem(10);
        ___qtablewidgetitem10->setText(QApplication::translate("QV_Objekt", "FTTH", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tbl_equipment->horizontalHeaderItem(11);
        ___qtablewidgetitem11->setText(QApplication::translate("QV_Objekt", "Heizungsart", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tbl_equipment->horizontalHeaderItem(12);
        ___qtablewidgetitem12->setText(QApplication::translate("QV_Objekt", "weiteres", nullptr));
        label_10->setText(QApplication::translate("QV_Objekt", "ID:", nullptr));
        label_11->setText(QApplication::translate("QV_Objekt", "Objekt ID:", nullptr));
        label_12->setText(QApplication::translate("QV_Objekt", "Erstellungsdatum:", nullptr));
        label_13->setText(QApplication::translate("QV_Objekt", "Fu\303\237bodenart:", nullptr));
        label_14->setText(QApplication::translate("QV_Objekt", "Sicherung:", nullptr));
        label_15->setText(QApplication::translate("QV_Objekt", "Absicherung in Ampere:", nullptr));
        label_16->setText(QApplication::translate("QV_Objekt", "Bad | Dusche", nullptr));
        label_17->setText(QApplication::translate("QV_Objekt", "Waschmaschinenanschluss:", nullptr));
        label_18->setText(QApplication::translate("QV_Objekt", "Balkon:", nullptr));
        label_19->setText(QApplication::translate("QV_Objekt", "Kabelanschluss:", nullptr));
        label_20->setText(QApplication::translate("QV_Objekt", "FTTH:", nullptr));
        label_21->setText(QApplication::translate("QV_Objekt", "Heizungsart:", nullptr));
        label_22->setText(QApplication::translate("QV_Objekt", "Weiteres:", nullptr));
        cb_sicherung->setItemText(0, QApplication::translate("QV_Objekt", "Schmelzsicherung", nullptr));
        cb_sicherung->setItemText(1, QApplication::translate("QV_Objekt", "Sicherungsautomat", nullptr));

        btn_reset->setText(QApplication::translate("QV_Objekt", "Zur\303\274cksetzen", nullptr));
        btn_save->setText(QApplication::translate("QV_Objekt", "\303\234bernehmen", nullptr));
        btn_add->setText(QApplication::translate("QV_Objekt", "Hinzuf\303\274gen", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_equipment), QApplication::translate("QV_Objekt", "Ausstattung", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tbl_tennant->horizontalHeaderItem(0);
        ___qtablewidgetitem13->setText(QApplication::translate("QV_Objekt", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tbl_tennant->horizontalHeaderItem(1);
        ___qtablewidgetitem14->setText(QApplication::translate("QV_Objekt", "Objekt ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tbl_tennant->horizontalHeaderItem(2);
        ___qtablewidgetitem15->setText(QApplication::translate("QV_Objekt", "Adress ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tbl_tennant->horizontalHeaderItem(3);
        ___qtablewidgetitem16->setText(QApplication::translate("QV_Objekt", "Vorname", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tbl_tennant->horizontalHeaderItem(4);
        ___qtablewidgetitem17->setText(QApplication::translate("QV_Objekt", "Nachname", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tbl_tennant->horizontalHeaderItem(5);
        ___qtablewidgetitem18->setText(QApplication::translate("QV_Objekt", "Geburtstag", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tbl_tennant->horizontalHeaderItem(6);
        ___qtablewidgetitem19->setText(QApplication::translate("QV_Objekt", "Einzugsdatum", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = tbl_tennant->horizontalHeaderItem(7);
        ___qtablewidgetitem20->setText(QApplication::translate("QV_Objekt", "Auszugsdatum", nullptr));
        label_23->setText(QApplication::translate("QV_Objekt", "ID:", nullptr));
        label_24->setText(QApplication::translate("QV_Objekt", "Objekt ID", nullptr));
        label_25->setText(QApplication::translate("QV_Objekt", "Adress ID", nullptr));
        label_26->setText(QApplication::translate("QV_Objekt", "Vorname:", nullptr));
        label_27->setText(QApplication::translate("QV_Objekt", "Nachname:", nullptr));
        label_28->setText(QApplication::translate("QV_Objekt", "Geburtstag:", nullptr));
        label_29->setText(QApplication::translate("QV_Objekt", "Einzug:", nullptr));
        label_30->setText(QApplication::translate("QV_Objekt", "Auszug:", nullptr));
        btn_t_reset->setText(QApplication::translate("QV_Objekt", "Zur\303\274cksetzen", nullptr));
        btn_t_save->setText(QApplication::translate("QV_Objekt", "\303\234bernehmen", nullptr));
        btn_t_add->setText(QApplication::translate("QV_Objekt", "Hinzuf\303\274gen", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_tennant), QApplication::translate("QV_Objekt", "Mieter", nullptr));
        btn_accept->setText(QApplication::translate("QV_Objekt", "Alles \303\234bernehmen", nullptr));
        btn_close->setText(QApplication::translate("QV_Objekt", "Verwerfen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QV_Objekt: public Ui_QV_Objekt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QV_OBJEKT_H
