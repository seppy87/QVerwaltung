#pragma once

#ifdef _DEBUG
#pragma comment(lib,"podofo\\dynamic\\debug\\podofo.lib")
#pragma comment(lib, "tinyxml\\debug\\ticppd.lib")
#else
#pragma comment(lib,"podofo\\dynamic\\release\\podofo.lib")
#endif

#include <QtWidgets/QMainWindow>
#include "ui_QVerwaltung.h"
#include"Ribbon/ribbon.h"
#include"Ribbon/ribbontabcontent.h"
#include"Ribbon/ribbonbuttongroup.h"

#include<qsqldatabase.h>
#include<qsqldriver.h>
#include<qsqlerror.h>
#include<qsqlquery.h>
#include"QV_Users.h"
#include<qsqlrecord.h>
#include<QMessageLogger>
const QString DRIVER("QSQLITE");

//My Classes
#include"QV_Objekt.h"
#include"QV_Update.h"
#include"QV_Settings.h"
#include"QV_Mietvertrag.h"
#include"QV_Mieter.h"


class QV_Users;
class QV_Objekt;
class QV_Settings;
class QV_Mietvertrag;
class QV_Mieter;
class QVerwaltung : public QMainWindow
{
	Q_OBJECT

public:
	QVerwaltung(QWidget *parent = Q_NULLPTR);

private:
	Ui::QVerwaltungClass ui;
	Ribbon *ribbon;
	QSqlDatabase db;
	bool isRoot = false;
	QV_Users *dlg_user;
	QV_Objekt* frm_object;
	QV_Settings* frm_settings;
	QV_Mietvertrag* frm_mietvertrag;
	QV_Mieter* frm_mieter;

protected:
	void settings();
	void users();
	void addObject();
	void editObject();
	void delObject();
	void addEquipment();
	void editEquipment();
	void delEquipment();

	//Mieter
	void addTennant();
	void editTennant();
	void delTennant();
	void contactTennant();

	void onTblOverViewCellClick();
	void onUpdateClick();
	void onContractClick();

	void resizeEvent(QResizeEvent* event) override;


	//READ SQLITE
	void init_sqlite();
	void login_dlg();
	void login(QString& name, QString& password, int& index);
	
	void init_objects();
	void init_mieter();
	void cbIndexChanged();
	void clearOverview();

	void onSettingsClick();

	void onTennantAddClick();

	friend class QV_Objekt;
	friend class QV_Mietvertrag;
	friend class QV_Mieter;
};
