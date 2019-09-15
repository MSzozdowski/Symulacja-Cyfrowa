#pragma once
#include "EventList.h"
#include "QueueToCashiers.h"
#include "Cashier.h"

#include <vector>
using namespace std;

class StartCashierService
{
public:
	void execute(vector<EventList>* event_list, QueueToCashiers* queue_to_cashiers,vector<Cashier*> cashier,int which_cashier, double global_time);
};

