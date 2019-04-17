#include "IP.h"
void IP_Calc()
{
	IP_Adress MyIP;
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
		else
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
					break;
				}
				else goto Exit;
			}
	}
Exit:
	MyIP.Start();
	MyIP.PrintMainInfo();
	MyIP.PrintInfo();
	if (MySettings.GetLang() == "RUS") cout << "Эта информация также сохранена в файл \"Info\\IP_Calc.txt\"\n";
	if (MySettings.GetLang() == "ENG") cout << "This information have written to \"Info\\IP_Calc.txt\"\n";
	system("pause");
	system("cls");
}
void IP_Splitting()
{
	system("cls");
	int Count;
	IP_Adress MainNetwork;
	while (true)	
	{
		if (MySettings.GetLang() == "RUS") cout << "Введите IP-адрес в десятично-точечном формате.\n";
		if (MySettings.GetLang() == "ENG") cout << "Enter the IP-Address in decimal format.\n";
		if (MainNetwork.CinIP())			
		{
			if (MySettings.GetLang() == "RUS") cout << "Недопустимое значение для IP-Adress!!!\n";
			if (MySettings.GetLang() == "ENG") cout << "Invalid value for IP-Adress!!!\n";
			while (getchar() != '\n');
			system("pause");
			system("cls");
		}
		else
			while (true)
			{
				if (MySettings.GetLang() == "RUS") cout << "Введите маску подсети в десятично-точечном формате.\n";
				if (MySettings.GetLang() == "ENG") cout << "Enter the Net Mask in decimal format.\n";
				if (MainNetwork.CinMask())					
				{
					if (MySettings.GetLang() == "RUS") cout << "Недопустимое значение для Net Mask!!!\n";
					if (MySettings.GetLang() == "ENG") cout << "Invalid value for Net Mask!!!\n";
					while (getchar() != '\n');
					system("pause");
					system("cls");
					break;
				}
				else goto Exit;
			}
	}
Exit:
	if (MySettings.GetLang() == "RUS") cout << "Количество необходимых подсетей: ";
	if (MySettings.GetLang() == "ENG") cout << "The number of required subnets: ";
	if (scanf_s("%d", &Count) != 1)
	{
		if (MySettings.GetLang()=="RUS") cout << "Неверное количество подсетей!!!\n";
		if (MySettings.GetLang()=="ENG") cout << "Invalid number of subnets!!!\n";
		system("pause");
		system("cls");
		goto Exit;
	}
	int* Hosts = new int[Count];
Error:
	for (int i = 0; i < Count; i++)
	{
		if (MySettings.GetLang() == "RUS") cout << "\tПодсеть " << i + 1 << ": ";
		if (MySettings.GetLang() == "ENG") cout << "\tSubnet " << i+1 << ": ";
		if (scanf_s("%d", &Hosts) != 1)
		{
			if (MySettings.GetLang()=="RUS") cout << "Неверное количество IP-адресов!!!\n";
			if (MySettings.GetLang()=="ENG") cout << "Incorrect number of IP-addresses!!!\n";
			system("pause");
			system("cls");
			goto Error;
		}
	}
	IP_Adress* Network = new IP_Adress[Count];
	delete[]Network;
	delete[]Hosts;
}