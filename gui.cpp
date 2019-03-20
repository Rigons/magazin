#include "gui.h"
#include "Produs.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <string>
#include <qlistwidget.h>
#include <algorithm>


void ProdGUI::initGUICmps() {
	QHBoxLayout* ly = new QHBoxLayout;
	setLayout(ly);
	
	QWidget* widFunct = new QWidget;
	QFormLayout* formFunct = new QFormLayout;
	widFunct->setLayout(formFunct);
	formFunct->addRow(new QLabel("Produs:"));
	txtNume = new QLineEdit;
	formFunct->addRow(new QLabel("Nume:"), txtNume);
	txtTip = new QLineEdit;
	formFunct->addRow(new QLabel("Tip:"), txtTip);
	txtPret = new QLineEdit;
	formFunct->addRow(new QLabel("Pret:"), txtPret);
	txtProduc = new QLineEdit;
	formFunct->addRow(new QLabel("Producator:"), txtProduc);

	bAdd = new QPushButton("Adauga Produs");
	formFunct->addWidget(bAdd);
	bMod = new QPushButton("Modifica Produs");
	formFunct->addWidget(bMod);
	bDel = new QPushButton("Sterge Produs");
	formFunct->addWidget(bDel);
	bUndo = new QPushButton("Undo");
	formFunct->addWidget(bUndo);
	bCos =new QPushButton("Cos");
	formFunct->addWidget(bCos);
	bDes = new QPushButton("Desen Cos");
	formFunct->addWidget(bDes);
	ly->addWidget(widFunct);

	QWidget* widList = new QWidget;
	QVBoxLayout* vl = new QVBoxLayout;
	widList->setLayout(vl);
	lis = new QListWidget;
	vl->addWidget(lis);
	QWidget* widSort = new QWidget;
	QVBoxLayout* lsort = new QVBoxLayout;
	widSort->setLayout(lsort);
	bSortNumeTip = new QPushButton("Sortare dupa Nume+tip");
	lsort->addWidget(bSortNumeTip);
	bSortNume = new QPushButton("Sortare dupa Nume");
	lsort->addWidget(bSortNume);
	bSortPret = new QPushButton("Sortare dupa Pret");
	lsort->addWidget(bSortPret);
	vl->addWidget(widSort);
	ly->addWidget(widList);
}
void ProdGUI::connectSignalsSlots() {
	QObject::connect(bSortNumeTip, &QPushButton::clicked, [&]() {
		reloadList(serv.sortProduse(Produs::cmpnumetip));
	});

	QObject::connect(bSortNume, &QPushButton::clicked, [&]() {
		reloadList(serv.sortProduse(Produs::cmpnume));
	});
	QObject::connect(bSortPret, &QPushButton::clicked, [&]() {
		reloadList(serv.sortProduse(Produs::cmpprice));
	});

	QObject::connect(lis, &QListWidget::itemSelectionChanged, [&]() {
		if (lis->selectedItems().isEmpty()) {
			txtNume->setText("");
			txtTip->setText("");
			txtPret->setText("");
			txtProduc->setText("");
			return;
		}
		QListWidgetItem* selItem = lis->selectedItems().at(0);
		QString nume = selItem->text();
		txtNume->setText(nume);
		QString Qst= selItem->data(Qt::UserRole).toString();
		std::string prod = Qst.toStdString();
		std::size_t found = prod.find(" ");
		string tip = prod.substr(0, found);
		prod.erase(0, found + 1);
		QString Qtip = QString::fromStdString(tip);
		QString Qprod = QString::fromStdString(prod);
		txtTip->setText(Qtip);
		txtProduc->setText(Qprod);
		try {
			//cautam Pet
			Produs p = serv.find(nume.toStdString(), tip,prod);
			txtPret->setText(QString::number(p.getprice()));
		}
		catch (RepoException& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMesage()));
		}
		catch (ValidException& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
		}
	});
	QObject::connect(bAdd, &QPushButton::clicked, this, &ProdGUI::addProdus);
	QObject::connect(bDel, &QPushButton::clicked, this, &ProdGUI::delProdus);
	QObject::connect(bMod, &QPushButton::clicked, this, &ProdGUI::modProdus);
	QObject::connect(bUndo, &QPushButton::clicked, this, &ProdGUI::undo);
	QObject::connect(bCos, &QPushButton::clicked, [&]() {
		COSGUI*secWind = new COSGUI(serv);
		//serv.addObj(secWind);
		serv.addObs(secWind);
		secWind->start();
		secWind->show();
	});
	QObject::connect(bDes,&QPushButton::clicked, [&]() {
		COSPaint*thirWind = new COSPaint(serv);
		//serv.addObj(secWind);
		serv.addObs(thirWind);
		thirWind->start();
		thirWind->show();
	});
}
void ProdGUI::delProdus() {
			if (lis->selectedItems().isEmpty()) {
				txtNume->setText("");
				txtTip->setText("");
				txtPret->setText("");
				txtProduc->setText("");
				return;
			}
			QListWidgetItem* selItem = lis->selectedItems().at(0);
			QString nume = selItem->text();
			QString Qst = selItem->data(Qt::UserRole).toString();
			std::string prod = Qst.toStdString();
			std::size_t found = prod.find(" ");
			string tip = prod.substr(0, found);
			prod.erase(0, found + 1);
			try {
				//cautam Pet
				serv.removeel(nume.toStdString(),tip,prod);
				reloadList(serv.getAllel());

			}
			catch (RepoException& ex) {
				QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMesage()));
			}
			catch (ValidException& ex) {
				QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
			}
}
void ProdGUI::modProdus() {
		if (lis->selectedItems().isEmpty()) {
			txtNume->setText("");
			txtTip->setText("");
			txtPret->setText("");
			txtProduc->setText("");
			return;
		}
		QListWidgetItem* selItem = lis->selectedItems().at(0);
		QString nume = selItem->text();
		QString Qst = selItem->data(Qt::UserRole).toString();
		std::string prod = Qst.toStdString();
		std::size_t found = prod.find(" ");
		string tip = prod.substr(0, found);
		prod.erase(0, found + 1);
		try {
			//cautam Pet
			serv.modifyel(nume.toStdString(), tip, prod, txtNume->text().toStdString(), txtTip->text().toStdString(), txtProduc->text().toStdString(), txtPret->text().toDouble());
			reloadList(serv.getAllel());

		}
		catch (RepoException& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMesage()));
		}
		catch (ValidException& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
		}
}
void ProdGUI::addProdus() {
	try {
		serv.addel(txtNume->text().toStdString(), txtTip->text().toStdString(), txtProduc->text().toStdString(), txtPret->text().toDouble());
		reloadList(serv.getAllel());
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMesage()));
	}
	catch (ValidException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
	}
}
void ProdGUI::undo() {
		try {

			serv.undo();
			reloadList(serv.getAllel());
		}
		catch (RepoException& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMesage()));
		}
		catch (ValidException& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
		}
	
}
void ProdGUI::reloadList(const std::vector<Produs>& prod) {
	Produs l{ "","","",5 };
	auto colo = serv.filterProduse(Produs::filprice,l);
	lis->clear();
	for (const auto& p : prod) {
		QString pret = QString::number(p.getprice());
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(p.getnume()), lis);
		std::string l = p.gettip() + " " + p.getproducator();
		item->setData(Qt::UserRole, QString::fromStdString(l));
		if (std::find(colo.cbegin(), colo.cend(), p) == colo.end()) {
			item->setBackground(QBrush{ QColor{Qt::blue} , Qt::CrossPattern });
			item->setBackgroundColor(QColor{ Qt::blue });
		}
	}

	listModel->setDiscs(prod);
}
void  COSGUI::initGUI(){

	QVBoxLayout* GL = new QVBoxLayout;
	this->setLayout(GL);
	QHBoxLayout* VL = new QHBoxLayout;
	QWidget* WV = new QWidget;
	WV->setLayout(VL);
	VL->addWidget(ProdView);
	VL->addWidget(CosView);
	GL->addWidget(WV);
	QVBoxLayout* AL = new QVBoxLayout;
	QWidget* WA = new QWidget;
	WA->setLayout(AL);
	AL->addWidget(bRandProd);
	AL->addWidget(number);
	AL->addWidget(bAddProd);
	AL->addWidget(bEmptyCos);
	GL->addWidget(WA);
}
void COSGUI::start() {
	initGUI();
	connectSignal();
	loadProd();
	loadCos();
}
void COSGUI::loadProd() {
	ProdView->clear();
	for (const auto & p : serv.getAllel()) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(p.getnume()), ProdView);
		std::string l = p.gettip() + " " + p.getproducator();
		item->setData(Qt::UserRole, QString::fromStdString(l));
	}
}
void COSGUI::loadCos() {
	CosView->clear();
	for (const auto & p : serv.toatedinCos()) {
		CosView->addItem(QString::fromStdString(p.getnume()));
	}
}
void COSGUI::connectSignal() {
	QObject::connect(bAddProd, &QPushButton::clicked, this, &COSGUI::addProd);
	QObject::connect(bEmptyCos, &QPushButton::clicked, [&]() {
		serv.golesteCos();
		loadCos();
	});
	QObject::connect(bRandProd, &QPushButton::clicked, [&]() { 
		try {
			string l = number->text().toStdString();
			if (l == "")
			{
				return;
			}
			int i = std::stoi(l);
			serv.addRandom(i);
			loadCos();
		}
		catch (RepoException& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMesage()));
		}
		catch (ValidException& ex) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
		}
	});
}
void COSGUI::addProd() {
	QListWidgetItem* selItem = ProdView->selectedItems().at(0);
	QString nume = selItem->text();
	QString Qst = selItem->data(Qt::UserRole).toString();
	std::string prod = Qst.toStdString();
	std::size_t found = prod.find(" ");
	string tip = prod.substr(0, found);
	prod.erase(0, found + 1);
	try {
		//cautam Pet
		serv.addtoCos(nume.toStdString(), tip, prod);
		loadCos();

	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMesage()));
	}
	catch (ValidException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
	}
}
void COSPaint::initGUI() {

}