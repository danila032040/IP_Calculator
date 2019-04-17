#include "IP_Calc.h"
#include "Globals.h"
#include <iostream>
using namespace std;



void IP_Calc()
{
	system("cls");
	while (true)
	{
		if (MySettings.GetLang() == "RUS") cout << "¬ведите IP-адрес в дес€тично-точечном формате.\n";
		if (MySettings.GetLang() == "ENG") cout << "Enter the IP-Address in decimal format.\n";
		if (MyIP.CinIP())
		{
			if (MySettings.GetLang() == "RUS") cout << "Ќедопустимое значение дл€ IP-Adress!!!\n";
			if (MySettings.GetLang() == "ENG") cout << "Invalid value for IP-Adress!!!\n";
			while (getchar() != '\n');
			system("pause");
			system("cls");
		}
		else break;
	}
	while (true)
	{
		if (MySettings.GetLang() == "RUS") cout << "¬ведите маску подсети в дес€тично-точечном формате.\n";
		if (MySettings.GetLang() == "ENG") cout << "Enter the Net Mask in decimal format.\n";
		if (MyIP.CinMask())
		{
			if (MySettings.GetLang() == "RUS") cout << "Ќедопустимое значение дл€ Net Mask!!!\n";
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
	system("pause");
	system("cls");
}