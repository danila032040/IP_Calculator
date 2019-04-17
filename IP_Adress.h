#pragma once
#include <string>
using namespace std;
class IP_Adress
{
private:
	unsigned short IP[4];
	unsigned short BitMask;
	unsigned short NetMask[4];
	unsigned short Network[4];
	unsigned short BroadCast[4];
	unsigned short HostMin[4];
	unsigned short HostMax[4];
	int Hosts;
	string bin(int);
public:
	IP_Adress();
	int CinIP();
	int CinMask();
	void Start();
	void PrintMainInfo();
	void PrintOtherInfo();
	void PrintInfo();
	int GetHosts() const;
	~IP_Adress();
};

