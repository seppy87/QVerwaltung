#include "QV_Objekt.h"
#include<qdatetime.h>

QV_Objekt::QV_Objekt(QVerwaltung *ptr, std::optional<QString> objectid, QV_METHOD method,QWidget *parent)
	: QWidget(parent)
{
	this->parent = ptr;
	ui.setupUi(this);
	this->setup_gui();
	this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

	switch (method) {
	case QV_METHOD::NEW:
		this->newObject = true;
		break;
	case QV_METHOD::EDIT:
		this->newObject = false;
		if (objectid.has_value() == false)
			throw std::exception("you need to pass an objectid to edit Objects");
		this->init_forms(objectid.value());
		break;
	default:
		throw std::exception("This should not happen");
	}
}

void QV_Objekt::init_forms(QString id) {
	QSqlQuery query(parent->db);
	query.exec("SELECT * FROM tbl_object WHERE id=" + id);
	while (query.next()) {
		this->ui.tb_object_id->setText(id);
		this->ui.tb_object_name->setText(query.value(1).toString());
		this->ui.tb_object_street->setText(query.value(2).toString());
		this->ui.tb_object_zip->setText(query.value(3).toString());
		this->ui.tb_object_city->setText(query.value(4).toString());
		this->ui.tb_object_etage->setText(query.value(5).toString());
		this->ui.tb_object_year->setText(query.value(6).toString());
		this->ui.tb_object_size->setText(query.value(7).toString());
		this->ui.tb_object_zimmer->setText(query.value(8).toString());
		break;
	}
	this->oid = id;
	{
		QSqlQuery qe(parent->db);
		qe.exec("SELECT * FROM tbl_ausstattung WHERE object_id=" + id);
		auto tbl = this->ui.tbl_equipment;
		uint r = 0;
		while (query.next()) {
			uint c = 0;
			tbl->setRowCount(tbl->rowCount() + 1);
			tbl->item(r, c++)->setText(qe.value(0).toString());
			tbl->item(r, c++)->setText(qe.value(1).toString());
			tbl->item(r, c++)->setText(qe.value(2).toString());
			tbl->item(r, c++)->setText(qe.value(3).toString());
			tbl->item(r, c++)->setText(qe.value(4).toString());
			tbl->item(r, c++)->setText(qe.value(5).toString());
			tbl->item(r, c++)->setText(qe.value(6).toString());
			tbl->item(r, c++)->setText(qe.value(7).toString());
			tbl->item(r, c++)->setText(qe.value(8).toString());
			tbl->item(r, c++)->setText(qe.value(9).toString());
			tbl->item(r, c++)->setText(qe.value(10).toString());
			tbl->item(r, c++)->setText(qe.value(11).toString());
			tbl->item(r, c++)->setText(qe.value(12).toString());
			r++;
		}
	}
	{
		QSqlQuery qe(parent->db);
		qe.exec("SELECT * FROM tbl_mieter WHERE object_id=" + id);
		auto tbl = this->ui.tbl_tennant;
		uint r = 0;
		while (qe.next()) {
			uint c = 0;
			tbl->setRowCount(tbl->rowCount() + 1);
			tbl->item(r, c++)->setText(qe.value(0).toString());
			tbl->item(r, c++)->setText(qe.value(1).toString());
			tbl->item(r, c++)->setText(qe.value(2).toString());
			tbl->item(r, c++)->setText(qe.value(3).toString());
			tbl->item(r, c++)->setText(qe.value(4).toString());
			tbl->item(r, c++)->setText(qe.value(5).toString());
			tbl->item(r, c++)->setText(qe.value(6).toString());
			tbl->item(r, c++)->setText(qe.value(7).toString());
			r++;
		}
	}
}

