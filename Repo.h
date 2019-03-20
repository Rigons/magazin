#pragma once
#include <vector>
#include <algorithm>
#include "Produs.h"
#include "exceptii.h"
#include <string>
#include <assert.h>
#include <map>
using namespace std;

class GenRepo {
public:
		virtual ~GenRepo()=default;
		virtual void add(const Produs&el)=0;
		virtual const Produs& find(std::string nume, std::string tip, std::string producator)=0;
		virtual void remove(const Produs& el)=0;
		virtual const vector<Produs>& getAll()=0;
		virtual void modify(const Produs& oel, const Produs& el)=0;
};

class Repodic:public GenRepo {
private:
	std::map<string,Produs> m;
	std::vector<Produs> v;
	double p=0.5;
public:
	Repodic() = default ;
	Repodic(const Repodic& ot) = delete;
	void add(const Produs&el) override;
	const Produs& find(std::string nume, std::string tip, std::string producator)override;
	void remove(const Produs& el)override;
	void modify(const Produs& oel, const Produs& el) override;
	const vector<Produs>& getAll() override;
};

class Repo :public GenRepo
{
private:
	//Mylisttemp<ElemT> elem;
	vector<Produs> v;
public:
	Repo() = default;
	Repo(const Repo& ot) = delete;

	//int getpoz(const Produs& el);

	void add(const Produs& el) override;

	const Produs& find(std::string nume, std::string tip, std::string producator)override {
		auto found = std::find_if(v.begin(), v.end(), [&](const Produs& pp){
			return pp.getnume() == nume && pp.gettip() == tip && pp.getproducator() == producator;
		});
		if (found == v.end()) {
			throw RepoException{ "Produs inexistent!!" };
		}
		return *found;
	}
	
	void remove(const Produs& el) override;
	
	void modify(const Produs& oel, const Produs& el) override;

	const vector<Produs>& getAll() noexcept override {
		return v;
	}
};

class FileRepo :public Repo {
private:
	std::string Fname;
	void loadFromFile();
	void writeToFile();
public:
	FileRepo(std::string Fname) :Repo(), Fname{ Fname } {
		loadFromFile();
	}
	void add(const Produs& el) override {
		Repo::add(el);
		writeToFile();
	}
	void remove(const Produs& el) override {
		Repo::remove(el);
		writeToFile();
	}

	void modify(const Produs& oel, const Produs& el) override {
		Repo::modify(oel, el);
		writeToFile();
	}
};
void testRepo();