#include "IP_Adress.h"
#include "Globals.h"
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

int IP_Adress::CinIP()
{
	if (scanf_s("%d.%d.%d.%d\0", &IP[0],&IP[1],&IP[2],&IP[3])!=4) return 1;
	for (int i = 0; i < 4; i++)
		if (IP[i] > 255 || IP[i]<0) return 1;
	return 0;
}

int IP_Adress::CinMask()
{
	int Err = scanf_s("%d.%d.%d.%d\0", &NetMask[0], &NetMask[1], &NetMask[2], &NetMask[3]);
	if (Err == 1)
	{
		BitMask = NetMask[0];
		if (BitMask > 32 || BitMask < 0) return 1;
		NetMask[0] = 0;
		int Help = BitMask, i = 0;
		while (Help >= 8)
		{
			NetMask[i] = 255;
			Help -= 8;
			i++;
		}
		if (Help>0) NetMask[i] = 0;
		while (Help > 0)
		{
			NetMask[i] += 1 << (8 - Help);
			Help--;
		}
	}
	else
	{
		if (Err != 4) return 1;
		for (int i = 0; i < 4; i++)
		{
			if (NetMask[i] != 255 && NetMask[i] != 254 && NetMask[i] != 252 &&
				NetMask[i] != 248 && NetMask[i] != 240 && NetMask[i] != 224 &&
				NetMask[i] != 192 && NetMask[i] != 128 && NetMask[i] != 0) return 1;
			BitMask += int(log10(NetMask[i] + 1) / log10(2));
		}
	}
	return 0;
}

