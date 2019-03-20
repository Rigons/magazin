#pragma once
#include <QAbstractListModel>
#include <vector>
#include <qdebug.h>
#include "service.h"
using namespace std;
class ListModel : public QAbstractListModel
{
	vector<Produs> discs;

public:

	ListModel() {}

	ListModel(vector<Produs> discs) : discs{ discs } {}

	int rowCount(const QModelIndex & parent = QModelIndex()) const override {
		return discs.size();
	}

	QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override
	{
		if (role == Qt::DisplayRole) {
			qDebug() << "get row:" << index.row();
			auto nume = discs[index.row()].getnume();
			return QString::fromStdString(nume);
		}
		if (role == Qt::UserRole) {
			auto tip = discs[index.row()].gettip();
			auto prod = discs[index.row()].getproducator();
			auto strin = tip+" " + prod;
			return QString::fromStdString(strin);
		}

		return QVariant{};
	}

	Produs getDisc(const QModelIndex & index) {
		return discs[index.row()];
	}

	void setDiscs(const vector<Produs>& discs) {
		this->discs = discs;
	}
};