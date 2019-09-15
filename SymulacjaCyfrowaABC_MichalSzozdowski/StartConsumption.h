#pragma once
#include "EventList.h"
#include "Table.h"

#include <vector>
#include <queue>

using namespace std;

class StartConsumption
{
public:
	void execute(vector<EventList>* event_list, queue<GroupOfClients*>* helper_queue_to_consumption,vector<Table*> table,double global_time);
};

