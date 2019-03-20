#pragma once
#include <service.h>
#include <qwidget.h>
#include <Produs.h>
#include <qlistwidget.h>
#include <qboxlayout.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlabel.h>
#include "Observer.h"
#include <vector>
#include <qpainter.h>
#include "listModel.h"

class ProdGUI: public QWidget {
private:
	service & serv;
	QListWidget*  lis;
	ListModel* listModel = new ListModel;
	QPushButton* bAdd;
	QLineEdit* txtNume;
	QLineEdit* txtTip;
	QLineEdit* txtProduc;
	QLineEdit* txtPret;
	QPushButton* bSortNumeTip;
	QPushButton* bSortNume;
	QPushButton* bSortPret;
	QPushButton* bUndo;
	QPushButton* bMod;
	QPushButton* bDel;
	QPushButton* bCos;
	QPushButton* bDes;
	void initGUICmps();
	void connectSignalsSlots();
	void reloadList(const std::vector<Produs>& prod);
	void addProdus();
	void delProdus();
	void modProdus();
	void undo();
public:
	ProdGUI(service& serv) :serv{ serv } {
		initGUICmps();
		connectSignalsSlots();
		reloadList(serv.getAllel());
	}

};
class COSGUI : public QWidget,public Observer {
private:
	service & serv;
	QLineEdit*number = new QLineEdit;
	QListWidget* CosView = new QListWidget;
	QListWidget* ProdView = new QListWidget;
	QPushButton* bAddProd = new QPushButton("Adauga Produs");
	QPushButton* bRandProd = new QPushButton("Adauga Random");
	QPushButton* bEmptyCos = new QPushButton("Goloste Cos");
	void initGUI();
	void loadCos();
	void loadProd();
	void connectSignal();
	void addProd();
public:
	COSGUI(service & serv) :serv{ serv } {}
	void start();
	void update() override {
		loadCos();
		loadProd();
	}
};
class COSPaint : public QWidget, public Observer {
private:
	service & serv;
	void initGUI();
	
	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };
		auto co = serv.toatedinCos();
		int x = 0;
		for (const auto& q : co) {

			p.drawRect(x * 50, 0, 40, q.getprice()*10);
			x++;
		}
	}
public:
	COSPaint(service & serv) :serv{ serv } {}
	void start() {
		
		repaint();
	}
	void update() override {
		repaint();
	}
};