void QV_Objekt::ontblEquipDoubleClick()
{
	auto tbl = ui.tbl_equipment;
	this->selectedEquipmentRow = this->ui.tbl_equipment->currentRow();
	this->ui.tb_e_id->setText(tbl->item(selectedEquipmentRow, 0)->text());
	this->ui.tb_e_objectid->setText(tbl->item(selectedEquipmentRow, 1)->text());
	this->ui.tb_e_creation->setText(tbl->item(selectedEquipmentRow, 2)->text());
	this->ui.tb_e_fussboden->setText(tbl->item(selectedEquipmentRow, 3)->text());
	this->ui.tb_e_bad->setText(tbl->item(selectedEquipmentRow, 6)->text());
	if (tbl->item(selectedEquipmentRow, 4)->text() == "Schmelzsicherung")
		this->ui.cb_sicherung->setCurrentIndex(0);
	else if (tbl->item(selectedEquipmentRow, 4)->text() == "Sicherungsautomat")
		this->ui.cb_sicherung->setCurrentIndex(1);
	this->ui.tb_e_fusevalue->setText(tbl->item(selectedEquipmentRow, 5)->text());
	this->ui.tb_e_waschmaschine->setText(tbl->item(selectedEquipmentRow, 7)->text());
	this->ui.tb_e_balkon->setText(tbl->item(selectedEquipmentRow, 8)->text());
	this->ui.tb_e_kabelanschluss->setText(tbl->item(selectedEquipmentRow, 9)->text());
	this->ui.tb_ftth->setText(tbl->item(selectedEquipmentRow, 10)->text());
	this->ui.tb_heizung->setText(tbl->item(selectedEquipmentRow, 11)->text());
	this->ui.tb_weiteres->setText(tbl->item(selectedEquipmentRow, 12)->text());
	this->ui.btn_save->setEnabled(true);
}

void QV_Objekt::onBtnResetClick()
{
	this->selectedEquipmentRow = -1;
	//auto list = ui.tab_equipment->findChildren<QLineEdit*>("");
	auto list = ui.tab_equipment->children();
	for (auto item : list) {
		QLineEdit* tb = qobject_cast<QLineEdit*>(item);
		if (tb == 0) continue;
		tb->setText("");
	}
	this->ui.tb_weiteres->setText("");
	this->ui.btn_save->setEnabled(false);
}

void QV_Objekt::onBtnSaveClick()
{
	if (this->selectedEquipmentRow < 0) return;
	if (this->newObject || this->ui.tbl_equipment->item(selectedEquipmentRow,0)->text()=="-1") {
		auto tbl = this->ui.tbl_equipment;
		//tbl->setRowCount(tbl->rowCount() + 1);
		//auto index = tbl->rowCount() - 1;
		auto index = this->selectedEquipmentRow;
		tbl->item(index, 0)->setText("-1");
		tbl->item(index, 1)->setText("-1");
		tbl->item(index, 2)->setText(QDateTime::currentDateTime().toString());
		tbl->item(index, 3)->setText(ui.tb_e_fussboden->text());
		tbl->item(index, 4)->setText(this->ui.cb_sicherung->currentText());
		tbl->item(index, 5)->setText(ui.tb_e_fusevalue->text());
		tbl->item(index, 6)->setText(ui.tb_e_bad->text());
		tbl->item(index, 7)->setText(ui.tb_e_waschmaschine->text());
		tbl->item(index, 8)->setText(ui.tb_e_balkon->text());
		tbl->item(index, 9)->setText(ui.tb_e_kabelanschluss->text());
		tbl->item(index, 10)->setText(ui.tb_ftth->text());
		tbl->item(index, 11)->setText(ui.tb_heizung->text());
		tbl->item(index, 12)->setText(ui.tb_weiteres->toPlainText());
	}
	else {
		QSqlQuery query(this->parent->db);
		query.prepare("UPDATE tbl_ausstattung SET "
			"erstellungsdatum=?, "
			"fussbode=?, "
			"sicherung=?, "
			"sicherungswert=?, "
			"bad_dusche=?, "
			"waschmaschine=?, "
			"balkon=?, "
			"kabelanschluss=?, "
			"ftth=?, "
			"heizungsart=?, "
			"weiteres=? WHERE id=? AND object_id=?");
		query.addBindValue(ui.tb_e_creation->text());
		query.addBindValue(ui.tb_e_fussboden->text());
		query.addBindValue(ui.cb_sicherung->currentText());
		query.addBindValue(ui.tb_e_fusevalue->text());
		query.addBindValue(ui.tb_e_bad->text());
		query.addBindValue(ui.tb_e_waschmaschine->text());
		query.addBindValue(ui.tb_e_balkon->text());
		query.addBindValue(ui.tb_e_kabelanschluss->text());
		query.addBindValue(ui.tb_ftth->text());
		query.addBindValue(ui.tb_heizung->text());
		query.exec();
	}
	this->onBtnResetClick();

}

