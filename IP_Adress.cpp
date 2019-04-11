#include "IP_Adress.h"
#include <iostream>
#include <string>
#include <direct.h>
using namespace std;
string IP_Adress::bin(int x)
{
	string s="";
	for (int i = 7; i >= 0; --i) s += to_string((x >> i) & 1);
	return s;
}
IP_Adress::IP_Adress() 
{
	for (int i = 0; i < 4; i++)
	{
		IP[i] = 0;
		NetMask[i] = 0;
		HostMin[i] = 0;
		HostMax[i] = 0;
		Network[i] = 0;
		BroadCast[i] = 0;
	}
	BitMask = 0;
	Hosts = 0;
}
IP_Adress::~IP_Adress()
{
}

void IP_Adress::CinIP()
{
	for (int i = 0; i < 3; i++) scanf_s("%d.", &IP[i]); scanf_s("%d", &IP[3]);

}
void IP_Adress::CinMask()
{
	string s;
	cin >> s;
	if (s.find('.') == -1)
	{
		BitMask = atoi(s.c_str());
		int Help = BitMask, i = 0;
		while (Help >= 8)
		{
			NetMask[i] = 255;
			Help -= 8;
			i++;
		}
		while (Help > 0)
		{
			NetMask[i]+=1 << (8-Help);
			Help--;
		}
	}
	else
	{
		for (int i = 3; i >= 0; i--)
		{
			string c;
			if (s.find_last_of('.') != -1)
			{
				c=s.substr(s.find_last_of('.') + 1, s.size());
				s.erase(s.find_last_of('.'), s.size());
			}
			else c = s;
			NetMask[i] = atoi(c.c_str());
			BitMask += int(log10(NetMask[i] + 1) / log10(2));
		}
	}
}

void IP_Adress::Start()
{
	for (int i = 0; i < 4; i++)
	{
		Network[i] = NetMask[i] & IP[i];
		HostMin[i] = Network[i];
		BroadCast[i] = NetMask[i] & IP[i];
		if (NetMask[i] != 255 && NetMask[i]!=0)
		{
			int Help = 8-(BitMask % 8), a=0;
			while (Help > 0)
			{
				a = a << 1;
				a++;
				Help--;
			}
			BroadCast[i] += a;
		}
		if (NetMask[i] == 0) BroadCast[i] = 255;
		HostMax[i] = BroadCast[i];
	}
	HostMin[3]++;
	{
		int Help = 31 - BitMask;
		while (Help > 0)
		{
			Hosts = (Hosts + 1) << 1;
			Help--;
		}
	}
	HostMax[3]--;
}

