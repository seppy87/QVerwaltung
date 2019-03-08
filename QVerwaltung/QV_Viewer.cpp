#include "QV_Viewer.h"
#include<qlabel.h>
#include<qboxlayout.h>
#include<qprintdialog.h>
#include<qprinter.h>
#include<qpainter.h>

QV_Viewer::QV_Viewer(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->doc = Poppler::Document::load("neues_document.pdf");
	Poppler::Page* page = doc->page(0);
	QImage img = page->renderToImage(500, 500);
	QLabel* imglabel = new QLabel();
	imglabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	imglabel->setScaledContents(true);
	imglabel->setVisible(true);
	imglabel->setPixmap(QPixmap::fromImage(img));
	imglabel->resize(imglabel->pixmap()->size());
	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(imglabel);
	this->ui.sa_pdf->setLayout(layout);
	connect(ui.btn_print, &QPushButton::clicked, this, &QV_Viewer::print);
}

QV_Viewer::~QV_Viewer()
{
}


void QV_Viewer::print() {
	QPrinter printer;
	QPrintDialog* dlg = new QPrintDialog(&printer, 0);
	if (dlg->exec() == QDialog::Accepted) {
		QImage* img = new QImage();
		*img = doc->page(0)->renderToImage(500, 500);
		printer.setPageSize(QPagedPaintDevice::A4);
		printer.setPaperSize(QPrinter::A4);
		printer.setFullPage(true);
		QPainter *painter = new QPainter(&printer);
		double xscale = printer.pageRect().width() / double(img->width());
		double yscale = printer.pageRect().height() / double(img->height());
		double scale = qMin(xscale, yscale);
		painter->translate(printer.paperRect().x() + printer.pageRect().width() / 2, printer.paperRect().y() + printer.pageRect().height() / 2);
		painter->scale(scale, scale);
		painter->translate(-img->width() / 2, -img->height() / 2);
		painter->drawImage(QPoint(0, 0), *img);
		painter->end();
		auto x = printer.printerState();
	}
}