void QV_Objekt::onBtnAddClick()
{
	auto tbl = this->ui.tbl_equipment;
	tbl->setRowCount(tbl->rowCount() + 1);
	auto index = tbl->rowCount() - 1;
	//auto index = this->selectedEquipmentRow;
	uint c = 0;
	tbl->setItem(index, c++,new QTableWidgetItem("-1"));
	tbl->setItem(index, c++, new QTableWidgetItem("-1"));
	tbl->setItem(index, c++, new QTableWidgetItem((QDateTime::currentDateTime().toString())));
	tbl->setItem(index, c++, new QTableWidgetItem(ui.tb_e_fussboden->text()));
	tbl->setItem(index, c++, new QTableWidgetItem((this->ui.cb_sicherung->currentText())));
	tbl->setItem(index, c++, new QTableWidgetItem((ui.tb_e_fusevalue->text())));
	tbl->setItem(index, c++, new QTableWidgetItem(ui.tb_e_bad->text()));
	tbl->setItem(index, c++, new QTableWidgetItem(ui.tb_e_waschmaschine->text()));
	tbl->setItem(index, c++, new QTableWidgetItem(ui.tb_e_balkon->text()));
	tbl->setItem(index, c++, new QTableWidgetItem(ui.tb_e_kabelanschluss->text()));
	tbl->setItem(index, c++, new QTableWidgetItem(ui.tb_ftth->text()));
	tbl->setItem(index, c++, new QTableWidgetItem(ui.tb_heizung->text()));
	tbl->setItem(index, c++, new QTableWidgetItem(ui.tb_weiteres->toPlainText()));
}

void QV_Objekt::ontblTennantDoubleClick()
{
	this->selectedTennantRow = this->ui.tbl_tennant->currentRow();
	uint c = 0;
	this->ui.tb_t_id->setText(ui.tbl_tennant->item(selectedTennantRow, c++)->text());
	this->ui.tb_ob_id->setText(ui.tbl_tennant->item(selectedTennantRow, c++)->text());
	this->ui.tb_t_aid->setText(ui.tbl_tennant->item(selectedTennantRow, c++)->text());
	this->ui.tb_t_vorname->setText(ui.tbl_tennant->item(selectedTennantRow, c++)->text());
	this->ui.tb_t_nachname->setText(ui.tbl_tennant->item(selectedTennantRow, c++)->text());
	this->ui.tb_t_geburtstag->setText(ui.tbl_tennant->item(selectedTennantRow, c++)->text());
	this->ui.tb_t_einzug->setText(ui.tbl_tennant->item(selectedTennantRow, c++)->text());
	this->ui.tb_t_auszug->setText(ui.tbl_tennant->item(selectedTennantRow, c++)->text());
	this->ui.btn_t_save->setEnabled(true);
}

void QV_Objekt::onBtnTResetClick()
{
	this->selectedTennantRow = -1;
	auto list = this->ui.tab_tennant->children();
	for (auto item : list) {
		QLineEdit* i = qobject_cast<QLineEdit*>(item);
		if (i == 0) continue;
		i->setText("");
	}
}

void QV_Objekt::onBtnTSaveClick()
{
	if (this->selectedTennantRow < 0) return;
	if (this->newObject || this->ui.tbl_tennant->item(selectedTennantRow, 0)->text() == "-1") {
		auto tbl = this->ui.tbl_tennant;
		uint c = 0;
		tbl->item(selectedTennantRow, c++)->setText("-1");
		tbl->item(selectedTennantRow, c++)->setText("-1");
		tbl->item(selectedTennantRow, c++)->setText("-1");
		tbl->item(selectedTennantRow, c++)->setText(ui.tb_t_vorname->text());
		tbl->item(selectedTennantRow, c++)->setText(ui.tb_t_nachname->text());
		tbl->item(selectedTennantRow, c++)->setText(ui.tb_t_geburtstag->text());
		tbl->item(selectedTennantRow, c++)->setText(ui.tb_t_einzug->text());
		tbl->item(selectedTennantRow, c++)->setText(ui.tb_t_auszug->text());
		this->onBtnTResetClick();
	}
	else {
		QSqlQuery q(parent->db);
		q.prepare("UPDATE tbl_mieter SET "
			"vorname=?, "
			"nachname=?, "
			"geburtstag=?, "
			"einzugsdatum=?, "
			"auszugsdatum=? WHERE id=?"
		);
		q.addBindValue(this->ui.tb_t_vorname->text());
		q.addBindValue(this->ui.tb_t_nachname->text());
		q.addBindValue(this->ui.tb_t_geburtstag->text());
		q.addBindValue(this->ui.tb_t_einzug->text());
		q.addBindValue(this->ui.tb_t_auszug->text());
		q.addBindValue(this->ui.tb_t_id->text());
		q.exec();
	}
	this->onBtnTResetClick();
}

