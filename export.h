#pragma once
#include <string>
#include <vector>
#include "Produs.h"

void exportTOCVS(const std::string& Fname, const std::vector<Produs>& produse);

void exportTOHTML(const std::string& Fname, const std::vector<Produs>& produse);