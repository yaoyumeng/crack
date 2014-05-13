#pragma once

#include "sqlite3.h"
#include <stdio.h>
#include "CLog.h"
#include "CppSQLite3.h"
#include "CrackBroker.h"
#include "CompClient.h"


class CPersistencManager
{
public:
	CPersistencManager(char *pDB);
	~CPersistencManager(void);

	int CreateTable();


	int PersistTaskMap(CT_MAP task_map);
	int PersistHash(CT_MAP task_map);
	int PersistBlockMap(CB_MAP block_map);

	int PersistReadyTaskQueue(CT_DEQUE ready_list);
	int PersistClientInfo(CI_VECTOR client_list);
	int PersistNoticeMap(CCB_MAP notice_map);


	int LoadTaskMap(CT_MAP &task_map);
	int LoadHash(CT_MAP &task_map);
	int LoadBlockMap(CB_MAP &block_map,CT_MAP &task_map);
	int LoadReadyTaskQueue(CT_DEQUE &ready_list,CT_MAP task_map);
	int LoadClientInfo(CI_VECTOR &client_list);
	int LoadNoticeMap(CCB_MAP &notice_map);


private:

	CppSQLite3DB m_SQLite3DB;

	string m_TaskTable;
	string m_BlockTable;
	string m_HashTable;
	string m_NoticeTable ;
	string m_ReadyTaskTable ;
	string m_ClientTable ;


};