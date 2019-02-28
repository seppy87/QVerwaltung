#pragma once


#include <QWidget>
#include "ui_QV_Users.h"
#include<qsqldatabase.h>
#include<qsqlquery.h>
#include<qsql.h>
#include"picosha2.hpp"

#define lat(x) QString::fromLatin1(x)

class QV_Users : public QWidget
{
	Q_OBJECT

public:
	QV_Users(QSqlDatabase *db, QWidget *parent = Q_NULLPTR);
	~QV_Users();

private:
	Ui::QV_Users ui;
	QSqlDatabase* db;
	uint currentID = 0;

protected:
	void init_table();
	void tbl_conextMenu(QPoint p);

	//QActions
	void deleteUser();
	void editUser();
	void saveUser();
	void addUser();
	void resetForm();

	void tbl_CellDoubleClick();
};
