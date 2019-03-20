#include "service.h"
#include <functional>
#include <algorithm>
#include <fstream>
#include "export.h"
#include <assert.h>
using namespace std;


void service::addel(const string& nume, const string& tip,const string& producator, const double pret) {
	Produs p{ nume,tip,producator,pret };
	val.validateProdus(p);
	repo.add(p);
	UndoActions.push_back(std::make_unique<UndoAdd>(repo, p));
}

void service::modifyel(const string& onume, const string& otip, const string& oproducator,const string& nume,const string& tip, const string& producator,const double& pret) {
	Produs oP=repo.find(onume,otip,oproducator);
	Produs P{ nume,tip,producator,pret };

	val.validateProdus(P);
	repo.modify(oP, P);

	UndoActions.push_back(std::make_unique<UndoModify>(repo, oP,P));
}
void service::removeel(const string& nume, const string& tip, const string& producator) {
	Produs p{ nume,tip,producator,0};
	val.validateProdus(p);
	repo.remove(p);
	UndoActions.push_back(std::make_unique<UndoRemove>(repo, p));
}
vector<Produs> service::sortProduse(bool(*Cmp)(const Produs& p1, const Produs& p2)) noexcept {
	vector<Produs> ve;
	ve = repo.getAll();
	sort(ve.begin(), ve.end(), Cmp);
	return ve;
}
vector<Produs> service::filterProduse(bool(*Cmp)(const Produs& p1,const Produs& p2), const Produs& p2)  {
	if (*Cmp == nullptr)
		throw RepoException("Pointer null");
	vector<Produs> ve;
	ve.clear();
	auto& all = repo.getAll();
	std::copy_if(all.begin(), all.end(), back_inserter(ve), [=](const Produs&p)noexcept {return Cmp(p, p2); });
	return ve;
}
const std::vector<Produs>& service::addtoCos(const std::string& nume, const std::string& tip, const std::string& producator) {
	const Produs& p = repo.find(nume, tip, producator);
	cos.adauga(p);
	return cos.lista();
}

const std::vector<Produs>& service::addRandom(int cate) {
	cos.umple(cate, repo.getAll());
	return cos.lista();
}

const std::vector<Produs>& service::golesteCos() noexcept{
	cos.goleste();
	return cos.lista();
}

const std::vector<Produs>& service::toatedinCos() noexcept{
	return cos.lista();
}

const double service::pretCos()noexcept {
	auto cosu = cos.lista();
	double sum = 0;
	for (auto& i : cosu) {
		sum =sum + i.getprice();
	}
	return sum;
}

void service::exportCosCVS(std::string FName) const {
	exportTOCVS(FName, cos.lista());
}

void service::exportCosHTML(std::string FName) const {
	exportTOHTML(FName, cos.lista());
}

void service::undo() {
	if (UndoActions.empty()) {
		throw RepoException("Nu mai exista operatii ");
	}
	UndoActions.back()->doUndo();
	UndoActions.pop_back();
}

void testCos() {
	std::ofstream out("testProd.txt", std::ios::trunc);
	out.close();
	FileRepo repo{ "testProd.txt" };
	//Repodic repo;
	validator val;
	service serv{ repo,val };
	serv.addel("a", "a", "a", 7);
	serv.addel("b", "b", "b", 10);
	serv.addel("a", "c", "c", 9);
	serv.addtoCos("a", "a", "a");
	serv.exportCosCVS("testla");
	serv.exportCosHTML("testfa");
	auto v = serv.toatedinCos();
	assert(v.size() == 1);
	serv.addRandom(4);
	v = serv.toatedinCos();
	assert(v.size() == 4);
	auto const cost = serv.pretCos();
	assert(cost == 33);
	serv.golesteCos();
	v = serv.toatedinCos();
	assert(v.size() == 0);
}

void testadd() {
	std::ofstream out("testProd.txt", std::ios::trunc);
	out.close();
	FileRepo repo{ "testProd.txt" };
	//Repodic repo;
	validator val;
	service serv{repo,val};
	serv.addel("a", "a", "a", 6);
	auto v = serv.getAllel();
	assert(serv.getAllel().size() == 1);
	try {
		serv.addel("", "", "", -1);
		assert(false);
	}
	catch (ValidException& ) {
		//wr.getMessage();
		assert(true);
	}
	try {
		serv.addel("a", "a", "a", 0);
		assert(false);}
	catch (RepoException&) {
		//wr.getMesage();
		assert(true);
	}

	serv.modifyel("a", "a", "a", "b", "b", "b", 3);
	try {
		serv.modifyel("a", "a", "a", "b", "b", "b", 3);
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
	try {
		serv.modifyel("", "", "", "b", "b", "b", 3);
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}

	serv.removeel("b", "b", "b");
	try {
		serv.removeel("", "", "");
		assert(false);
	}
	catch (ValidException&) {
		assert(true);
	}
	try {
		serv.removeel("a", "a", "a");
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
}
void testundo() {
	std::ofstream out("testProd.txt", std::ios::trunc);
	out.close();
	FileRepo repo{ "testProd.txt" };
	validator val;
	service serv{ repo,val };
	try {
		serv.undo();
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
	serv.addel("a", "a", "a", 7);
	serv.addel("b", "b", "b", 10);
	serv.addel("a", "c", "c", 9);
	serv.undo();
	serv.removeel("b", "b", "b");
	serv.undo();
	serv.modifyel("b", "b", "b", "a", "c", "c", 9);
	serv.undo();
}

void testsort() {
	std::ofstream out("testProd.txt", std::ios::trunc);
	out.close();
	FileRepo repo{ "testProd.txt" };
	//Repodic repo;
	validator val;
	service serv{ repo,val };
	serv.addel("a", "a", "a", 7);
	serv.addel("b", "b", "b", 10);
	serv.addel("a", "c", "c", 9);
	vector<Produs> v = serv.sortProduse(Produs::cmpnumetip);
	auto p = v[1];
	assert(p.gettip() == "c");
	v = serv.sortProduse(Produs::cmpnume);
	p = v[2];
	assert(p.getnume() == "b");
	v = serv.sortProduse(Produs::cmpprice);
	p = v[1];
	assert(p.getprice() == 9);
}

void testfilter() {
	std::ofstream out("testProd.txt", std::ios::trunc);
	out.close();
	FileRepo repo{ "testProd.txt" };
	//Repodic repo;
	validator val;
	service serv{ repo,val };
	serv.addel("a", "a", "a", 7);
	serv.addel("b", "b", "b", 10);
	serv.addel("a", "c", "c", 9);
	Produs p{ "b","","c",9 };
	auto v = serv.filterProduse(Produs::filnume,p);

	assert(v.size() == 1);

	v = serv.filterProduse(Produs::filproducator, p);
	assert(v.size() == 1);

	v = serv.filterProduse(Produs::filprice, p);
	assert(v.size() == 2);
}

void testservice() {

	testadd();
	testsort();
	testfilter();
	testCos();
	testundo();
}