void IP_Adress::Start()
{
	if (BitMask == 32)
	{
		for (int i = 0; i < 4; i++)
		{
			Network[i] = IP[i];
			BroadCast[i] = IP[i];
			HostMax[i] = IP[i];
			HostMin[i] = IP[i];
		}
		Hosts = 0;
	}
	else
		if (BitMask == 31)
		{
			for (int i = 0; i < 4; i++)
			{
				Network[i] = IP[i];
				BroadCast[i] = IP[i];
				HostMax[i] = IP[i];
				HostMin[i] = IP[i];
			}
			BroadCast[3]++;
			HostMax[3]++;
			Hosts = 0;
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				Network[i] = NetMask[i] & IP[i];
				HostMin[i] = Network[i];
				BroadCast[i] = NetMask[i] & IP[i];
				if (NetMask[i] != 255 && NetMask[i] != 0)
				{
					int Help = 8 - (BitMask % 8), a = 0;
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
}

void IP_Adress::PrintMainInfo()
{
	string Sdvig = "";
	for (int i = 0; i < 4; i++)
	{
		if (IP[i] < 100) Sdvig += " ";
		if (IP[i] < 9) Sdvig += " ";
	}
	printf_s("Adress:    %d.%d.%d.%d%s %s.%s.%s.%s\n", IP[0], IP[1], IP[2], IP[3], Sdvig.c_str(), bin(IP[0]).c_str(), bin(IP[1]).c_str(), bin(IP[2]).c_str(), bin(IP[3]).c_str());
	printf_s("BitMask: %25d                            \n", BitMask);
	Sdvig = "";
	for (int i = 0; i < 4; i++)
	{
		if (NetMask[i] < 100) Sdvig += " ";
		if (NetMask[i] < 9) Sdvig += " ";
	}
	printf_s("NetMask:   %d.%d.%d.%d%s %s.%s.%s.%s\n", NetMask[0], NetMask[1], NetMask[2], NetMask[3], Sdvig.c_str(), bin(NetMask[0]).c_str(), bin(NetMask[1]).c_str(), bin(NetMask[2]).c_str(), bin(NetMask[3]).c_str());
	printf_s("\n");
	FILE* output;
	_mkdir("Info");
	_chdir("Info");
	fopen_s(&output, "IP_Splitting.txt", "w");
	Sdvig = "";
	for (int i = 0; i < 4; i++)
	{
		if (IP[i] < 100) Sdvig += " ";
		if (IP[i] < 9) Sdvig += " ";
	}
	fprintf_s(output, "Adress:    %d.%d.%d.%d%s %s.%s.%s.%s\n", IP[0], IP[1], IP[2], IP[3], Sdvig.c_str(), bin(IP[0]).c_str(), bin(IP[1]).c_str(), bin(IP[2]).c_str(), bin(IP[3]).c_str());
	fprintf_s(output, "BitMask: %25d                            \n", BitMask);
	Sdvig = "";
	for (int i = 0; i < 4; i++)
	{
		if (NetMask[i] < 100) Sdvig += " ";
		if (NetMask[i] < 9) Sdvig += " ";
	}
	fprintf_s(output, "NetMask:   %d.%d.%d.%d%s %s.%s.%s.%s\n", NetMask[0], NetMask[1], NetMask[2], NetMask[3], Sdvig.c_str(), bin(NetMask[0]).c_str(), bin(NetMask[1]).c_str(), bin(NetMask[2]).c_str(), bin(NetMask[3]).c_str());
	fprintf_s(output, "\n");
	fclose(output);
	_chdir("..");
}
void IP_Adress::PrintOtherInfo()
{
	string Sdvig = "";
	for (int i = 0; i < 4; i++)
	{
		if (IP[i] < 100) Sdvig += " ";
		if (IP[i] < 9) Sdvig += " ";
	}
	printf_s("\tAdress:    %d.%d.%d.%d%s %s.%s.%s.%s\n", IP[0], IP[1], IP[2], IP[3], Sdvig.c_str(), bin(IP[0]).c_str(), bin(IP[1]).c_str(), bin(IP[2]).c_str(), bin(IP[3]).c_str());
	printf_s("\tBitMask: %25d                            \n", BitMask);
	Sdvig = "";
	for (int i = 0; i < 4; i++)
	{
		if (NetMask[i] < 100) Sdvig += " ";
		if (NetMask[i] < 9) Sdvig += " ";
	}
	printf_s("\tNetMask:   %d.%d.%d.%d%s %s.%s.%s.%s\n", NetMask[0], NetMask[1], NetMask[2], NetMask[3], Sdvig.c_str(), bin(NetMask[0]).c_str(), bin(NetMask[1]).c_str(), bin(NetMask[2]).c_str(), bin(NetMask[3]).c_str());
	Sdvig = "";
	for (int i = 0; i < 4; i++)
	{
		if (Network[i] < 100) Sdvig += " ";
		if (Network[i] < 9) Sdvig += " ";
	}
	printf_s("\tNetwork:   %d.%d.%d.%d%s %s.%s.%s.%s\n", Network[0], Network[1], Network[2], Network[3], Sdvig.c_str(), bin(Network[0]).c_str(), bin(Network[1]).c_str(), bin(Network[2]).c_str(), bin(Network[3]).c_str());
	Sdvig = "";
	for (int i = 0; i < 4; i++)
	{
		if (HostMin[i] < 100) Sdvig += " ";
		if (HostMin[i] < 9) Sdvig += " ";
	}
	printf_s("\tHostmin:   %d.%d.%d.%d%s %s.%s.%s.%s\n", HostMin[0], HostMin[1], HostMin[2], HostMin[3], Sdvig.c_str(), bin(HostMin[0]).c_str(), bin(HostMin[1]).c_str(), bin(HostMin[2]).c_str(), bin(HostMin[3]).c_str());
	Sdvig = "";
	for (int i = 0; i < 4; i++)
	{
		if (HostMax[i] < 100) Sdvig += " ";
		if (HostMax[i] < 9) Sdvig += " ";
	}
	printf_s("\tHostmax:   %d.%d.%d.%d%s %s.%s.%s.%s\n", HostMax[0], HostMax[1], HostMax[2], HostMax[3], Sdvig.c_str(), bin(HostMax[0]).c_str(), bin(HostMax[1]).c_str(), bin(HostMax[2]).c_str(), bin(HostMax[3]).c_str());
	Sdvig = "";
	for (int i = 0; i < 4; i++)
	{
		if (BroadCast[i] < 100) Sdvig += " ";
		if (BroadCast[i] < 9) Sdvig += " ";
	}
	printf_s("\tBroadcast: %d.%d.%d.%d%s %s.%s.%s.%s\n", BroadCast[0], BroadCast[1], BroadCast[2], BroadCast[3], Sdvig.c_str(), bin(BroadCast[0]).c_str(), bin(BroadCast[1]).c_str(), bin(BroadCast[2]).c_str(), bin(BroadCast[3]).c_str());
	printf_s("\tHosts:   %25d                            \n", Hosts);
	FILE* output;
	_mkdir("Info");
	_chdir("Info");
	fopen_s(&output, "IP_Splitting.txt", "a");
	Sdvig = "";
	for (int i = 0; i < 4; i++)
	{
		if (IP[i] < 100) Sdvig += " ";
		if (IP[i] < 9) Sdvig += " ";
	}
	fprintf_s(output, "\tAdress:    %d.%d.%d.%d%s %s.%s.%s.%s\n", IP[0], IP[1], IP[2], IP[3], Sdvig.c_str(), bin(IP[0]).c_str(), bin(IP[1]).c_str(), bin(IP[2]).c_str(), bin(IP[3]).c_str());
	fprintf_s(output, "\tBitMask: %25d                            \n", BitMask);
	Sdvig = "";
	for (int i = 0; i < 4; i++)
	{
		if (NetMask[i] < 100) Sdvig += " ";
		if (NetMask[i] < 9) Sdvig += " ";
	}
	fprintf_s(output, "\tNetMask:   %d.%d.%d.%d%s %s.%s.%s.%s\n", NetMask[0], NetMask[1], NetMask[2], NetMask[3], Sdvig.c_str(), bin(NetMask[0]).c_str(), bin(NetMask[1]).c_str(), bin(NetMask[2]).c_str(), bin(NetMask[3]).c_str());

	Sdvig = "";
	for (int i = 0; i < 4; i++)
	{
		if (Network[i] < 100) Sdvig += " ";
		if (Network[i] < 9) Sdvig += " ";
	}
	fprintf_s(output, "\tNetwork:   %d.%d.%d.%d%s %s.%s.%s.%s\n", Network[0], Network[1], Network[2], Network[3], Sdvig.c_str(), bin(Network[0]).c_str(), bin(Network[1]).c_str(), bin(Network[2]).c_str(), bin(Network[3]).c_str());
	Sdvig = "";
	for (int i = 0; i < 4; i++)
	{
		if (HostMin[i] < 100) Sdvig += " ";
		if (HostMin[i] < 9) Sdvig += " ";
	}
	fprintf_s(output, "\tHostmin:   %d.%d.%d.%d%s %s.%s.%s.%s\n", HostMin[0], HostMin[1], HostMin[2], HostMin[3], Sdvig.c_str(), bin(HostMin[0]).c_str(), bin(HostMin[1]).c_str(), bin(HostMin[2]).c_str(), bin(HostMin[3]).c_str());
	Sdvig = "";
	for (int i = 0; i < 4; i++)
	{
		if (HostMax[i] < 100) Sdvig += " ";
		if (HostMax[i] < 9) Sdvig += " ";
	}
	fprintf_s(output, "\tHostmax:   %d.%d.%d.%d%s %s.%s.%s.%s\n", HostMax[0], HostMax[1], HostMax[2], HostMax[3], Sdvig.c_str(), bin(HostMax[0]).c_str(), bin(HostMax[1]).c_str(), bin(HostMax[2]).c_str(), bin(HostMax[3]).c_str());
	Sdvig = "";
	for (int i = 0; i < 4; i++)
	{
		if (BroadCast[i] < 100) Sdvig += " ";
		if (BroadCast[i] < 9) Sdvig += " ";
	}
	fprintf_s(output, "\tBroadcast: %d.%d.%d.%d%s %s.%s.%s.%s\n", BroadCast[0], BroadCast[1], BroadCast[2], BroadCast[3], Sdvig.c_str(), bin(BroadCast[0]).c_str(), bin(BroadCast[1]).c_str(), bin(BroadCast[2]).c_str(), bin(BroadCast[3]).c_str());
	fprintf_s(output, "\tHosts:   %25d                            \n", Hosts);
	fclose(output);
	_chdir("..");
}

void IP_Adress::PrintInfo()
{
	string Sdvig = "";
	for (int i = 0; i < 4; i++)
	{
		if (IP[i] < 100) Sdvig += " ";
		if (IP[i] < 9) Sdvig += " ";
	}
	printf_s("Adress:    %d.%d.%d.%d%s %s.%s.%s.%s\n", IP[0], IP[1], IP[2], IP[3], Sdvig.c_str(), bin(IP[0]).c_str(), bin(IP[1]).c_str(), bin(IP[2]).c_str(), bin(IP[3]).c_str());
	printf_s("BitMask: %25d                            \n", BitMask);
	Sdvig = "";
	for (int i = 0; i < 4; i++)
	{
		if (NetMask[i] < 100) Sdvig += " ";
		if (NetMask[i] < 9) Sdvig += " ";
	}
	printf_s("NetMask:   %d.%d.%d.%d%s %s.%s.%s.%s\n", NetMask[0], NetMask[1], NetMask[2], NetMask[3], Sdvig.c_str(), bin(NetMask[0]).c_str(), bin(NetMask[1]).c_str(), bin(NetMask[2]).c_str(), bin(NetMask[3]).c_str());
	Sdvig = "";
	for (int i = 0; i < 4; i++)
	{
		if (Network[i] < 100) Sdvig += " ";
		if (Network[i] < 9) Sdvig += " ";
	}
	printf_s("Network:   %d.%d.%d.%d%s %s.%s.%s.%s\n", Network[0], Network[1], Network[2], Network[3], Sdvig.c_str(),bin(Network[0]).c_str(), bin(Network[1]).c_str(), bin(Network[2]).c_str(), bin(Network[3]).c_str());
	Sdvig = "";
	for (int i = 0; i < 4; i++)
	{
		if (HostMin[i] < 100) Sdvig += " ";
		if (HostMin[i] < 9) Sdvig += " ";
	}
	printf_s("Hostmin:   %d.%d.%d.%d%s %s.%s.%s.%s\n", HostMin[0], HostMin[1], HostMin[2], HostMin[3], Sdvig.c_str(),bin(HostMin[0]).c_str(), bin(HostMin[1]).c_str(), bin(HostMin[2]).c_str(), bin(HostMin[3]).c_str());
	Sdvig = "";
	for (int i = 0; i < 4; i++)
	{
		if (HostMax[i] < 100) Sdvig += " ";
		if (HostMax[i] < 9) Sdvig += " ";
	}
	printf_s("Hostmax:   %d.%d.%d.%d%s %s.%s.%s.%s\n", HostMax[0], HostMax[1], HostMax[2], HostMax[3], Sdvig.c_str(),bin(HostMax[0]).c_str(), bin(HostMax[1]).c_str(), bin(HostMax[2]).c_str(), bin(HostMax[3]).c_str());
	Sdvig = "";
	for (int i = 0; i < 4; i++)
	{
		if (BroadCast[i] < 100) Sdvig += " ";
		if (BroadCast[i] < 9) Sdvig += " ";
	}
	printf_s("Broadcast: %d.%d.%d.%d%s %s.%s.%s.%s\n", BroadCast[0], BroadCast[1], BroadCast[2], BroadCast[3], Sdvig.c_str(),bin(BroadCast[0]).c_str(), bin(BroadCast[1]).c_str(), bin(BroadCast[2]).c_str(), bin(BroadCast[3]).c_str());
	printf_s("Hosts:   %25d                            \n", Hosts);
	FILE* output;
	_mkdir("Info");
	_chdir("Info");
	fopen_s(&output, "IP_Calc.txt", "w");
	Sdvig = "";
	for (int i = 0; i < 4; i++)
	{
		if (IP[i] < 100) Sdvig += " ";
		if (IP[i] < 9) Sdvig += " ";
	}
	fprintf_s(output, "Adress:    %d.%d.%d.%d%s %s.%s.%s.%s\n", IP[0], IP[1], IP[2], IP[3], Sdvig.c_str(), bin(IP[0]).c_str(), bin(IP[1]).c_str(), bin(IP[2]).c_str(), bin(IP[3]).c_str());
	fprintf_s(output, "BitMask: %25d                            \n", BitMask);
	Sdvig = "";
	for (int i = 0; i < 4; i++)
	{
		if (NetMask[i] < 100) Sdvig += " ";
		if (NetMask[i] < 9) Sdvig += " ";
	}
	fprintf_s(output, "NetMask:   %d.%d.%d.%d%s %s.%s.%s.%s\n", NetMask[0], NetMask[1], NetMask[2], NetMask[3], Sdvig.c_str(), bin(NetMask[0]).c_str(), bin(NetMask[1]).c_str(), bin(NetMask[2]).c_str(), bin(NetMask[3]).c_str());

	Sdvig = "";
	for (int i = 0; i < 4; i++)
	{
		if (Network[i] < 100) Sdvig += " ";
		if (Network[i] < 9) Sdvig += " ";
	}
	fprintf_s(output,"Network:   %d.%d.%d.%d%s %s.%s.%s.%s\n", Network[0], Network[1], Network[2], Network[3], Sdvig.c_str(),bin(Network[0]).c_str(), bin(Network[1]).c_str(), bin(Network[2]).c_str(), bin(Network[3]).c_str());
	Sdvig = "";
	for (int i = 0; i < 4; i++)
	{
		if (HostMin[i] < 100) Sdvig += " ";
		if (HostMin[i] < 9) Sdvig += " ";
	}
	fprintf_s(output,"Hostmin:   %d.%d.%d.%d%s %s.%s.%s.%s\n", HostMin[0], HostMin[1], HostMin[2], HostMin[3], Sdvig.c_str(),bin(HostMin[0]).c_str(), bin(HostMin[1]).c_str(), bin(HostMin[2]).c_str(), bin(HostMin[3]).c_str());
	Sdvig = "";
	for (int i = 0; i < 4; i++)
	{
		if (HostMax[i] < 100) Sdvig += " ";
		if (HostMax[i] < 9) Sdvig += " ";
	}
	fprintf_s(output,"Hostmax:   %d.%d.%d.%d%s %s.%s.%s.%s\n", HostMax[0], HostMax[1], HostMax[2], HostMax[3], Sdvig.c_str(),bin(HostMax[0]).c_str(), bin(HostMax[1]).c_str(), bin(HostMax[2]).c_str(), bin(HostMax[3]).c_str());
	Sdvig = "";
	for (int i = 0; i < 4; i++)
	{
		if (BroadCast[i] < 100) Sdvig += " ";
		if (BroadCast[i] < 9) Sdvig += " ";
	}
	fprintf_s(output,"Broadcast: %d.%d.%d.%d%s %s.%s.%s.%s\n", BroadCast[0], BroadCast[1], BroadCast[2], BroadCast[3], Sdvig.c_str(),bin(BroadCast[0]).c_str(), bin(BroadCast[1]).c_str(), bin(BroadCast[2]).c_str(), bin(BroadCast[3]).c_str());
	fprintf_s(output,"Hosts:   %25d                            \n", Hosts);
	fclose(output);
	_chdir("..");
}

int IP_Adress::GetHosts() const
{
	return Hosts;
}

void IP_Adress::Make(const IP_Adress& obj, const int Size)
{
	for (int i = 0; i < 4; i++) IP[i] = obj.BroadCast[i];
	IP[3]++;
	BitMask = 32 - int(log10(Size + 2 + 1) / log10(2));
	int Help = BitMask, i = 0;
	while (Help >= 8)
	{
		NetMask[i] = 255;
		Help -= 8;
		i++;
	}
	if (Help > 0) NetMask[i] = 0;
	while (Help > 0)
	{
		NetMask[i] += 1 << (8 - Help);
		Help--;
	}
	Start();
}

void IP_Adress::Make(const int Size, const IP_Adress& obj)
{
	for (int i = 0; i < 4; i++) IP[i] = obj.IP[i];
	BitMask = 32 - int(log10(Size+2 + 1) / log10(2));
	int Help = BitMask, i = 0;
	while (Help >= 8)
	{
		NetMask[i] = 255;
		Help -= 8;
		i++;
	}
	if (Help > 0) NetMask[i] = 0;
	while (Help > 0)
	{
		NetMask[i] += 1 << (8 - Help);
		Help--;
	}
	Start();
}