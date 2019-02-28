#include "QVerwaltung.h"
#include<qsqldriver.h>
#include<qmessagebox.h>
#include<qstandardpaths.h>
#include<qcryptographichash.h>
#include"LoginDialog.h"
#include"picosha2.hpp"
#include<boost/algorithm/string/case_conv.hpp>
#include<tuple>
#include<qcombobox.h>
#include<Windows.h>
#include<Poco/Path.h>
#include<Poco/File.h>



QVerwaltung::QVerwaltung(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	this->ribbon = new Ribbon(this);
	this->ribbon->setGeometry(this->ui.tabWidget->geometry());
	this->ui.tabWidget->setVisible(false);
	this->ribbon->addTab("Datei");
	QToolButton *btnExit = new QToolButton();
	btnExit->setText("Exit");
	btnExit->setIcon(QIcon(":/icons/icons/exit_ico.png"));
	ribbon->addButton("Datei", "Allgemein", btnExit);
	connect(btnExit, &QToolButton::clicked, this, [&]() {QCoreApplication::quit(); });
	QToolButton *btnSettings = new QToolButton();
	btnSettings->setText("Einstellungen");
	btnSettings->setIcon(QIcon(":/icons/icons/settings.jpg"));
	ribbon->addButton("Datei", "Allgemein", btnSettings);
	connect(btnSettings, &QToolButton::clicked, this, &QVerwaltung::onSettingsClick);
	QToolButton *btnUsers = new QToolButton();
	btnUsers->setText("Benutzer");
	btnUsers->setIcon(QIcon(":/icons/icons/users.png"));
	ribbon->addButton("Datei", "Allgemein", btnUsers);
	connect(btnUsers, &QToolButton::clicked, this, &QVerwaltung::users);
	connect(ui.cb_choose, &QComboBox::currentTextChanged, this, &QVerwaltung::cbIndexChanged);
	ribbon->addTab("Objekt");
	QToolButton* btn_addObject = new QToolButton();
	btn_addObject->setText(lat("Object Hinzufügen"));
	btn_addObject->setIcon(QIcon(":/icons/icons/addobject.png"));
	connect(btn_addObject, &QToolButton::clicked, this, &QVerwaltung::addObject);
	this->ribbon->addButton("Objekt", "Objekte Modifizieren", btn_addObject);
	//Objekt editieren
	QToolButton* btn_editObject = new QToolButton();
	btn_editObject->setText(lat("Objekt bearbeiten"));
	btn_editObject->setIcon(QIcon(":/icons/icons/addobject.png"));
	connect(btn_editObject, &QToolButton::clicked, this, &QVerwaltung::editObject);
	this->ribbon->addButton("Objekt", "Objekte Modifizieren", btn_editObject);
	//Objekt löschen
	QToolButton* btn_delObject = new QToolButton();
	btn_delObject->setText(lat("Objekt löschen"));
	btn_delObject->setIcon(QIcon(":/icons/icons/delete.png"));
	connect(btn_delObject, &QToolButton::clicked, this, &QVerwaltung::delObject);
	this->ribbon->addButton("Objekt", "Objekte Modifizieren", btn_delObject);
	//Ausstattung Hinzufügen
	QToolButton* btn_equip = new QToolButton();
	btn_equip->setText(lat("Ausstattung hinzufügen"));
	btn_equip->setIcon(QIcon(":/icons/icons/equipment.png"));
	connect(btn_equip, &QToolButton::clicked, this, &QVerwaltung::addEquipment);
	this->ribbon->addButton("Objekt", "Ausstattung Modifizieren", btn_equip);
	//Ausstattung bearbeiten
	QToolButton* btn_editequip = new QToolButton();
	btn_editequip->setText(lat("Ausstattung bearbeiten"));
	btn_editequip->setIcon(QIcon(":/icons/icons/equipment.png"));
	connect(btn_editequip, &QToolButton::clicked, this, &QVerwaltung::editEquipment);
	this->ribbon->addButton("Objekt", "Ausstattung Modifizieren", btn_editequip);
	//Ausstattung löschen
	QToolButton* btn_delequip = new QToolButton();
	btn_delequip->setText(lat("Ausstattung löschen"));
	btn_delequip->setIcon(QIcon(":/icons/icons/delete.png"));
	connect(btn_delequip, &QToolButton::clicked, this, &QVerwaltung::delEquipment);
	this->ribbon->addButton("Objekt", "Ausstattung Modifizieren", btn_delequip);
	//TAB Mieter
	this->ribbon->addTab("Mieter");
	QToolButton* btn_addTennant = new QToolButton();
	btn_addTennant->setText(lat("Mieter hinzufügen"));
	btn_addTennant->setIcon(QIcon(":/icons/icons/addcustomer.png"));
	connect(btn_addTennant, &QToolButton::clicked, this, &QVerwaltung::addTennant);
	this->ribbon->addButton("Mieter", "Mieter Modifizieren", btn_addTennant);
	//Mieter Editieren
	QToolButton* btn_editTennant = new QToolButton();
	btn_editTennant->setText(lat("Mieter bearbeiten"));
	btn_editTennant->setIcon(QIcon(":/icons/Resources/edituser.png"));
	connect(btn_editTennant, &QToolButton::clicked, this, &QVerwaltung::editTennant);
	this->ribbon->addButton("Mieter", "Mieter Modifizieren", btn_editTennant);
	//Mieter löschen
	QToolButton* btn_delTennant = new QToolButton();
	btn_delTennant->setText(lat("Mieter löschen"));
	btn_delTennant->setIcon(QIcon(":/icons/icons/deluser.png"));
	connect(btn_delTennant, &QToolButton::clicked, this, &QVerwaltung::delTennant);
	this->ribbon->addButton("Mieter", "Mieter Modifizieren", btn_delTennant);
	//Mieter kontaktieren
	QToolButton* btn_contactTennant = new QToolButton();
	btn_contactTennant->setText(lat("Mieter kontaktieren"));
	btn_contactTennant->setIcon(QIcon(":/icons/icons/mail.png"));
	connect(btn_contactTennant, &QToolButton::clicked, this, &QVerwaltung::contactTennant);
	this->ribbon->addButton("Mieter", "Kommunikation", btn_contactTennant);

	QToolButton* btn_contract = new QToolButton();
	btn_contract->setText("Mietvertrag");
	btn_contract->setIcon(QIcon(":/QVerwaltung/icons/contract.png"));
	connect(btn_contract, &QToolButton::clicked, this, &QVerwaltung::onContractClick);
	this->ribbon->addButton(lat("Verträge"), "Mietvertrag", btn_contract);

	//Programm Details
	QToolButton* btn_update = new QToolButton();
	btn_update->setText("Update");
	btn_update->setIcon(QIcon(":/icons/icons/update.png"));
	connect(btn_update, &QToolButton::clicked, this, &QVerwaltung::onUpdateClick);
	this->ribbon->addButton("Datei", "Programm", btn_update);
	this->ribbon->show();

	connect(this->ui.tbl_overview, &QTableWidget::cellDoubleClicked, this, &QVerwaltung::onTblOverViewCellClick);
	this->init_sqlite();
}

