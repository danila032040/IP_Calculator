#include "IP_Calc.h"
#include "Globals.h"
#include <iostream>
using namespace std;



void IP_Calc()
{
	system("cls");
	if (MySettings.GetLang() == "RUS") cout << "Введите IP-адрес в десятично-точечном формате.\n";
	if (MySettings.GetLang() == "ENG") cout << "Enter the IP-Address in decimal format.\n";
	MyIP.CinIP();
	if (MySettings.GetLang() == "RUS") cout << "Введите маску подсети в десятично-точечном формате.\n";
	if (MySettings.GetLang() == "ENG") cout << "Enter the Bit Mask in decimal format.\n";
	MyIP.CinMask();
	MyIP.Start();
	MyIP.PrintMainInfo();
	MyIP.PrintInfo();
	if (MySettings.GetLang() == "RUS") cout << "Эта информация также сохранена в файл \"Info\\IP_Calc.txt\"\n";
	if (MySettings.GetLang() == "ENG") cout << "This information have written to \"Info\\IP_Calc.txt\"\n";
	system("pause");
	system("cls");
}