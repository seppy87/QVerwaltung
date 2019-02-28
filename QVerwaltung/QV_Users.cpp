#include "QV_Users.h"
#include<qcheckbox.h>
#include<qmenu.h>
#include<qmessagebox.h>
#include<qsqlerror.h>

QV_Users::QV_Users(QSqlDatabase *db, QWidget *parent)
	: QWidget(parent)
{
	this->db = db;
	ui.setupUi(this);
	init_table();
}

void QV_Users::init_table() {
	QSqlQuery query(*db);
	query.exec("SELECT * FROM tbl_user");
	QVector<std::tuple<int, QString, QString, bool>> vec;
	while (query.next()) {
		vec.insert(vec.end(), std::tuple(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(), query.value(3).toBool()));
	}

	this->ui.tbl_users->setRowCount(vec.size());
	uint r = 0;
	
	for (auto el : vec) {
		uint c = 0;
		this->ui.tbl_users->setItem(r, c++, new QTableWidgetItem(QString::number(std::get<0>(el))));
		this->ui.tbl_users->setItem(r, c++, new QTableWidgetItem((std::get<1>(el))));
		this->ui.tbl_users->setItem(r, c++, new QTableWidgetItem((std::get<2>(el))));
		QCheckBox *cb = new QCheckBox();
		cb->setChecked(std::get<3>(el));
		cb->setStyleSheet("margin-left:50%;margin-right:50%;");
		if (std::get<0>(el) == 1)
			cb->setEnabled(false);
		this->ui.tbl_users->setCellWidget(r, c, cb);
		//this->ui.tbl_users->itemAt(r, c)->setTextAlignment(Qt::AlignCenter);
		r++;
	}
	ui.tbl_users->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui.tbl_users, &QTableWidget::customContextMenuRequested, this, &QV_Users::tbl_conextMenu);
	connect(ui.tbl_users, &QTableWidget::cellDoubleClicked, this, &QV_Users::tbl_CellDoubleClick);
	connect(ui.btn_Save, &QPushButton::clicked, this, &QV_Users::saveUser);
	connect(ui.btn_add, &QPushButton::clicked, this, &QV_Users::addUser);
}

void QV_Users::tbl_conextMenu(QPoint p) {
	QMenu* menu = new QMenu(this);
	QAction* delUser = new QAction(lat("Lösche"));
	connect(delUser, &QAction::triggered, this, &QV_Users::deleteUser);
	menu->addAction(delUser);
	QAction* edUser = new QAction(lat("Bearbeiten"));
	connect(edUser, &QAction::triggered, this, &QV_Users::editUser);
	menu->addAction(edUser);
	menu->popup(ui.tbl_users->viewport()->mapToGlobal(p));
}

void QV_Users::deleteUser()
{
	auto id = this->ui.tbl_users->item(this->ui.tbl_users->currentRow(), 0)->text();
	if (id == "1")
	{
		QMessageBox::critical(nullptr, "ERROR", lat("Root Benutzer kann man nicht löschen!"), QMessageBox::StandardButton::Ok);
		return;
	}
	auto res = QMessageBox::question(nullptr, "Sind Sie sicher?", lat("Sind Sie sicher, dass Sie den Benutzer löschen wollen?"), QMessageBox::StandardButton::Yes, QMessageBox::StandardButton::No);
	if (res == QMessageBox::No) return;
	QSqlQuery query(*db);
	bool r = query.exec("DELETE FROM tbl_user WHERE id=" + id);
	if (!r)
		QMessageBox::critical(nullptr, "ERROR", "Konnte SQL Query nicht ausführen", QMessageBox::StandardButton::Ok);
}

void QV_Users::editUser()
{
}

void QV_Users::saveUser()
{
	QSqlQuery query(*db);
	query.prepare("UPDATE tbl_user SET name=? , password=?, admin=? WHERE id=?");
	std::string hash_hex;
	picosha2::hash256_hex_string(this->ui.tb_password->text().toStdString(), hash_hex);
	query.addBindValue(ui.tb_name->text());
	query.addBindValue(QString::fromStdString(hash_hex));
	query.addBindValue(ui.cb_root->isChecked());
	query.addBindValue(this->currentID);
	bool r = query.exec();
	if (!r) {
		QMessageBox::critical(nullptr, "ERROR", lat("Konnte SQL Query nicht ausführen ") + query.lastError().text(), QMessageBox::StandardButton::Ok);
		
	}
	auto txt = query.lastQuery();
	this->resetForm();
}

void QV_Users::addUser()
{
	QSqlQuery query(*db);
	query.prepare("INSERT INTO tbl_user(name,password,admin) VALUES(:username,:passwort,:root)");
	std::string hash_hex;
	picosha2::hash256_hex_string(ui.tb_password->text().toStdString(), hash_hex);
	query.bindValue(":username", ui.tb_name->text());
	query.bindValue(":passwort", QString::fromStdString(hash_hex));
	query.bindValue(":root", ui.cb_root->isChecked());
	bool r = query.exec();
	if (!r) QMessageBox::critical(nullptr, "ERROR", lat("Konnte SQL Query nicht ausführen"), QMessageBox::StandardButton::Ok);
}

void QV_Users::resetForm()
{
	this->ui.btn_Save->setEnabled(false);
	this->currentID = 0;
	this->ui.tb_name->setText("");
	this->ui.tb_password->setText("");
	this->ui.cb_root->setChecked(false);
}

void QV_Users::tbl_CellDoubleClick()
{
	auto row = ui.tbl_users->currentRow();
	this->currentID = this->ui.tbl_users->item(row, 0)->text().toInt();
	this->ui.tb_name->setText(this->ui.tbl_users->item(row, 1)->text());
	auto cb = (QCheckBox*)this->ui.tbl_users->cellWidget(row, 3);
	this->ui.cb_root->setChecked(cb->isChecked());
	this->ui.tabWidget->setCurrentIndex(1);
	this->ui.btn_Save->setEnabled(true);
}

QV_Users::~QV_Users()
{
}
