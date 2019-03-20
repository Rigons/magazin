#pragma once
#include "Repo.h"
#include "Produs.h"
#include <algorithm>
#include "validator.h"
#include "CosProdus.h"
#include <memory>
#include "undo.h"

class service
{
private:
	GenRepo& repo;
	CosProdus cos;
	std::vector<unique_ptr<UndoAction>> UndoActions;
	validator& val;
public:
	service(GenRepo& repo, validator& val) noexcept : repo{ repo }, val{ val } {}

	service(const service& ot) = delete;
	void operator=(const service& ot) = delete;

	void addel(const string& nume, const string& tip,const string& producator,const double price);

	void modifyel(const string& onume, const string& otip, const string& oproducator, const string& nume, const string& tip, const string& producator, const double& pret);

	void removeel(const string& nume, const string& tip,const string& producator);

	vector<Produs> sortProduse(bool(*Cmp)(const Produs& p1, const Produs& p2)) noexcept;

	vector<Produs> filterProduse(bool(*Cmp)(const Produs& p1,const Produs& p2), const Produs& b2) ;

	const vector<Produs>& getAllel()const noexcept {
		return repo.getAll();
	}
	const std::vector<Produs>& addtoCos(const std::string& nume, const std::string& tip, const std::string& producator);
	
	const std::vector<Produs>& addRandom(int cate);

	const std::vector<Produs>& golesteCos()noexcept;

	const std::vector<Produs>& toatedinCos()noexcept;

	void undo();

	const Produs& find(const string& nume, const string& tip, const string& producator) {
		Produs p{ nume,tip,producator,0 };
		val.validateProdus(p);
		return repo.find(nume, tip, producator);
	}

	const double pretCos()noexcept;

	void exportCosCVS(std::string FName) const;
	
	void exportCosHTML(std::string FName) const;
	void addObs(Observer *o)
	{
		cos.addObserver(o);
	}
};
void testservice();


