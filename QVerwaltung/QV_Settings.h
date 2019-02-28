#pragma once

#include <QWidget>
#include "ui_QV_Settings.h"
#include<qsettings.h>
#include<qfile.h>
#include"QVerwaltung.h"

class QV_Settings : public QWidget
{
	Q_OBJECT

public:
	QV_Settings(QWidget *parent = Q_NULLPTR);
	~QV_Settings();
	const QSettings* getSettings() { return setting; }

private:
	Ui::QV_Settings ui;
	
	QSettings *setting;

protected:
	void createSettings();
	void onSeiteSpeichernClick();
};
