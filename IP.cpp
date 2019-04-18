#include "IP.h"
#include <direct.h>
#include <algorithm>
#include <vector>
using namespace std;

bool cmp(pair<int, int> a, pair<int, int> b)
{
	return a.first > b.first;
}

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
	MyIP.PrintInfo();
	if (MySettings.GetLang() == "RUS") cout << "Эта информация также сохранена в файл \"Info\\IP_Calc.txt\"\n";
	if (MySettings.GetLang() == "ENG") cout << "This information have written to \"Info\\IP_Calc.txt\"\n";
	system("pause");
	system("cls");
}
void IP_Splitting()
{
	system("cls");
Error:
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
	MainNetwork.Start();
	if (MySettings.GetLang() == "RUS") cout << "Количество необходимых подсетей: ";
	if (MySettings.GetLang() == "ENG") cout << "The number of required subnets: ";
	if (scanf_s("%d", &Count) != 1 || 4*Count-2>MainNetwork.GetHosts())
	{
		if (MySettings.GetLang()=="RUS") cout << "Неверное количество подсетей!!!\n";
		if (MySettings.GetLang()=="ENG") cout << "Invalid number of subnets!!!\n";
		system("pause");
		system("cls");
		goto Error;
	}
	int* Hosts = new int[Count];
	int AllHosts = 0,FreeIP = 0;
	for (int i = 0; i < Count; i++)
	{
		if (MySettings.GetLang() == "RUS") cout << "\tПодсеть " << i + 1 << ": ";
		if (MySettings.GetLang() == "ENG") cout << "\tSubnet " << i+1 << ": ";
		if (scanf_s("%d", &Hosts[i]) != 1)
		{
			if (MySettings.GetLang()=="RUS") cout << "Неверное количество IP-адресов!!!\n";
			if (MySettings.GetLang()=="ENG") cout << "Incorrect number of IP-addresses!!!\n";
			system("pause");
			system("cls");
			delete[]Hosts;
			goto Error;
		}
		FreeIP += Hosts[i]+2;
		AllHosts+=pow(2, int(log10(Hosts[i] +2 + 1) / log10(2)));
	}
	if (AllHosts> MainNetwork.GetHosts())
	{
		if (MySettings.GetLang() == "RUS") cout << "Неверное количество IP-адресов!!!\n";
		if (MySettings.GetLang() == "ENG") cout << "Incorrect number of IP-addresses!!!\n";
		system("pause");
		system("cls");
		delete[]Hosts;
		goto Error;
	}
	IP_Adress* Network = new IP_Adress[Count];
	int *Name = new int[Count];
	for (int i = 0; i < Count; i++) Name[i] = i+1;
	cout << "\n";
	{
		vector<pair<int, int>> Sort;
		for (int i = 0; i < Count; i++) Sort.push_back(make_pair(Hosts[i], Name[i]));
		sort(Sort.begin(), Sort.end(), cmp);
		for (int i = 0; i < Count; i++)
		{
			Hosts[i] = Sort[i].first;
			Name[i] = Sort[i].second;
		}
	}
	Network[0].Make(Hosts[0],MainNetwork);
	for (int i = 1; i < Count; i++)
	{
		Network[i].Make(Network[i - 1], Hosts[i]);
	}
	MainNetwork.PrintMainInfo();
	for (int i = 0; i < Count; i++)
	{
		FILE* output;
		_mkdir("Info");
		_chdir("Info");
		fopen_s(&output, "IP_Splitting.txt", "a");
		if (MySettings.GetLang() == "RUS")
		{
			cout << "Подсеть " << Name[i] << ":\n";
			fprintf_s(output,"Подсеть %d:\n", Name[i]);
		}
		if (MySettings.GetLang() == "ENG")
		{
			cout << "Subnet " << Name[i] << ":\n";
			fprintf_s(output, "Subnet %d:\n", Name[i]);
		}
		fclose(output);
		_chdir("..");
		Network[i].PrintOtherInfo();
	}
	FILE* output;
	_mkdir("Info");
	_chdir("Info");
	fopen_s(&output, "IP_Splitting.txt", "a");
	FreeIP = MainNetwork.GetHosts() - FreeIP;
	if (MySettings.GetLang() == "RUS")
	{
		printf_s("Свободных IP адресов: %20d\n", FreeIP);
		fprintf_s(output, "Свободных IP адресов: %20d\n", FreeIP);
	}
	if (MySettings.GetLang() == "ENG")
	{
		printf_s("Free IP Addresses: %23d:\n", FreeIP);
		fprintf_s(output, "Free IP Addresses: %23d\n", FreeIP);
	}
	fclose(output);
	_chdir("..");
	delete[]Network;
	delete[]Hosts;
	if (MySettings.GetLang() == "RUS") cout << "Эта информация также сохранена в файл \"Info\\IP_Splitting.txt\"\n";
	if (MySettings.GetLang() == "ENG") cout << "This information have written to \"Info\\IP_Splitting.txt\"\n";
	system("pause");
	system("cls");
}