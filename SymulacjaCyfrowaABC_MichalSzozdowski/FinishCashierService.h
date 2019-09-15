#pragma once
#include "Cashier.h"
#include "QueueToCashiers.h"

#include <vector>

using namespace std;

class FinishCashierService
{
public:
	void execute( vector<Cashier*> cashiers,double global_time,int position, vector<GroupOfClients*>* to_alarm);
};

