#pragma once

#include <time.h>

struct login_info;

class CClientInfo
{
public:
	CClientInfo(void);
	~CClientInfo(void);

	int Init(const void* data, const char* ip, int port, unsigned int sock);

	virtual void SetCPUGPU(int cpu, int gpu){}

public:
	
	char m_osinfo[64];	//操作系统信息
	char m_ip[20];		//IP地址信息

	char m_type;		//客户端类型,control , compute
	
	char m_hostname[64];//主机名称
	unsigned char m_guid[40]; //节点guid
	
	unsigned int m_clientsock;
	int m_port;

	time_t m_keeplivetime;		//最近一次心跳时间
	
	time_t m_logintime;		//登录时间

};
