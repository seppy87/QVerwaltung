#pragma once

#include <QWidget>
#include "ui_QV_Viewer.h"
#include<poppler-qt5.h>



class QV_Viewer : public QWidget
{
	Q_OBJECT

public:
	QV_Viewer(QWidget *parent = Q_NULLPTR);
	~QV_Viewer();

private:
	Ui::QV_Viewer ui;
	Poppler::Document *doc;

protected:
	void print();
};
