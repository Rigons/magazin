#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "Observer.h"
#include "Produs.h"
using std::vector;

class CosProdus :public Observable {
	vector<Produs> inCos;
public:
	CosProdus() = default;
	void adauga(const Produs& p) {
		inCos.push_back(p);
		notify();
	}
	void goleste() noexcept{
		inCos.clear();
		notify();
	}
	void umple(size_t cate, vector<Produs> all) {
		std::shuffle(all.begin(), all.end(), std::default_random_engine(std::random_device{}()));
		while (inCos.size() < cate && all.size() > 0) {
			inCos.push_back(all.back());
			all.pop_back();
		}
		notify();
	}
	const vector<Produs>& lista() const noexcept{
		return inCos;
	}
};