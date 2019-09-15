#pragma once
#include "Waiter.h"
#include "EventList.h"

#include <vector>
#include <queue>

using namespace std;
class StartMealService
{
public:
	void execute(vector<EventList>* event_list, queue<GroupOfClients*>* helper_queue_to_waiters_meal, vector<Waiter*> waiter, int position, double global_time);
};

