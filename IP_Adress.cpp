#include "IP_Adress.h"
#include <iostream>
#include <string>
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
			BitMask += log10(NetMask[i] + 1) / log10(2);
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
	cout << "Adress: ";
	for (int i = 0; i < 3; i++) cout << IP[i] << "."; cout << IP[3] << " ";
	for (int i = 0; i < 3; i++) cout << bin(IP[i]) << "."; cout << bin(IP[3]) << ";\n";
	cout << "BitMask: " << BitMask << ";\n";
	cout << "NetMask: ";
	for (int i = 0; i < 3; i++) cout << NetMask[i] << "."; cout << NetMask[3] << " ";
	for (int i = 0; i < 3; i++) cout << bin(NetMask[i]) << "."; cout << bin(NetMask[3]) << ";\n";
}
void IP_Adress::PrintInfo()
{
	cout << "Network: ";
	for (int i = 0; i < 3; i++) cout << Network[i] << "."; cout << Network[3] << " ";
	for (int i = 0; i < 3; i++) cout << bin(Network[i]) << "."; cout << bin(Network[3]) << ";\n";
	cout << "Broadcast: ";
	for (int i = 0; i < 3; i++) cout << BroadCast[i] << "."; cout << BroadCast[3] << " ";
	for (int i = 0; i < 3; i++) cout << bin(BroadCast[i]) << "."; cout << bin(BroadCast[3]) << ";\n";
	cout << "Hostmin: ";
	for (int i = 0; i < 3; i++) cout << HostMin[i] << "."; cout << HostMin[3] << " ";
	for (int i = 0; i < 3; i++) cout << bin(HostMin[i]) << "."; cout << bin(HostMin[3]) << ";\n";
	cout << "Hostmax: ";
	for (int i = 0; i < 3; i++) cout << HostMax[i] << "."; cout << HostMax[3] << " ";
	for (int i = 0; i < 3; i++) cout << bin(HostMax[i]) << "."; cout << bin(HostMax[3]) << ";\n";
	cout << "Hosts: " << Hosts << ";\n";
}