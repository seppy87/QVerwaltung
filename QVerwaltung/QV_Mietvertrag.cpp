#include "QV_Mietvertrag.h"
#include<Windows.h>
#include<qmessagebox.h>
#include<qfiledialog.h>

QV_Mietvertrag::QV_Mietvertrag(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.groupBox->setVisible(false);
	connect(ui.btn_add, &QToolButton::clicked, this, &QV_Mietvertrag::onAddElementClick);
	connect(ui.btn_del, &QToolButton::clicked, this, &QV_Mietvertrag::onDelElementClick);
	connect(ui.btn_resetPara, &QPushButton::clicked, this, &QV_Mietvertrag::onResetBtnClick);
	connect(ui.btn_addPara, &QPushButton::clicked, this, &QV_Mietvertrag::onAddBtnClick);
	connect(ui.pushButton, &QPushButton::clicked, this, &QV_Mietvertrag::convert2PDF);
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
	int res = QMessageBox::question(nullptr, "Sind Sie sicher?", "Wollen Sie wirklich den Paragraphen entfernen?", QMessageBox::StandardButton::Yes, QMessageBox::StandardButton::No);
	if (res == QMessageBox::StandardButton::No) return;
	auto row = this->ui.tbl_paragraph->currentRow();
	auto groupid = ui.tbl_paragraph->item(row, 2)->text();
	auto pid = ui.tbl_paragraph->item(row, 3)->text();
	auto contract = doc->FirstChildElement("contract");
	auto content = contract->FirstChildElement("content");
	ticpp::Iterator<ticpp::Element> iter;
	for (iter = iter.begin(content->FirstChildElement()->Parent()); iter != iter.end(); iter++) {
		if (iter->GetAttribute("no") == groupid.toStdString()) {
			ticpp::Iterator<ticpp::Element> i;
			for (i = i.begin(iter->FirstChildElement()->Parent()); i != i.end(); i++) {
				if (i->GetAttribute("no") == pid.toStdString()) {
					auto pNode = i->Parent();
					iter->RemoveChild(i->FirstChild()->Parent());
					
					if (iter->NoChildren())
						iter->Parent()->RemoveChild(pNode);
					doc->SaveFile();
					this->ui.tbl_paragraph->removeRow(row);
					return;
				}
			}
		}
	}
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
			ticpp::Text* text = new ticpp::Text(ui.textEdit->toPlainText().toStdString());
			el->LinkEndChild(text);
			iter->LinkEndChild(el);
			this->addToTable(ui.tb_addName->text(), ui.tb_addGroup->text(), iter->GetAttribute("no").c_str(), ui.tb_addParagraph->text(), ui.textEdit->toPlainText());
			onResetBtnClick(true);
			return;
		}
		ticpp::Element* group = new ticpp::Element("group");
		group->SetAttribute("name", ui.tb_addGroup->text().toStdString());
		group->SetAttribute("no", ui.tb_addGroupNo->text().toStdString());
		ticpp::Element* el = new ticpp::Element("paragraph");
		el->SetAttribute("name", ui.tb_addName->text().toStdString());
		el->SetAttribute("no", ui.tb_addParagraph->text().toStdString());
		ticpp::Text* text = new ticpp::Text(ui.textEdit->toPlainText().toStdString());
		el->LinkEndChild(text);
		group->LinkEndChild(el);
		this->addToTable(ui.tb_addName->text(), ui.tb_addGroup->text(), ui.tb_addGroupNo->text(), ui.tb_addParagraph->text(), ui.textEdit->toPlainText());
		content->LinkEndChild(group);
		onResetBtnClick(true);
	}
	catch (ticpp::Exception& ex) {
		QMessageBox::critical(nullptr, "ERROR", QString::fromStdString(ex.what()));
	}
}

void QV_Mietvertrag::addToTable(const QString name, const QString gruppe, const QString gruppennr, const QString paragraph, const QString inhalt)
{
	auto r = this->ui.tbl_paragraph->rowCount();
	ui.tbl_paragraph->setRowCount(r + 1);
	uint c = 0;
	ui.tbl_paragraph->setItem(r, c++, new QTableWidgetItem(name));
	ui.tbl_paragraph->setItem(r, c++, new QTableWidgetItem(gruppe));
	ui.tbl_paragraph->setItem(r, c++, new QTableWidgetItem(gruppennr));
	ui.tbl_paragraph->setItem(r, c++, new QTableWidgetItem(paragraph));
	ui.tbl_paragraph->setItem(r, c++, new QTableWidgetItem(inhalt));
}

void QV_Mietvertrag::convert2PDF()
{

	//retrieve Addresses
	LPSTR lpBuffer = new char[255];
	ExpandEnvironmentStringsA("%APPDATA%", lpBuffer, 255);
	QString path(lpBuffer);

	QSettings *setting = new QSettings(path + "\\QVerwaltung\\main.ini", QSettings::Format::IniFormat);
	setting->setIniCodec("UTF-8");
	setting->beginGroup("Stammdaten");
	std::wstring first;
	if (setting->value("Form").toString() == "Unternehmen")
		first = setting->value("Firma").toString().toStdWString();
	else
		first = QString(setting->value("Vorname").toString() + QString(" ") + setting->value("Nachname").toString()).toStdWString();
	auto strasse = setting->value("Strasse").toString().toStdWString();
	auto plz = setting->value("PLZ").toString().toStdWString();
	auto q = setting->value("Stadt").toString();
	auto stadt = setting->value("Stadt").toString().toStdWString();
	//PoDoFo::PdfString *str = new PoDoFo::PdfString()
	setting->endGroup();

	using namespace PoDoFo;
	auto filename = QFileDialog::getSaveFileName(this, lat("Wähle Speicherort aus"), "neues_document.pdf", tr("Portable Document Format (*.pdf)"), nullptr);
	PdfStreamedDocument document(filename.toStdString().c_str());
	PdfPage* page;
	PdfPainter painter;
	PdfFont* pFont;
	page = document.CreatePage(PdfPage::CreateStandardPageSize(ePdfPageSize_A4));
	if (!page)
		PODOFO_RAISE_ERROR(ePdfError_InvalidHandle);
	painter.SetPage(page);
	pFont = document.CreateFont("Courier");
	pFont->SetFontSize(7);
	painter.SetFont(pFont);
	painter.DrawText(56, page->GetPageSize().GetHeight() - 150, PdfString(std::wstring(first + L" "+strasse + L" " + plz + L" " + stadt).c_str()));
	if (this->ui.cb_tennant->currentText() == "FREI")
	{
		PdfRect rect(56, 600, 250, 90);
		PdfTextField *tf = new PdfTextField(page, rect, &document);
		tf->SetMultiLine(true);
		tf->SetFieldName("tb_addresse");
	}
	painter.FinishPage();
	document.GetInfo()->SetCreator(PdfString(std::string("QVerwaltung - Hausverwaltungssoftware")));
	document.GetInfo()->SetAuthor(PdfString(std::string("VONOVIA")));
	document.GetInfo()->SetTitle(PdfString(std::string("Mietvertrag")));
	document.Close();

}
