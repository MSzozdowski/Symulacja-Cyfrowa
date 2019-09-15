#pragma once
#include "EventList.h"
#include "Restaurant.h"

#include <vector>

class AlarmGenerator
{
public:
	static void execute(vector<GroupOfClients*>* to_alarm, double global_time, Restaurant* restaurant, queue<GroupOfClients*>* helper_queue_drink, queue<GroupOfClients*>* helper_queue_meal, queue<GroupOfClients*>* queue_to_consumption);
};

