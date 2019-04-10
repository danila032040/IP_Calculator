#pragma once

class IP_Adress
{
private:
	int IP[4];
	int NetMask[4];
	int HostMin[4];
	int HostMax[4];
	int Network[4];
	int BroadCast[4];
	int BitMask;
	int Hosts;
public:
	IP_Adress();
	void CinIP();
	void CinMask();
	void Start();
	~IP_Adress();
};

