#include "QV_Settings.h"
#include<Windows.h>
#include<qmessagebox.h>
QV_Settings::QV_Settings(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
	LPWSTR lpBuffer = new wchar_t[255];
	ExpandEnvironmentStringsW(L"%APPDATA%", lpBuffer, 255);
	QString path(QString::fromStdWString(lpBuffer));
	
	this->setting = new QSettings(path + "\\QVerwaltung\\main.ini", QSettings::Format::IniFormat);
	//this->setting = new QSettings("main.ini", QSettings::Format::IniFormat);
	this->setting->beginGroup("Stammdaten");
	QMessageBox::information(nullptr, "test", this->setting->value("Firma", "No Value").toString());
	this->setting->endGroup();
	this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
	connect(ui.btn_SiteSave, &QPushButton::clicked, this, &QV_Settings::onSeiteSpeichernClick);
	this->setupForm();
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
		this->setting->setValue("Form", [&]() {if (this->ui.rb_privat->isChecked()) return QString("Einzelperson"); return QString("Unternehmen"); }());
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

void QV_Settings::setupForm()
{
	this->setting->beginGroup("Stammdaten");
	auto form = this->setting->value("Form", "Privat").toString();
	if (form == "Unternehmen")
		this->ui.rb_commercial->setChecked(true);
	else
		this->ui.rb_privat->setChecked(true);
	ui.tb_unternehmen->setText(setting->value("Firma", " ").toString());
	ui.tb_vorname->setText(setting->value("Vorname", " ").toString());
	ui.tb_nachname->setText(setting->value("Nachname", " ").toString());
	ui.tb_strasse->setText(setting->value("Strasse", " ").toString());
	ui.tb_plz->setText(setting->value("PLZ", " ").toString());
	ui.tb_stadt->setText(setting->value("Stadt", " ").toString());
	ui.tb_uid->setText(setting->value("UstID", " ").toString());
	ui.tb_handelsregister->setText(setting->value("Handelsregister", " ").toString());
	ui.tb_telefon->setText(setting->value("Telefon", " ").toString());
	ui.tb_fax->setText(setting->value("Fax", " ").toString());
	ui.tb_email->setText(setting->value("EMail", " ").toString());
	ui.tb_internet->setText(setting->value("Internet", " ").toString());
}
