#pragma once

#include <QWidget>
#include "ui_QV_Objekt.h"
#include"QVerwaltung.h"
#include<optional>

class QVerwaltung;

enum class QV_METHOD : unsigned int{
	EDIT = 1,
	NEW = 2,
};

class QV_Objekt : public QWidget
{
	Q_OBJECT

public:
	QV_Objekt(QVerwaltung *ptr, std::optional<QString> objectid, QV_METHOD method = QV_METHOD::NEW, QWidget *parent = Q_NULLPTR);
	~QV_Objekt();

private:
	QVerwaltung *parent;
	Ui::QV_Objekt ui;
	bool newObject;
	int selectedEquipmentRow = -1;
	int selectedTennantRow = -1;
	QString oid;

protected:
	void init_forms(QString id);

	void ontblEquipDoubleClick();
	void onBtnResetClick();
	void onBtnSaveClick();
	void onBtnAddClick();
	//Mieter
	void ontblTennantDoubleClick();
	void onBtnTResetClick();
	void onBtnTSaveClick();
	void onBtnTAddClick();

	//GLOBAL
	void onBtnCloseClick();
	void onBtnAcceptClick();

	void createNewObject();
	void updateObject();
	void insertVector(const QVector<QVector<QString>>& set, QString table, QString objectid);

	//static Functions
	static QVector<QVector<QString>> getNewEntries(QTableWidget* tbl);

	//SETUP FORMS
	void setup_gui();
};
