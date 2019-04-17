#include "IP_Calc.h"
#include "Globals.h"
#include <iostream>
using namespace std;



void IP_Calc()
{
	system("cls");
	while (true)
	{
		if (MySettings.GetLang() == "RUS") cout << "Введите IP-адрес в десятично-точечном формате.\n";
		if (MySettings.GetLang() == "ENG") cout << "Enter the IP-Address in decimal format.\n";
		if (MyIP.CinIP())
		{
			if (MySettings.GetLang() == "RUS") cout << "Недопустимое значение для IP-Adress!!!\n";
			if (MySettings.GetLang() == "ENG") cout << "Invalid value for IP-Adress!!!\n";
			while (getchar() != '\n');
			system("pause");
			system("cls");
		}
		else break;
	}
	while (true)
	{
		if (MySettings.GetLang() == "RUS") cout << "Введите маску подсети в десятично-точечном формате.\n";
		if (MySettings.GetLang() == "ENG") cout << "Enter the Net Mask in decimal format.\n";
		if (MyIP.CinMask())
		{
			if (MySettings.GetLang() == "RUS") cout << "Недопустимое значение для Net Mask!!!\n";
			if (MySettings.GetLang() == "ENG") cout << "Invalid value for Net Mask!!!\n";
			while (getchar() != '\n');
			system("pause");
			system("cls");
		}
		else break;
	}
	MyIP.Start();
	MyIP.PrintMainInfo();
	MyIP.PrintInfo();
	if (MySettings.GetLang() == "RUS") cout << "Эта информация также сохранена в файл \"Info\\IP_Calc.txt\"\n";
	if (MySettings.GetLang() == "ENG") cout << "This information have written to \"Info\\IP_Calc.txt\"\n";
	system("pause");
	system("cls");
}