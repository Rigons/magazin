#include "Produs.h"
#include <assert.h>



Produs& Produs::operator=(const Produs& ot) {
	if (this == &ot) {
		return *this;
	}
	nume = ot.nume;
	tip = ot.tip;
	producator = ot.producator;
	price = ot.price;
	return *this;
}
double Produs::getprice()const noexcept {
	return price;
}

string Produs::getnume()const {
	return nume;
}
string Produs::gettip()const {
	return tip;
}

string Produs::getproducator()const {
	return producator;
}

void testNew() {
	Produs p1{ "Ceara", "casa", "Well", 5.0 };
	Produs p2{ "Ceara","afara","Well",2.0 };
	assert(Produs::cmpnume(p1, p2) == false);
	assert(Produs::cmpprice(p2, p1) == true);
	assert(Produs::cmpnumetip(p1, p2) == false);
	assert(p1.gettip() == "casa");
	assert(p1.getnume() == "Ceara");
	assert(p1.getprice() == 5.0);
	assert(p1.getproducator() == "Well");
	assert((p1==p2)==0);
	p2 = p2;
	p2 = p1;
	assert(p1.gettip() == "casa");
}
void testProdus() {
	testNew();
}