void QV_Objekt::onBtnTAddClick()
{
	auto tbl = ui.tbl_tennant;
	tbl->setRowCount(tbl->rowCount() + 1);
	uint r = tbl->rowCount() - 1;
	uint c = 0;
	tbl->setItem(r, c++, new QTableWidgetItem("-1"));
	tbl->setItem(r, c++, new QTableWidgetItem("-1"));
	tbl->setItem(r, c++, new QTableWidgetItem("-1"));
	tbl->setItem(r, c++, new QTableWidgetItem(ui.tb_t_vorname->text()));
	tbl->setItem(r, c++, new QTableWidgetItem(ui.tb_t_nachname->text()));
	tbl->setItem(r, c++, new QTableWidgetItem(ui.tb_t_geburtstag->text()));
	tbl->setItem(r, c++, new QTableWidgetItem(ui.tb_t_einzug->text()));
	tbl->setItem(r, c++, new QTableWidgetItem(ui.tb_t_auszug->text()));
}

QV_Objekt::~QV_Objekt()
{
}


void QV_Objekt::onBtnCloseClick()
{
}

void QV_Objekt::onBtnAcceptClick()
{
	if (this->newObject) {
		createNewObject();
		return;
	}
	updateObject();
}

void QV_Objekt::createNewObject()
{
	QString oid;
	{
		QSqlQuery q(parent->db);
		q.prepare("INSERT INTO tbl_object(name,strasse,plz,stadt,etage,baujahr,groesse,zimmer) VALUES( ? , ? , ? , ? , ? , ? , ? , ? )");
		q.addBindValue(ui.tb_object_name->text());
		q.addBindValue(ui.tb_object_street->text());
		q.addBindValue(ui.tb_object_zip->text());
		q.addBindValue(ui.tb_object_city->text());
		q.addBindValue(ui.tb_object_etage->text());
		q.addBindValue(ui.tb_object_year->text());
		q.addBindValue(ui.tb_object_size->text());
		q.addBindValue(ui.tb_object_zimmer->text());
		q.exec();
	}
	{
		QSqlQuery q(parent->db);
		q.exec("SELECT MAX(id) FROM tbl_object");
		q.next();
		oid = q.value(0).toString();
	}
	{
		QVector<QVector<QString>> rows;
		auto tbl = ui.tbl_equipment;
		for (uint r = 0; r < tbl->rowCount(); r++) {
			if (tbl->item(r, 0)->text() != "-1") continue;
			QVector<QString> set;
			for (uint c = 0; c < tbl->columnCount(); c++) {
				set.insert(set.end(), tbl->item(r, c)->text());
			}
			rows.insert(rows.end(), set);
		}
		if (rows.size() > 0) this->insertVector(rows,"tbl_ausstattung",oid);
	}
	{
		QVector<QVector<QString>> rows;
		auto tbl = ui.tbl_tennant;
		for (uint r = 0; r < tbl->rowCount(); r++) {
			if (tbl->item(r, 0)->text() == "-1") continue;
			QVector<QString> set;
			for (uint c = 0; c < tbl->colorCount(); c++) {
				set.insert(set.end(), tbl->item(r, c)->text());
			}
			rows.insert(rows.end(), set);
		}
		if (rows.size() > 0) this->insertVector(rows, "tbl_mieter",oid);
	}
}

void QV_Objekt::updateObject()
{
	QString oid = ui.tb_object_id->text();
	QSqlQuery q(parent->db);
	q.prepare("UPDATE tbl_object SET "
		"name=?, "
		"strasse=?, "
		"plz=?, "
		"stadt=?, "
		"etage=?, "
		"baujahr=?, "
		"groesse=?, "
		"zimmer=? WHERE id=?"
	);
	q.addBindValue(ui.tb_object_name->text());
	q.addBindValue(ui.tb_object_street->text());
	q.addBindValue(ui.tb_object_zip->text());
	q.addBindValue(ui.tb_object_city->text());
	q.addBindValue(ui.tb_object_etage->text());
	q.addBindValue(ui.tb_object_year->text());
	q.addBindValue(ui.tb_object_size->text());
	q.addBindValue(ui.tb_object_zimmer->text());
	q.exec();
	this->insertVector(QV_Objekt::getNewEntries(ui.tbl_equipment),"tbl_ausstattung",oid);
	this->insertVector(QV_Objekt::getNewEntries(ui.tbl_tennant),"tbl_mieter",oid);
	
}

