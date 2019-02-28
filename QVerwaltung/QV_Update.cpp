#include "QV_Update.h"
#include<Windows.h>

QV_Update::QV_Update(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
	connect(&this->versionmanager, &QNetworkAccessManager::finished, this, &QV_Update::onFinished);
	QNetworkRequest _request;
	_request.setUrl(QUrl("https://raw.githubusercontent.com/seppy87/QVerwaltung/master/version.nfo"));
	versionmanager.get(_request);
	//Sleep(1000);
	//disconnect(&this->netmanager);
	connect(&this->changeLogManager, &QNetworkAccessManager::finished, this, &QV_Update::getChangelog);
	
	_request.setUrl(QUrl("https://raw.githubusercontent.com/seppy87/QVerwaltung/master/change.log"));
	changeLogManager.get(_request);
}

void QV_Update::onFinished(QNetworkReply *reply) {
	
	auto r = reply->readAll();
	this->ui.tb_recent->setText(r);
	if (QDate::fromString(this->ui.tb_current->text()) != QDate::fromString(this->ui.tb_recent->text())) {
		this->setWindowTitle(QString::fromLatin1("Aktualisierungen sind verfügbar"));
		this->ui.btn_update->setEnabled(true);
	}
	
}

void QV_Update::getChangelog(QNetworkReply * reply)
{
	auto error = reply->errorString();
	QString t = reply->readAll();
	auto temp = t.toStdString();
	ui.tb_changelog->setText(t);
}

QV_Update::~QV_Update()
{
}
