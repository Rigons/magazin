#include "export.h"
#include "Produs.h"
#include <fstream>
#include <string>
#include "exceptii.h"
#include <vector>

void exportTOCVS(const std::string& Fname, const std::vector<Produs>& produse) {
	std::ofstream out(Fname, std::ios::trunc);
	if (!out.is_open()) {
		throw RepoException("Unable to opne file: " + Fname);
	}
	for (const auto& p : produse) {
		out << p.getnume() << ",";
		out << p.gettip() << ",";
		out << p.getproducator() << ",";
		out << p.getprice() << std::endl;
	}
	out.close();
}

void exportTOHTML(const std::string& Fname, const std::vector<Produs>& produse) {
	std::ofstream out(Fname, std::ios::trunc);
	if (!out.is_open()) {
		throw RepoException("Unable to open file: " + Fname);
	}
	out << "<html><body>" << std::endl;
	out << "<table border=\"1\" style=\"width:100 % \">" << std::endl;
	for (const auto& p : produse) {
		out << "<tr>" << std::endl;
		out << "<td>" << p.getnume() << "</td>" << std::endl;
		out << "<td>" << p.gettip() << "</td>" << std::endl;
		out << "<td>" << p.getproducator() << "</td>" << std::endl;
		out << "<td>" << p.getprice() << "</td>" << std::endl;
		out << "</tr>" << std::endl;
	}
	out << "</table>" << std::endl;
	out << "</body></html>" << std::endl;
	out.close();
}