#include "Repo.h"
#include "exceptii.h"
#include <string>
#include <assert.h>
#include <vector>
#include <algorithm>
#include <fstream>

void Repo::add(const Produs& el) {
	auto found = std::find_if(v.begin(), v.end(), [el](const Produs& pp) {
		return pp.getnume() == el.getnume() && pp.gettip() == el.gettip() && pp.getproducator() == el.getproducator();
	});
	if (found != v.end())
		throw RepoException("Elemnt deja introdus");
	v.push_back(el);
}
/*
int Repo::getpoz(const Produs& el) {
	for (unsigned i = 0; i < v.size(); i++) {
		if (v[i] == el)
			return i;
	}
	return -1;
}*/
void Repo::remove(const Produs& el) {
	auto found = std::find_if(v.begin(), v.end(), [el](const Produs& pp) {
		return pp.getnume() == el.getnume() && pp.gettip() == el.gettip() && pp.getproducator() == el.getproducator();
	});
	if (found == v.end())
		throw RepoException("Elementul nu exista.");
	auto vvvv = v.erase(found);
}
void Repo::modify(const Produs& oel, const Produs& el) {
	auto found = std::find_if(v.begin(), v.end(), [oel](const Produs& pp) {
		return pp.getnume() == oel.getnume() && pp.gettip() == oel.gettip() && pp.getproducator() == oel.getproducator();
	});
	auto o = v.end();
	if (found == v.end()) {
		throw RepoException("Elementul nu exista.");
	}
	auto l = found - v.begin();
	v[l] = el;
}
void FileRepo::loadFromFile() {
	std::ifstream in(Fname);
	if (!in.is_open()) {
		throw RepoException("Unable to open file: " + Fname);
	}
	while (!in.eof())
	{
		std::string name;
		in >> name;
		std::string tip;
		in >> tip;
		std::string prod;
		in >> prod;
		double pret;
		in >> pret;
		if (in.eof()) {
			break;
		}
		Produs p{ name.c_str(),tip.c_str(),prod.c_str(),pret };
		Repo::add(p);
	}
	in.close();
}
void FileRepo::writeToFile() {
	std::ofstream out(Fname);
	if (!out.is_open()) {
		std::string msg("Unable to open file: " + Fname);
		throw RepoException(msg);
	}
	for (auto& p : getAll()) {
		out << p.getnume();
		out << endl;
		out << p.gettip();
		out << endl;
		out << p.getproducator();
		out << endl;
		out << p.getprice();
		out << std::endl;
	}
	out.close();
}
void Repodic::add(const Produs&el) {
	const float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	std::string key = el.getnume()+" " + el.gettip()+" " + el.getproducator();
	auto it = m.find(key);
	if (it != m.end()|| x < p)
		throw RepoException("Element deja existent sau random mai mic ca p");
	auto l = m.insert(std::pair<string, Produs>(key, el));
}
const Produs&  Repodic::find(std::string nume, std::string tip, std::string producator) {
	std::string key = nume + " " + tip + " " + producator;
	auto it = m.find(key);
	if (it == m.end())
		throw RepoException("Element inexistent");
	return m.at(key);

}
void  Repodic::remove(const Produs& el) {
	std::string key = el.getnume() + " " + el.gettip() + " " + el.getproducator();
	auto it = m.find(key);
	if (it == m.end())
		throw RepoException("Element inexitent");
	auto l = m.erase(it);
}
void  Repodic::modify(const Produs& oel, const Produs& el) {
	std::string key1 = oel.getnume() + " " + oel.gettip() + " " + oel.getproducator();
	auto it = m.find(key1);
	if (it == m.end())
		throw RepoException("Element inexitent");
	auto l = m.erase(it);
	std::string key2 = el.getnume() + " " + el.gettip()+" " + el.getproducator();
	auto it2 = m.find(key2);
	if (it2 != m.end())
		throw RepoException("Element existent");
	auto k=m.insert(std::pair<string, Produs>(key2, el));
}
const vector<Produs>&  Repodic::getAll() {
	for (auto& i : m) {
		auto el = std::get<1>(i);
		v.push_back(el);
	}
	return v;
}
void testRepo() {
	//testMAP();
	Repo repo;
	Produs el{ "tra","fa","fa",5 };
	try {
		auto oel = repo.find("tra", "fa", "fa");
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
	repo.add(el);
	auto oel = repo.find("tra", "fa", "fa");
	assert(el == oel);
	try{
		FileRepo repF{ "testPets.txt" };
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
}