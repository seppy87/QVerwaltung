#include "QV_Mietvertrag.h"
#include<Windows.h>
#include<qmessagebox.h>
#include<qfiledialog.h>
#include"QV_Viewer.h"

QV_Mietvertrag::QV_Mietvertrag(QVerwaltung *pwindow, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->ptr = pwindow;
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
	connect(ui.debug_pdf, &QPushButton::clicked, this, &QV_Mietvertrag::showPDF);
	//Tennant auffüllen
	QSqlQuery q(ptr->db);
	q.prepare("SELECT tbl_mieter.id, tbl_mieter.vorname, tbl_mieter.nachname, tbl_object.id, tbl_object.strasse, tbl_object.etage FROM tbl_mieter, tbl_object");
	if (q.exec()) {
		while (q.next()) {
			ui.cb_tennant->addItem(q.value(0).toString() + ";" + q.value(1).toString() + " " + q.value(2).toString());
			ui.cb_object->addItem(q.value(3).toString() + ";" + q.value(4).toString() + ";" + q.value(5).toString());
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
	ui.tb_addGroup->setText("");
	ui.tb_addGroupNo->setText("");
	ui.tb_addName->setText("");
	ui.tb_addParagraph->setText("");
	ui.textEdit->setText("");
	ui.groupBox->setVisible(false);
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
	double rowheight = 15;
	double *colwidth = new double[4]{100,75,120,150};
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
	

	using namespace PoDoFo;
	auto filename = QFileDialog::getSaveFileName(this, lat("Wähle Speicherort aus"), "neues_document.pdf", tr("Portable Document Format (*.pdf)"), nullptr);
	PdfStreamedDocument document(filename.toStdString().c_str(), ePdfVersion_1_7);
	PdfPage* page;
	PdfPainter painter;
	PdfFont* pFont;
	page = document.CreatePage(PdfPage::CreateStandardPageSize(ePdfPageSize_A4));
	if (!page)
		PODOFO_RAISE_ERROR(ePdfError_InvalidHandle);
	painter.SetPage(page);
	pFont = document.CreateFont("Times");
	pFont->SetFontSize(7);
	painter.SetFont(pFont);
	painter.DrawText(56, page->GetPageSize().GetHeight() - 150, PdfString(std::wstring(first + L" "+strasse + L" " + plz + L" " + stadt).c_str()));
	PdfAcroForm *acrFrm = new PdfAcroForm(&document);
	PdfRect rect(56, 600, 250, 90);
	std::wstring mieter_address;
	if (this->ui.cb_tennant->currentText() == "FREI")
	{
		
		PdfTextField *tf = new PdfTextField(page, rect, acrFrm);
		tf->SetMultiLine(true);
		tf->SetMaxLen(255);
		tf->SetFieldName("tb_addresse");
		tf->SetText("TEST");
		acrFrm->SetNeedAppearances(true);
		
	}
	else {
		painter.GetFont()->SetFontSize(12);
		auto list = this->ui.cb_tennant->currentText().split(';');
		auto name = list[1];
		auto id = list[0];
		QSqlQuery q(ptr->db);
		q.prepare("SELECT id , strasse, plz, stadt FROM tbl_adresse WHERE pid=" + id + " ORDER BY ID DESC LIMIT 1");
		if (q.exec()) {
			auto test = q.value(1).toString().toStdWString();
			q.next();
			mieter_address = std::wstring(name.toStdWString() + L"\n" + q.value(1).toString().toStdWString() + L"\n" + q.value(2).toString().toStdWString() + L" " + q.value(3).toString().toStdWString());
			painter.DrawMultiLineText(rect, PdfString(std::wstring(name.toStdWString() + L"\n" + q.value(1).toString().toStdWString() + L"\n" + q.value(2).toString().toStdWString() + L" " + q.value(3).toString().toStdWString()).c_str()));
		}
	}
	pFont = document.CreateFont("Times");
	pFont->SetFontSize(10);
	painter.SetFont(pFont);
	auto cc = setting->value("Chef").toString();
	std::wstring chef = L"Geschäftsführer: " + setting->value("Chef").toString().toStdWString();
	painter.DrawText(400, 770,PdfString(setting->value("Firma","").toString().toStdWString().c_str()));
	painter.DrawText(400, 760, PdfString(chef.c_str()));
	painter.DrawText(400, 750, PdfString(strasse.c_str()));
	painter.DrawText(400, 740, PdfString(std::wstring(plz + L" " + stadt).c_str()));
	painter.DrawText(400, 730, PdfString(std::wstring(L"USt.-ID: " + setting->value("UstID", "").toString().toStdWString()).c_str()));
	painter.DrawText(400, 720, PdfString(std::wstring(L"Handelsregister Nr.: " + setting->value("Handelsregister", "").toString().toStdWString()).c_str()));
	painter.DrawText(400, 710, PdfString(std::wstring(L"Sachbearbeiter: " + setting->value("Vorname").toString().toStdWString() + L" " + setting->value("Nachname").toString().toStdWString()).c_str()));
	
	painter.DrawText(400, 700, PdfString(std::wstring(L"Datum: " + QLocale(QLocale::German).toString(QDate::currentDate()).toStdWString()).c_str()));

	pFont = document.CreateFont("Times-Bold",true,false);
	pFont->SetFontSize(10);
	painter.SetFont(pFont);
	painter.DrawText(50, 550, PdfString("Betreff: Ihr Mietvertrag"));
	pFont = document.CreateFont("Times", false, false);
	pFont->SetFontSize(10);
	painter.SetFont(pFont);
	PdfRect textrect(50, 100, 500, 430);
	QDate date = QDate::currentDate().addDays(14);
	
	//painter.DrawText(50, 530, PdfString(std::wstring(L"Anbei schicken wir Ihnen den Mietvertrag zu, bitte lesen Sie ihn sorgfältig durch").c_str()));
	std::wstring text = L"Anbei schicken wir Ihnen den Mietvertrag zu, bitte lesen Sie ihn genau durch und bei Fragen können Sie gerne uns fragen.\n"
		L"Bitte schicken Sie den Mietvertrag bis zum " + QLocale(QLocale::German).toString(date).toStdWString() + L" unterschrieben zurück.\n"
		L"wir wünschen Ihnen viel Vergnügen mit Ihrer neuen Wohnung.\n\n"
		L"Mit freundlichen Grüßen\n";
	painter.DrawMultiLineText(textrect, PdfString(text.c_str()));
	painter.FinishPage();

	PdfPage* vpage = document.CreatePage(PdfPage::CreateStandardPageSize(ePdfPageSize_A4));
	painter.SetPage(vpage);
	PdfFont* vFont = document.CreateFont("Courier-Bold", true, false);
	vFont->SetFontSize(18);
	painter.SetFont(vFont);
	PdfRect TOrect(50, 700, 500, 80);
	painter.DrawMultiLineText(TOrect, PdfString(L"Mietvertrag"), ePdfAlignment_Center);
	vFont->SetFontSize(12);
	PdfRect zwischenRect(50, 700, 500, 25);
	painter.DrawMultiLineText(zwischenRect, PdfString(L"zwischen"), ePdfAlignment_Center);
	PdfRect firmaRect(50, 620, 500, 84);
	std::wstring firmen_stempel = first + L"\n" + strasse + L"\n" + plz + L" " + stadt + L"\nvertreten durch:\n" + chef+L"\n\nund";
	painter.DrawMultiLineText(firmaRect, PdfString(firmen_stempel.c_str()), ePdfAlignment_Center);
	PdfRect mieterRect(180, 560, 250, 80);
	if (this->ui.cb_tennant->currentText() == "FREI") {
		
		PdfTextField *empf = new PdfTextField(vpage, mieterRect, &document);
		empf->SetMultiLine(true);
		empf->SetFieldName(PdfString(L"tb_Vertragspartner"));
	}
	else {
		painter.DrawMultiLineText(mieterRect,PdfString(mieter_address.c_str()),PoDoFo::ePdfAlignment_Center);
	}
	PdfRect fuerRect(50, 540, 500, 15);
	painter.DrawMultiLineText(fuerRect, PdfString(L"für das Mietobjekt"), ePdfAlignment_Center);
	PdfRect objectRect(180, 460, 250, 80);
	if (this->ui.cb_object->currentText() == "FREI") {
		
		PdfTextField *tb_obj = new PdfTextField(vpage,objectRect, &document);
		tb_obj->SetMultiLine(true);
		tb_obj->SetFieldName(PdfString(L"tb_object"));
		painter.DrawText(50, 450, PdfString(L"Mit den Eigenschaften (bei keinem Eintrag, existiert die Eigenschaft nicht!):"));
		//GRÖße
		painter.DrawText(50, 430, PdfString(L"Größe:"));
		PdfRect sizeRect(100, 430, 50, 12);
		PdfTextField *tb_size = new PdfTextField(vpage, sizeRect, &document);
		tb_size->SetFieldName(PdfString(L"tb_size"));
		//Zimmer
		painter.DrawText(155, 430, PdfString(L"Zimmer:"));
		PdfRect roomRect(220, 430, 50, 12);
		PdfTextField *tb_zimmer = new PdfTextField(vpage, roomRect, &document);
		tb_zimmer->SetFieldName(PdfString(L"tb_zimmer"));
		painter.DrawText(270, 430, PdfString(L"Balkon:"));
		PdfRect balkonRect(320, 430, 25, 12);
		PdfCheckBox *cb_balkon = new PdfCheckBox(vpage, balkonRect, &document);
		//cb_balkon->SetBackgroundColor(128, 128, 128);
		cb_balkon->SetFieldName("cb_balkon");
		//Dusche oder Badewanne
		painter.DrawText(50, 415, PdfString(L"Bad:"));
		PdfRect badRect(100, 415, 75, 12);
		PdfComboBox *cb_bad = new PdfComboBox(vpage, badRect, &document);
		cb_bad->InsertItem("badewanne", "Badewanne");
		cb_bad->InsertItem("dusche", "Dusche");
		cb_bad->InsertItem("keinBad", "Kein Bad");
		cb_bad->SetFieldName(PdfString(L"cb_bad"));
		//Sicherung
		painter.DrawText(50, 400, PdfString(L"Sicherungsautomat: "));
		PdfRect SichaRect(180, 400, 25, 12);
		PdfCheckBox *cb_sicherungsautomat = new PdfCheckBox(vpage, SichaRect, &document);
		cb_sicherungsautomat->SetFieldName(PdfString(L"cb_sicherungsautomat"));
		//Sicherungswert
		painter.DrawText(215, 400, PdfString(L"Absicherung [A]:"));
		PdfRect swertRect(350, 400, 50, 12);
		PdfTextField *tb_fusevalue = new PdfTextField(vpage, swertRect, &document);
		tb_fusevalue->SetFieldName("tb_fuse");
	}
	else {
		auto obj = this->ui.cb_object->currentText().split(';');
		QSqlQuery q(ptr->db);
		q.prepare("SELECT * FROM tbl_object WHERE id=" + obj[0]);
		q.exec();
		q.next();
		std::wstring mietobjekt = q.value(2).toString().toStdWString() + L"\n" + q.value(3).toString().toStdWString() + L" " + q.value(4).toString().toStdWString() + L"\nEtage:" + q.value(5).toString().toStdWString();
		painter.DrawMultiLineText(objectRect, PdfString(mietobjekt.c_str()));
		QSqlQuery q2(ptr->db);
		auto oid = q.value(0).toString();
		q2.prepare("SELECT * FROM tbl_ausstattung WHERE object_id=" + q.value(0).toString()+" AND ID= (SELECT MAX(ID) FROM tbl_ausstattung)");
		int res = q2.exec();
		q2.next();
		auto y = q2.executedQuery();
		PdfRect equipRect(50, 50, 500, 300);
		std::wstring text = L"Größe: " + q.value(7).toString().toStdWString()+L" Zimmer: "+q.value(8).toString().toStdWString()+L" Baujahr: "+q.value(6).toString().toStdWString()+L'\n';
		text += L"Balkon: " + q2.value(8).toString().toStdWString() + L" Fußboden: " + q2.value(3).toString().toStdWString() + L" Bad: " + q2.value(6).toString().toStdWString() + L'\n';
		text += L"Sicherungsart: " + q2.value(4).toString().toStdWString() + L" Absicherungswert: " + q2.value(5).toString().toStdWString()+L'\n';
		text += L"Heizungsmethode: " + q2.value(11).toString().toStdWString() + L" Kabelanschluss: " + q2.value(9).toString().toStdWString() + L" FTTH: " + q2.value(10).toString().toStdWString() + L'\n';
		text += L"Weiteres: " + q2.value(12).toString().toStdWString();
		//painter.DrawMultiLineText(equipRect, PdfString(text.c_str()));
		PdfTable table(4, 6);
		table.SetColumnWidths(colwidth);
		table.SetRowHeight(rowheight);
		PdfSimpleTableModel tbl(4, 6);
		tbl.SetFont(vFont);
		tbl.SetForegroundColor(PdfColor(0, 0, 0));
		tbl.SetAlignment(PoDoFo::ePdfVerticalAlignment_Center);
		tbl.SetText(0, 0, PdfString(L"Größe:"));
		tbl.SetText(1, 0, PdfString(q.value(7).toString().toStdWString().c_str()));
		tbl.SetText(2, 0, PdfString(L"Zimmer:"));
		auto temp = q.value(8).toString().toStdString();
		tbl.SetText(3, 0, PdfString(temp));
		tbl.SetText(0, 1, PdfString(L"Baujahr"));
		tbl.SetText(1, 1, PdfString(q.value(6).toString().toStdWString().c_str()));
		tbl.SetText(2, 1, PdfString(L"Balkon:"));
		tbl.SetText(3, 1, PdfString(q2.value(8).toString().toStdWString().c_str()));
		tbl.SetText(0, 2, PdfString(L"Fußboden:"));
		tbl.SetText(1, 2, PdfString(q2.value(3).toString().toStdWString().c_str()));
		tbl.SetText(2, 2, PdfString(L"Bad:"));
		tbl.SetText(3, 2, PdfString(q2.value(6).toString().toStdWString().c_str()));
		tbl.SetText(0, 3, PdfString(L"Sicherungsart:"));
		tbl.SetText(1, 3, PdfString(q2.value(4).toString().toStdWString().c_str()));
		tbl.SetText(2, 3, PdfString(L"Absicherungswert:"));
		tbl.SetText(3, 3, PdfString(q2.value(5).toString().toStdWString().c_str()));
		tbl.SetText(0, 4, PdfString(L"Heizungsart:"));
		tbl.SetText(1, 4, PdfString(q2.value(11).toString().toStdWString().c_str()));
		tbl.SetText(2, 4, PdfString(L"Kabelanschluss:"));
		tbl.SetText(3, 4, PdfString(q2.value(9).toString().toStdWString().c_str()));
		tbl.SetText(0, 5, PdfString(L"FTTH"));
		tbl.SetText(1, 5, PdfString(q2.value(10).toString().toStdWString().c_str()));
		//tbl.SetText(2, 5, PdfString(L"Weiteres:"));
		//tbl.SetText(3, 5, PdfString(q2.value(12).toString().toStdWString().c_str()));
		tbl.SetBorderEnabled(true);
		table.SetModel(&tbl);
		table.Draw(50, 430, &painter);
		PdfRect weiteresRect(50, 50, 400, 270);
		painter.DrawMultiLineText(weiteresRect, PdfString(std::wstring(L"Weiteres: " + q2.value(12).toString().toStdWString()).c_str()));

	}
	painter.FinishPage();
	PdfPage* cPage = document.CreatePage(PdfPage::CreateStandardPageSize(PoDoFo::ePdfPageSize_A4));
	painter.SetPage(cPage);
	{
		PdfFont* abschnittFont = document.CreateFont("Courier-Bold");
		abschnittFont->SetFontSize(12);
		int x = 780;
		uint xb = 50;
		uint fontSize = 13; //actual fontsize+1;!!
		uint sizeWidth = 500;
		QString currentGroup;
		for (uint i = 0; i < ui.tbl_paragraph->rowCount(); i++) {
			if (ui.tbl_paragraph->item(i, 1)->text() != currentGroup) {
				painter.SetFont(abschnittFont);
				currentGroup = ui.tbl_paragraph->item(i, 1)->text();
				QString groupNo = ui.tbl_paragraph->item(i, 2)->text();
				PdfRect abschnittRect(xb, x, sizeWidth, fontSize);
				std::wstring text = L"Abschnitt: " + groupNo.toStdWString() + L": " + currentGroup.toStdWString();
				painter.DrawMultiLineText(abschnittRect, PdfString(text.c_str()),ePdfAlignment_Center);
				x = x - fontSize;
			}
			painter.SetFont(vFont);
			std::wstring text = L"§" + ui.tbl_paragraph->item(i, 2)->text().toStdWString() + L'.' + ui.tbl_paragraph->item(i, 3)->text().toStdWString() + L": " + ui.tbl_paragraph->item(i, 0)->text().toStdWString();
			painter.DrawText(xb, x, PdfString(text.c_str()));
			x = x - fontSize;
			//68 Zeichen!!
			auto line = ui.tbl_paragraph->item(i, 4)->text().toStdWString();
			if (line.length() > 68) {
				auto count = (line.length() / 68) + 1;
				PdfRect contentRect(xb, x - (count*fontSize), sizeWidth, count*fontSize);
				painter.DrawMultiLineText(contentRect, PdfString(line.c_str()));
				x = x - ((count)*fontSize);
			}
			else
				painter.DrawText(xb, x, PdfString(ui.tbl_paragraph->item(i, 4)->text().toStdWString().c_str()));
			x = x - fontSize;
			if (x < 50) {
				this->newPage(painter, document);
				x = 780;
			}
		}
		//delete abschnittFont;
	}
	painter.FinishPage();
	document.GetInfo()->SetCreator(PdfString(std::string("QVerwaltung - Hausverwaltungssoftware")));
	document.GetInfo()->SetAuthor(PdfString(first.c_str()));
	document.GetInfo()->SetTitle(PdfString(std::string("Mietvertrag")));
	document.Close();
	setting->endGroup();
}

void QV_Mietvertrag::newPage(PoDoFo::PdfPainter & painter, PoDoFo::PdfStreamedDocument & document)
{
	using namespace PoDoFo;
	PdfPage* nPage = document.CreatePage(PdfPage::CreateStandardPageSize(ePdfPageSize_A4));
	painter.FinishPage();
	painter.SetPage(nPage);
}


void QV_Mietvertrag::showPDF() {
	(new QV_Viewer())->show();
}