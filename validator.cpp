#include "validator.h"



void validator::validateProdus(const Produs& p) const {
	vector<string> v;
	if (p.getnume().size() == 0)
		v.push_back("Nume invalid");
	if (p.gettip().size() == 0)
		v.push_back("Tip invalid");
	if (p.getproducator().size() == 0)
		v.push_back("Producator invalid");

	if (v.size() != 0)
		throw ValidException(v);
}