void QVerwaltung::settings() {

}

void QVerwaltung::users() {
	this->dlg_user = new QV_Users(&db);
	dlg_user->show();
}

void QVerwaltung::addObject()
{
	this->frm_object = new QV_Objekt(this,std::optional<QString>());
	this->frm_object->show();
}

void QVerwaltung::editObject()
{
	if (ui.cb_choose->currentText() != "Objekte") return;
	this->onTblOverViewCellClick();
}

void QVerwaltung::delObject()
{
	if (ui.cb_choose->currentText() != "Objekte") return;
	auto rid = this->ui.tbl_overview->currentRow();
	if (rid < 0)return;
	auto res = QMessageBox::question(nullptr, "Sind Sie Sicher?", "Wollen Sie das Objekt wirklich löschen?", QMessageBox::StandardButton::Yes, QMessageBox::StandardButton::No);
	if (res == QMessageBox::StandardButton::No) return;
	auto id = this->ui.tbl_overview->item(rid, 0)->text();
	QSqlQuery q(db);
	q.prepare("DELETE FROM tbl_object WHERE id=?");
	q.addBindValue(id);
	q.exec();
}

void QVerwaltung::addEquipment()
{
}

void QVerwaltung::editEquipment()
{
}

void QVerwaltung::delEquipment()
{

}

void QVerwaltung::addTennant()
{
}

void QVerwaltung::editTennant()
{
}

void QVerwaltung::delTennant()
{
	if (ui.cb_choose->currentText() != "Mieter") return;
	auto rid = this->ui.tbl_overview->currentRow();
	if (rid < 0)return;
	auto res = QMessageBox::question(nullptr, "Sind Sie Sicher?", "Wollen Sie das Mieter wirklich löschen?", QMessageBox::StandardButton::Yes, QMessageBox::StandardButton::No);
	if (res == QMessageBox::StandardButton::No) return;
	auto id = this->ui.tbl_overview->item(rid, 0)->text();
	QSqlQuery q(db);
	q.prepare("DELETE FROM tbl_object WHERE id=?");
	q.addBindValue(id);
	q.exec();
}

void QVerwaltung::contactTennant()
{
}

void QVerwaltung::onTblOverViewCellClick()
{
	auto id = this->ui.tbl_overview->item(this->ui.tbl_overview->currentRow(), 0)->text();
	this->frm_object = new QV_Objekt(this, std::optional<QString>(id), QV_METHOD::EDIT);
	this->frm_object->show();
}

