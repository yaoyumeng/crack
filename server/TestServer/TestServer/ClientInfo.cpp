#include "ClientInfo.h"

#include <string.h>

CClientInfo::CClientInfo(void)
{
	m_clientsock = -1;
	memset(m_osinfo,0,16);
	memset(m_ip,0,20);
	memset(m_hostname,0,50);
	memset(m_guid,0,40);
	m_type = -1;

}

CClientInfo::~CClientInfo(void)
{
}
