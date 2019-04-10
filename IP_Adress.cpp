#include "IP_Adress.h"
#include <iostream>
using namespace std;
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
		//TO DO
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

}