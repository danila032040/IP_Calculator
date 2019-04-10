#include "Settings.h"
#include <conio.h>
#include <fstream>
#include <direct.h>
#include <windows.h>

Settings::Settings()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	if (Load())
	{
		if (Set())
		{
			cout << "Критическая ошибка!!!\n";
			cout << "Critical error!!!\n";
			system("pause");
			exit(1);
		}
	}
	else
	{
		if (Lang == "RUS") cout << "Настройки успешно загружены!!!\n";
		if (Lang == "ENG") cout << "Your settings are successfully uploaded!!!\n";
		if (Lang == "RUS") cout << "Выбранный язык - Русский\n";
		if (Lang == "ENG") cout << "Your language - English\n";
	}
}
Settings::~Settings()
{
}

string Settings::GetLang() 
{
	return Lang;
}
void Settings::SetLang()
{
	int Ans;
	while (true)
	{
		cout << "Choose your language\n";
		cout << "\t1 - ENG\n";
		cout << "\t2 - RUS\n";
		cin >> Ans;
		if (Ans != 1 && Ans != 2) cout << "Error\n";
		else
		{
			cout << "Press Y/N\n";
			char c = _getch();
			if (c == 'y' || c == 'Y')
			{
				switch (Ans)
				{
					case 1: Lang = "ENG"; break;
					case 2: Lang = "RUS"; break;
				}
				return;
			}
		}
	}
}

int Settings::Set()
{
	system("cls");
	_mkdir("Settings");
	_chdir("Settings");
	ofstream fout("Settings.txt");
	if (!fout.is_open())
	{
		cout << "Ошибка открытия файла!!!\n";
		cout << "Can not open the file!!!\n";
		_chdir("..");
		system("pause");
		system("cls");
		return 1;
	}
	SetLang();
	fout << Lang;
	fout.close();
	_chdir("..");
	system("cls");
	return 0;
}
int Settings::Load()
{
	system("cls");
	_mkdir("Settings");
	_chdir("Settings");
	ifstream fin("Settings.txt");
	if (!fin.is_open())
	{
		cout << "Ошибка открытия файла!!!\n";
		cout << "Can not open the file!!!\n";
		_chdir("..");
		system("pause");
		system("cls");
		return 1;
	}
	fin >> Lang;
	fin.close();
	_chdir("..");
	system("cls");
	return 0;
}
