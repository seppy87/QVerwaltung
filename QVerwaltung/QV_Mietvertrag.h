#pragma once

#pragma comment(lib,"podofo\\dynamic\\Release\\podofo.lib")

#include <QWidget>
#include"QVerwaltung.h"
#include "ui_QV_Mietvertrag.h"
#include"tinyxml/ticpp.h"
#include"podofo/podofo/podofo.h"
#include<qsettings.h>

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

	inline void addToTable(const QString name, const QString gruppe, const QString gruppennr, const QString paragraph, const QString inhalt);

	void convert2PDF();
};