void QVerwaltung::onUpdateClick()
{
	(QV_Update()).exec();
}

void QVerwaltung::onContractClick()
{
	frm_mietvertrag = new QV_Mietvertrag();
	frm_mietvertrag->show();
}

void QVerwaltung::resizeEvent(QResizeEvent* event) {
	QMainWindow::resizeEvent(event);
	auto rect = this->ribbon->geometry();
	rect.setWidth(this->width());
	this->ribbon->setGeometry(rect);
	
}

void QVerwaltung::init_sqlite() {
	//QSqlDriver* driver = new QSqlDriver()
	auto path = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation);
	this->db = QSqlDatabase::addDatabase(DRIVER);
	LPSTR lpBuffer = new char[255];
	ExpandEnvironmentStringsA("%APPDATA%", lpBuffer, 255);
	db.setDatabaseName(QString::fromLatin1(lpBuffer)+"\\QVerwaltung\\db.sqlite");
	auto r = db.open();
	if (!r) {
		QMessageBox::critical(nullptr, "ERROR", "Could not open Database", QMessageBox::StandardButton::Ok);
		QCoreApplication::quit();
	}
	this->login_dlg();
	
}

void QVerwaltung::login_dlg()
{
	LoginDialog dlg;
	connect(&dlg, &LoginDialog::acceptLogin, this, &QVerwaltung::login);
	connect(&dlg, &LoginDialog::closeSignal, qApp, &QCoreApplication::quit,Qt::QueuedConnection);
	//connect(&dlg, &LoginDialog::rejected, qApp, &QCoreApplication::quit, Qt::QueuedConnection);
	dlg.exec();
	disconnect(&dlg);
}

void QVerwaltung::login(QString & name, QString & password, int & index)
{
	std::string hash_hex;
	picosha2::hash256_hex_string(password.toStdString(), hash_hex);
	//auto x = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
	//QMessageBox::information(nullptr, "Info", hash_hex.c_str(), QMessageBox::StandardButton::Ok);
	QSqlQuery query(db);
	query.prepare("SELECT * FROM tbl_user WHERE name=?");
	query.addBindValue(name);
	query.exec();
	//std::tuple<QString, QString, QString> users;
	QString pw;
	while (query.next()) {
		pw = query.value(2).toString();
		this->isRoot = query.value(3).toBool();
		break;
	}
	auto temp = boost::algorithm::to_lower_copy(pw.toStdString());
	if (QString::fromStdString(temp) == QString::fromStdString(hash_hex))
		QMessageBox::information(nullptr, "Information", "Correct");
	else
		login_dlg();
	this->init_objects();
}

void QVerwaltung::init_objects()
{
	this->clearOverview();
	QSqlQuery query(db);
	query.exec("SELECT * FROM tbl_object");
	uint row = 0;
	while (query.next()) {
		
		this->ui.tbl_overview->setRowCount((this->ui.tbl_overview->rowCount())+1);
		auto cs = query.record().count();
		if(row==0)
			this->ui.tbl_overview->setColumnCount(cs);
		for (uint c = 0; c < cs; c++) {
			if (row == 0)
				this->ui.tbl_overview->setHorizontalHeaderItem(c, new QTableWidgetItem(query.record().fieldName(c)));
			this->ui.tbl_overview->setItem(row, c, new QTableWidgetItem(query.value(c).toString()));
		}
		row++;
	}
}

void QVerwaltung::init_mieter()
{
	this->clearOverview();
	QSqlQuery query(db);
	query.exec("SELECT * from tbl_mieter;");
	uint row = 0;
	while (query.next()) {
		this->ui.tbl_overview->setRowCount(this->ui.tbl_overview->rowCount() + 1);
		auto cs = query.record().count();
		if(row==0)
			this->ui.tbl_overview->setColumnCount(cs);
		for (uint c = 0; c < cs; c++) {
			if (row == 0)
				this->ui.tbl_overview->setHorizontalHeaderItem(c, new QTableWidgetItem(query.record().fieldName(c)));
			this->ui.tbl_overview->setItem(row, c, new QTableWidgetItem(query.value(c).toString()));
		}
		row++;
	}

}

void QVerwaltung::cbIndexChanged()
{
	auto text = boost::algorithm::to_lower_copy(this->ui.cb_choose->currentText().toStdString());
	if (text == "objekte") {
		init_objects();
		return;
	}
	if (text == "mieter") {
		init_mieter();
		return;
	}
	
}

void QVerwaltung::clearOverview()
{
	this->ui.tbl_overview->clear();
	this->ui.tbl_overview->setRowCount(0);
	this->ui.tbl_overview->setColumnCount(0);
}

void QVerwaltung::onSettingsClick()
{
	this->frm_settings = new QV_Settings();
	this->frm_settings->show();
}

