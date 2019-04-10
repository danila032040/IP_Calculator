#pragma once
#include <string>
using namespace std;

class Settings
{
private:
	string Lang;
public:
	Settings();
	~Settings();
	string GetLang();
	void SetLang();
	int Set();
	int Load();
};

