#pragma once
#include <string>
#include <iostream>
using namespace std;


class Produs
{

public:
	Produs() = default;
	Produs(const std::string n, std::string t, std::string prod, double p) :nume{ n }, tip{ t }, producator{ prod }, price{ p }{}
	double getprice()const noexcept;
	string getnume()const;
	string gettip()const;
	string getproducator()const;
	Produs& operator=(const Produs& ot);
	void setprice(const double nprice) noexcept{
		this->price = nprice;
	}
	void settip(const string& ntip) noexcept{
		this->tip = ntip;
	}
	void setnume(const string& nnume) noexcept{
		this->nume = nnume;
	}
	void setproducator(const string& nproducator) {
		this->producator = nproducator;
	}
	bool operator==(const Produs& other)const noexcept{
		return nume == other.nume && tip == other.tip && producator == other.producator;
	}
	static bool cmpnumetip(const Produs& p1, const Produs& p2) {
		if(p1.getnume()==p2.getnume())
			return p1.gettip() < p2.gettip();
		return p1.getnume() < p2.getnume();
	}

	static bool cmpnume(const Produs& p1, const Produs& p2) {
		return p1.getnume() < p2.getnume();
	}

	static bool cmpprice(const Produs& p1, const Produs& p2) noexcept{
		return p1.getprice() < p2.getprice();
	}

	static bool filprice(const Produs& p1, const Produs& p2) noexcept {
		return p1.getprice() >= p2.getprice();
	}
	static bool filnume(const Produs& p1, const Produs& p2) noexcept {
		return p1.getnume() >= p2.getnume();
	}
	static bool filproducator(const Produs& p1, const Produs& p2) noexcept {
		return p1.getproducator() >= p2.getproducator();
	}
private:
	std::string nume;
	std::string tip;
	std::string producator;
	double price=-1.0;

};



void testProdus();