#include <iostream>
#include "Globals.h"
using namespace std;

void Menu()
{
	MySettings.Load();
	if (MySettings.GetLang()=="RUS") cout << "Добро пожаловать в IP-Calculator 3000!!!\n";
	if (MySettings.GetLang() == "ENG") cout << "Welcome to IP-Calculator 3000!!!\n";
	int Ans = 0;
	while (true)
	{
		if (MySettings.GetLang() == "RUS") cout << "Введите 1 для IP-Calculator\n";
		if (MySettings.GetLang() == "ENG") cout << "Write 1 for IP-Calculator\n";
		if (MySettings.GetLang() == "RUS") cout << "Введите 2 для IP разбития сети\n";
		if (MySettings.GetLang() == "ENG") cout << "Write 2 for IP-Splitting\n";
		if (MySettings.GetLang() == "RUS") cout << "Введите 3 для настройки программы\n";
		if (MySettings.GetLang() == "ENG") cout << "Write 3 for settings\n";
		if (MySettings.GetLang() == "RUS") cout << "Введите 4 для выхода\n";
		if (MySettings.GetLang() == "ENG") cout << "Write 4 for exit\n";
		cin >> Ans;
		switch (Ans)
		{
			case 1:
			{
				IP_Calc();
				break;
			}
			case 2:
			{
				IP_Splitting();
				break;
			}
			case 3:
			{
				MySettings.Set();
				MySettings.Load();
				break;
			}
			case 4:
			{
				goto Exit;
				break;
			}
		}
	}
	Exit:
	if (MySettings.GetLang() == "RUS") cout << "Спасибо за использование нашей программы!!!\n";
	if (MySettings.GetLang() == "RUS") cout << "								©Red Papers Comp\n";
	if (MySettings.GetLang() == "ENG") cout << "Thanks for using our programm!!!\n";
	if (MySettings.GetLang() == "ENG") cout << "                     ©Red Papers Comp\n";
}

int main()
{
	Menu();
	system("pause");
	return 0;
}