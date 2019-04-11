#include "IP_Calc.h"
#include "Globals.h"
#include <iostream>
using namespace std;



void IP_Calc()
{
	system("cls");
	if (MySettings.GetLang() == "RUS") cout << "¬ведите IP-адрес в дес€тично-точечном формате.\n";
	if (MySettings.GetLang() == "ENG") cout << "Enter the IP-Address in decimal format.\n";
	MyIP.CinIP();
	if (MySettings.GetLang() == "RUS") cout << "¬ведите маску подсети в дес€тично-точечном формате.\n";
	if (MySettings.GetLang() == "ENG") cout << "Enter the Bit Mask in decimal format.\n";
	MyIP.CinMask();
	MyIP.Start();
	MyIP.PrintMainInfo();
	MyIP.PrintInfo();
	system("pause");
	system("cls");
}