void IP_Adress::PrintMainInfo()
{
	printf_s("*********************************************************************\n");
	printf_s("*   Adress  * %3d.%3d.%3d.%3d * %s.%s.%s.%s *\n",IP[0],IP[1],IP[2],IP[3],bin(IP[0]).c_str(),bin(IP[1]).c_str(),bin(IP[2]).c_str(),bin(IP[3]).c_str());
	printf_s("*********************************************************************\n");
	printf_s("*  BitMask  *%28d                           *\n",BitMask);
	printf_s("*********************************************************************\n");
	printf_s("*  NetMask  * %3d.%3d.%3d.%3d * %s.%s.%s.%s *\n", NetMask[0], NetMask[1], NetMask[2], NetMask[3], bin(NetMask[0]).c_str(), bin(NetMask[1]).c_str(), bin(NetMask[2]).c_str(), bin(NetMask[3]).c_str());
	printf_s("*********************************************************************\n");
	FILE* output;
	_mkdir("Info");
	_chdir("Info");
	fopen_s(&output, "IP_Calc.txt", "w");
	fprintf_s(output,"*********************************************************************\n");
	fprintf_s(output,"*   Adress  * %3d.%3d.%3d.%3d * %s.%s.%s.%s *\n", IP[0], IP[1], IP[2], IP[3], bin(IP[0]).c_str(), bin(IP[1]).c_str(), bin(IP[2]).c_str(), bin(IP[3]).c_str());
	fprintf_s(output,"*********************************************************************\n");
	fprintf_s(output,"*  BitMask  *%28d                           *\n", BitMask);
	fprintf_s(output,"*********************************************************************\n");
	fprintf_s(output,"*  NetMask  * %3d.%3d.%3d.%3d * %s.%s.%s.%s *\n", NetMask[0], NetMask[1], NetMask[2], NetMask[3], bin(NetMask[0]).c_str(), bin(NetMask[1]).c_str(), bin(NetMask[2]).c_str(), bin(NetMask[3]).c_str());
	fprintf_s(output,"*********************************************************************\n");
	fclose(output);
	_chdir("..");
}
void IP_Adress::PrintInfo()
{
	printf_s("*********************************************************************\n");
	printf_s("*  Network  * %3d.%3d.%3d.%3d * %s.%s.%s.%s *\n", Network[0], Network[1], Network[2], Network[3], bin(Network[0]).c_str(), bin(Network[1]).c_str(), bin(Network[2]).c_str(), bin(Network[3]).c_str());
	printf_s("*********************************************************************\n");
	printf_s("* Broadcast * %3d.%3d.%3d.%3d * %s.%s.%s.%s *\n", BroadCast[0], BroadCast[1], BroadCast[2], BroadCast[3], bin(BroadCast[0]).c_str(), bin(BroadCast[1]).c_str(), bin(BroadCast[2]).c_str(), bin(BroadCast[3]).c_str());
	printf_s("*********************************************************************\n");
	printf_s("*  Hostmin  * %3d.%3d.%3d.%3d * %s.%s.%s.%s *\n", HostMin[0], HostMin[1], HostMin[2], HostMin[3], bin(HostMin[0]).c_str(), bin(HostMin[1]).c_str(), bin(HostMin[2]).c_str(), bin(HostMin[3]).c_str());
	printf_s("*********************************************************************\n");
	printf_s("*  Hostmax  * %3d.%3d.%3d.%3d * %s.%s.%s.%s *\n", HostMax[0], HostMax[1], HostMax[2], HostMax[3], bin(HostMax[0]).c_str(), bin(HostMax[1]).c_str(), bin(HostMax[2]).c_str(), bin(HostMax[3]).c_str());
	printf_s("*********************************************************************\n");
	printf_s("*   Hosts   *%28d                           *\n", Hosts);
	printf_s("*********************************************************************\n");
	FILE* output;
	_mkdir("Info");
	_chdir("Info");
	fopen_s(&output, "IP_Calc.txt", "a");
	fprintf_s(output,"*********************************************************************\n");
	fprintf_s(output,"*  Network  * %3d.%3d.%3d.%3d * %s.%s.%s.%s *\n", Network[0], Network[1], Network[2], Network[3], bin(Network[0]).c_str(), bin(Network[1]).c_str(), bin(Network[2]).c_str(), bin(Network[3]).c_str());
	fprintf_s(output,"*********************************************************************\n");
	fprintf_s(output,"* Broadcast * %3d.%3d.%3d.%3d * %s.%s.%s.%s *\n", BroadCast[0], BroadCast[1], BroadCast[2], BroadCast[3], bin(BroadCast[0]).c_str(), bin(BroadCast[1]).c_str(), bin(BroadCast[2]).c_str(), bin(BroadCast[3]).c_str());
	fprintf_s(output,"*********************************************************************\n");
	fprintf_s(output,"*  Hostmin  * %3d.%3d.%3d.%3d * %s.%s.%s.%s *\n", HostMin[0], HostMin[1], HostMin[2], HostMin[3], bin(HostMin[0]).c_str(), bin(HostMin[1]).c_str(), bin(HostMin[2]).c_str(), bin(HostMin[3]).c_str());
	fprintf_s(output,"*********************************************************************\n");
	fprintf_s(output,"*  Hostmax  * %3d.%3d.%3d.%3d * %s.%s.%s.%s *\n", HostMax[0], HostMax[1], HostMax[2], HostMax[3], bin(HostMax[0]).c_str(), bin(HostMax[1]).c_str(), bin(HostMax[2]).c_str(), bin(HostMax[3]).c_str());
	fprintf_s(output,"*********************************************************************\n");
	fprintf_s(output,"*   Hosts   *%28d                           *\n", Hosts);
	fprintf_s(output,"*********************************************************************\n");
	fclose(output);
	_chdir("..");
}