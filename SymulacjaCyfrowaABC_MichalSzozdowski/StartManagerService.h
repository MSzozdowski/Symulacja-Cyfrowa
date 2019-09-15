#pragma once
#include "EventList.h"
#include "Manager.h"
#include "QueueToTable.h"

#include <vector>
#include "Table.h"

class StartManagerService
{
public:
	void execute(vector<EventList>* event_list, Manager* manager, vector<Table*> tables, QueueToTable* queue_to_table,double global_time);
};