void QV_Objekt::insertVector(const QVector<QVector<QString>>& set, QString table, QString objectid)
{
	QSqlQuery q(parent->db);
	if (table == "tbl_ausstattung")
	{
		q.prepare("INSERT INTO tbl_ausstattung(object_id , erstellungsdatum, fussboden , sicherung , sicherungswert , bad_dusche , waschmaschine , balkon , Kabelanschluss , ftth , heizungsart , weiteres )"
			"VALUES( ? , ? , ? , ? , ? , ? , ? , ? , ? , ? , ? , ? )");
		q.addBindValue(objectid);
		q.addBindValue(QDateTime::currentDateTime().toString());
		q.addBindValue(ui.tb_e_fussboden->text());
		q.addBindValue(ui.cb_sicherung->currentText());
		q.addBindValue(ui.tb_e_fusevalue->text());
		q.addBindValue(ui.tb_e_bad->text());
		q.addBindValue(ui.tb_e_waschmaschine->text());
		q.addBindValue(ui.tb_e_balkon->text());
		q.addBindValue(ui.tb_e_kabelanschluss->text());
		q.addBindValue(ui.tb_ftth->text());
		q.addBindValue(ui.tb_heizung->text());
		q.addBindValue(ui.tb_weiteres->toPlainText());
		q.exec();
		return;
	}
	if (table == "tbl_mieter") {
		q.prepare("INSERT INTO tbl_mieter( objectid , address_id , vorname , nachname , geburtstag , einzugs_datum , auszugs_datum )"
			"VALUES( ? , ? , ? , ? , ? , ? , ? )");
		q.addBindValue(objectid);
		q.addBindValue("0");
		q.addBindValue(ui.tb_t_vorname->text());
		q.addBindValue(ui.tb_t_nachname->text());
		q.addBindValue(ui.tb_t_geburtstag->text());
		q.addBindValue(ui.tb_t_einzug->text());
		q.addBindValue(ui.tb_t_auszug->text());
		q.exec();
		return;
	}
	
}

QVector<QVector<QString>> QV_Objekt::getNewEntries(QTableWidget * tbl)
{
	
	QVector<QVector<QString>> result;
	for (uint r = 0; r < tbl->rowCount(); r++) {
		if (tbl->item(r, 0)->text() == "-1") continue;
		QVector<QString> set;
		for (uint c = 0; c < tbl->columnCount(); c++) {
			set.insert(set.end(), tbl->item(r, c)->text());
		}
		result.insert(result.end(), set);
	}
	return result;
}

void QV_Objekt::setup_gui() {

	//SETUP TBL_EQUIPMENT
	this->ui.tbl_equipment->setColumnWidth(0, 15);
	this->ui.tbl_equipment->setColumnWidth(1, 15);
	connect(this->ui.tbl_equipment, &QTableWidget::cellDoubleClicked, this, &QV_Objekt::ontblEquipDoubleClick);
	connect(this->ui.btn_reset, &QPushButton::clicked, this, &QV_Objekt::onBtnResetClick);
	connect(this->ui.btn_save, &QPushButton::clicked, this, &QV_Objekt::onBtnSaveClick);
	connect(this->ui.btn_add, &QPushButton::clicked, this, &QV_Objekt::onBtnAddClick);
	connect(this->ui.btn_t_reset, &QPushButton::clicked, this, &QV_Objekt::onBtnTResetClick);
	connect(this->ui.btn_t_save, &QPushButton::clicked, this, &QV_Objekt::onBtnTSaveClick);
	connect(this->ui.btn_t_add, &QPushButton::clicked, this, &QV_Objekt::onBtnTAddClick);
	connect(this->ui.btn_accept, &QPushButton::clicked, this, &QV_Objekt::onBtnAcceptClick);
	connect(this->ui.btn_close, &QPushButton::clicked, this, [&]() {this->close(); });
}