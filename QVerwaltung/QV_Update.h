#pragma once

#include <QDialog>
#include "ui_QV_Update.h"
#include<QtNetwork>

class QV_Update : public QDialog
{
	Q_OBJECT

public:
	QV_Update(QWidget *parent = Q_NULLPTR);
	~QV_Update();

protected:
	void onFinished(QNetworkReply* reply);
	void getChangelog(QNetworkReply* reply);

private:
	Ui::QV_Update ui;
	QNetworkAccessManager versionmanager;
	QNetworkAccessManager changeLogManager;
	bool runned = false;
};
