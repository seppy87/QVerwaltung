#include "QV_Mietvertrag.h"
#include<Windows.h>
#include<qmessagebox.h>

QV_Mietvertrag::QV_Mietvertrag(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.groupBox->setVisible(false);
	connect(ui.btn_add, &QToolButton::clicked, this, &QV_Mietvertrag::onAddElementClick);
	connect(ui.btn_del, &QToolButton::clicked, this, &QV_Mietvertrag::onDelElementClick);
	connect(ui.btn_resetPara, &QPushButton::clicked, this, &QV_Mietvertrag::onResetBtnClick);
	connect(ui.btn_addPara, &QPushButton::clicked, this, &QV_Mietvertrag::onAddBtnClick);
	ui.tbl_paragraph->setColumnWidth(4, 200);
	LPSTR lpBuffer = new char[255];
	ExpandEnvironmentStringsA("%APPDATA%", lpBuffer, 255);
	std::string file = lpBuffer;
	file += "\\QVerwaltung\\vertrag\\mietvertrag.xml";
	this->doc = new ticpp::Document(file);
	doc->LoadFile(TiXmlEncoding::TIXML_ENCODING_UTF8);
	auto contract = doc->FirstChildElement();
	auto spec = contract->FirstChildElement("specification");
	auto text = spec->FirstChild()->ToText()->Value();
	std::string str(text);
	if (str != "Mietvertrag") {
		QMessageBox::warning(nullptr, "Warnung", "Spezifikation der XML ist nicht Mietvertrag");
	}
	auto content = contract->FirstChildElement("content");
	ticpp::Iterator<ticpp::Element> iter;
	for (iter = iter.begin(content); iter != iter.end(); iter++) {
		std::string groupname = iter->GetAttribute("name");
		auto groupno = iter->GetAttribute("no");
		ticpp::Iterator<ticpp::Element> it;
		for (it = it.begin(iter->FirstChildElement()->Parent()); it != it.end(); it++) {
			ui.tbl_paragraph->setRowCount(ui.tbl_paragraph->rowCount() + 1);
			ui.tbl_paragraph->setItem(ui.tbl_paragraph->rowCount() - 1, 0, new QTableWidgetItem(QString::fromStdString(it->GetAttribute("name"))));
			ui.tbl_paragraph->setItem(ui.tbl_paragraph->rowCount() - 1, 1, new QTableWidgetItem(lat(groupname.c_str())));
			ui.tbl_paragraph->setItem(ui.tbl_paragraph->rowCount() - 1, 2, new QTableWidgetItem(lat(groupno.c_str())));
			ui.tbl_paragraph->setItem(ui.tbl_paragraph->rowCount() - 1, 3, new QTableWidgetItem(lat(it->GetAttribute("no").c_str())));
			ui.tbl_paragraph->setItem(ui.tbl_paragraph->rowCount() - 1, 4, new QTableWidgetItem(QString::fromStdString(it->FirstChild()->Value())));
			
		}
	}
	
}

QV_Mietvertrag::~QV_Mietvertrag()
{
}

void QV_Mietvertrag::onAddElementClick()
{
	this->ui.groupBox->setVisible(true);
}

void QV_Mietvertrag::onDelElementClick()
{
}

void QV_Mietvertrag::onResetBtnClick(bool save)
{
	if (save)
		doc->SaveFile();
}

void QV_Mietvertrag::onAddBtnClick()
{
	try {
		auto contract = this->doc->FirstChildElement("contract");
		auto content = contract->FirstChildElement("content");
		ticpp::Iterator<ticpp::Element> iter;
		auto groupname = this->ui.tb_addGroup->text();
		
		for (iter = iter.begin(content->FirstChildElement()->Parent()); iter != iter.end(); iter++) {
			if (iter->GetAttribute("name") != groupname.toStdString())continue;
			ticpp::Element* el = new ticpp::Element("paragraph");
			el->SetAttribute("name", ui.tb_addName->text().toStdString());
			el->SetAttribute("no", ui.tb_addParagraph->text().toStdString());
			ticpp::Text* text = new ticpp::Text(ui.textEdit->toPlainText());
			el->LinkEndChild(text);
			iter->LinkEndChild(el);
			onResetBtnClick(true);
			return;
		}
		ticpp::Element* group = new ticpp::Element("group");
		group->SetAttribute("name", ui.tb_addGroup->text().toStdString());
		group->SetAttribute("no", ui.tb_addGroupNo->text().toStdString());
		ticpp::Element* el = new ticpp::Element("paragraph");
		el->SetAttribute("name", ui.tb_addName->text().toStdString());
		el->SetAttribute("no", ui.tb_addParagraph->text().toStdString());
		ticpp::Text* text = new ticpp::Text(ui.textEdit->toPlainText());
		el->LinkEndChild(text);
		group->LinkEndChild(el);
		content->LinkEndChild(group);
		onResetBtnClick(true);
	}
	catch (ticpp::Exception& ex) {
		QMessageBox::critical(nullptr, "ERROR", QString::fromStdString(ex.what()));
	}
}
