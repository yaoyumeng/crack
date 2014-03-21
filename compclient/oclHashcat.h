#ifndef __OCLHASHCAT_H__
#define __OCLHASHCAT_H__

#include "Crack.h"
#include <map>
#include <string>

using namespace std;

class oclHashcat : public Crack
{
public:
	oclHashcat(void);
	~oclHashcat(void);
	map<string,string> MapTargetHash;
	static void *MonitorThread(void *p);

	virtual int Launcher(const crack_block* item, bool gpu, unsigned short deviceId);
};

#endif