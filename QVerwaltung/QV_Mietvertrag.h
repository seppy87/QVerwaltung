#pragma once

#include <QWidget>
#include"QVerwaltung.h"
#include "ui_QV_Mietvertrag.h"
#include"tinyxml/ticpp.h"

class QV_Mietvertrag : public QWidget
{
	Q_OBJECT

public:
	QV_Mietvertrag(QWidget *parent = Q_NULLPTR);
	~QV_Mietvertrag();

private:
	Ui::QV_Mietvertrag ui;
	ticpp::Document *doc;

protected:
	void onAddElementClick();
	void onDelElementClick();

	void onResetBtnClick(bool save=false);
	void onAddBtnClick();
};
