#pragma once
#include "Produs.h"
#include "exceptii.h"
#include <vector>
#include <string>

using namespace std;

class validator
{
public:
	void validateProdus(const Produs& b) const;
};

