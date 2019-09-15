#pragma once
#include "Table.h"
#include "Manager.h"

#include <vector>
#include <queue>

using namespace std;

class FinishManagerService
{
public:
	void execute(Manager* manager, vector<Table*> table, queue<GroupOfClients*>* helper_queue_to_waiters , double global_time,vector<int>* helper_id,vector<double>* helper_time);
};

