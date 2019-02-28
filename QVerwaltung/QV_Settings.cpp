#include "QV_Settings.h"
#include<Windows.h>
#include<qmessagebox.h>
QV_Settings::QV_Settings(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
	LPSTR lpBuffer = new char[255];
	ExpandEnvironmentStringsA("%APPDATA%", lpBuffer, 255);
	QString path(lpBuffer);
	
	this->setting = new QSettings(path + "\\QVerwaltung\\main.ini", QSettings::Format::IniFormat);
	//this->setting = new QSettings("main.ini", QSettings::Format::IniFormat);
	this->setting->beginGroup("Stammdaten");
	QMessageBox::information(nullptr, "test", this->setting->value("Firma", "No Value").toString());
	this->setting->endGroup();
	this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
	connect(ui.btn_SiteSave, &QPushButton::clicked, this, &QV_Settings::onSeiteSpeichernClick);

}

QV_Settings::~QV_Settings()
{
}

void QV_Settings::createSettings()
{
}

void QV_Settings::onSeiteSpeichernClick()
{
	auto index = this->ui.tabWidget->currentIndex();
	switch (index) {
	case 0:
		this->setting->beginGroup("Stammdaten");
		this->setting->setValue("Form", [&]() {if (this->ui.radioButton->isChecked()) return QString("Einzelperson"); return QString("Unternehmen"); }());
		this->setting->setValue("Firma", this->ui.tb_unternehmen->text());
		this->setting->setValue("Vorname", this->ui.tb_vorname->text());
		this->setting->setValue("Nachname", this->ui.tb_nachname->text());
		this->setting->setValue("Strasse", this->ui.tb_strasse->text());
		this->setting->setValue("PLZ", this->ui.tb_plz->text());
		this->setting->setValue("Stadt", this->ui.tb_stadt->text());
		this->setting->setValue("UstID", this->ui.tb_uid->text());
		this->setting->setValue("Handelsregister", this->ui.tb_handelsregister->text());
		this->setting->setValue("Telefon", this->ui.tb_telefon->text());
		this->setting->setValue("Fax", this->ui.tb_fax->text());
		this->setting->setValue("EMail", this->ui.tb_email->text());
		this->setting->setValue("Internet", this->ui.tb_internet->text());
		//this->setting->setValue();
		this->setting->sync();
		return;
	}
}
