#include "QV_Mieter.h"

QV_Mieter::QV_Mieter(QVerwaltung* ptr, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->parent = ptr;
	connect(ui.btn_ok, &QPushButton::clicked, this, &QV_Mieter::onBtnOkClick);
}

QV_Mieter::~QV_Mieter()
{
}

void QV_Mieter::showWindow(QString id)
{
	this->id = id;
	QSqlQuery q(parent->db);
	q.exec("SELECT * FROM tbl_mieter WHERE id=" + id);
	q.next();
	auto addressid = q.value(2).toString();
	QSqlQuery r(parent->db);
	r.exec("SELECT * FROM tbl_adresse WHERE id=" + addressid);
	r.next();
	ui.tb_vorname->setText(q.value(3).toString());
	ui.tb_nachname->setText(q.value(4).toString());
	ui.tb_geburtstag->setText(q.value(5).toString());
	ui.tb_einzug->setText(q.value(6).toString());
	ui.tb_auszug->setText(q.value(7).toString());
	ui.tb_strasse->setText(r.value(2).toString());
	ui.tb_plz->setText(r.value(3).toString());
	ui.tb_stadt->setText(r.value(4).toString());
	this->show();
}

void QV_Mieter::onBtnOkClick()
{
	if (this->id == "-1") {
		this->onBtnOkInsertClick();
		return;
	}
	this->onBtnOkUpdateClick();
}

void QV_Mieter::onBtnOkInsertClick()
{
	QSqlQuery q(parent->db);
	q.prepare("INSERT INTO tbl_mieter(vorname,nachname,geburtstag,einzugs_datum,auszugsdatum) VALUES( ? , ? , ? , ? , ? )");
	q.addBindValue(ui.tb_vorname->text());
	q.addBindValue(ui.tb_nachname->text());
	q.addBindValue(ui.tb_geburtstag->text());
	q.addBindValue(ui.tb_einzug->text());
	q.addBindValue(ui.tb_auszug->text());
	q.exec();
	//q.clear();
	q.exec("SELECT MAX(ID) FROM tbl_mieter");
	q.next();
	auto pid = q.value(0).toString();
	q.prepare("INSERT INTO tbl_adresse( pid , strasse , plz , stardt ) VALUES( ? , ? , ? , ? )");
	q.addBindValue(pid);
	q.addBindValue(ui.tb_strasse->text());
	q.addBindValue(ui.tb_plz->text());
	q.addBindValue(ui.tb_stadt->text());
	q.exec();
	q.exec("SELECT MAX(ID) FROM tbl_adresse");
	q.next();
	auto aid = q.value(0).toString();
	q.prepare("UPDATET tbl_mieter SET address_id=? WHERE id=?");
	q.addBindValue(aid);
	q.addBindValue(pid);
	q.exec();
}

void QV_Mieter::onBtnOkUpdateClick()
{
	QSqlQuery q(parent->db);
	q.prepare("UPDATE tbl_mieter SET "
			"vorname=?, "
			"nachname=?, "
			"geburtstag=?, "
			"einzugs_datum=?, "
			"auszugs_datum=? WHERE id= ?"
	);
	q.addBindValue(ui.tb_vorname->text());
	q.addBindValue(ui.tb_nachname->text());
	q.addBindValue(ui.tb_geburtstag->text());
	q.addBindValue(ui.tb_einzug->text());
	q.addBindValue(ui.tb_auszug->text());
	q.addBindValue(this->id);
	q.exec();
	QSqlQuery a(parent->db);
	a.prepare("UPDATE tbl_adresse SET "
		"strasse=?, "
		"plz=?, "
		"stadt=? WHERE pid=?"
	);
	a.addBindValue(ui.tb_strasse->text());
	a.addBindValue(ui.tb_plz->text());
	a.addBindValue(ui.tb_stadt->text());
	a.addBindValue(this->id);
	a.exec();
	
}

void QV_Mieter::onBtnAbortClick()
{
	for (auto child : this->children()) {
		auto item = qobject_cast<QLineEdit*>(child);
		if (!item) continue;
		item->setText("");
	}
}
