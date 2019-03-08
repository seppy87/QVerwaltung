#pragma once

#include <QWidget>
#include"QVerwaltung.h"
#include "ui_QV_Mieter.h"


class QVerwaltung;
class QV_Mieter : public QWidget
{
	Q_OBJECT

public:
	QV_Mieter(QVerwaltung* ptr = nullptr, QWidget *parent = Q_NULLPTR);
	~QV_Mieter();
	void showWindow(QString id);

private:
	Ui::QV_Mieter ui;
	QVerwaltung* parent;
	QString id = "-1";
protected:
	void onBtnOkClick();
	void onBtnOkInsertClick();
	void onBtnOkUpdateClick();
	void onBtnAbortClick();
};
