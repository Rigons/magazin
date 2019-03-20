#pragma once
#include <vector>
using namespace std;
class MylisttempException {
private:
	std::string mesaj;
public:
	MylisttempException(const std::string& message) : mesaj{ message } {}

	std::string getMessage()const {
		return mesaj;
	}
};
class ValidException {
private:
	std::vector<std::string> mesaj;
public:
	ValidException(const std::vector<std::string>& message) : mesaj{ message } {}

	std::string getMessage() const {
		std::string s = "";
		for (const auto& msg : mesaj)
			s += msg + "\n";
		return s;
	}
};
class RepoException {
private:
	std::string mesaj;
public:
	RepoException(const std::string& message) :mesaj{ message } {}
	std::string getMesage()const {
		return mesaj;
	}
};