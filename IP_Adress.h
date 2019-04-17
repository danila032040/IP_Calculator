#pragma once
#include <string>
using namespace std;
class IP_Adress
{
private:
	int IP[4];
	int BitMask;
	int NetMask[4];
	int Network[4];
	int BroadCast[4];
	int HostMin[4];
	int HostMax[4];
	int Hosts;
	string bin(int);
public:
	IP_Adress();
	int CinIP();
	int CinMask();
	void Start();
	void PrintMainInfo();
	void PrintInfo();
	~IP_Adress();
};

