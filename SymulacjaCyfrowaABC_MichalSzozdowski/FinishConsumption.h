#pragma once
#include "Table.h"
#include "QueueToCashiers.h"

#include <queue>

using namespace std;

class FinishConsumption
{
public:
	void execute(Table* table, QueueToCashiers* queue_to_cashiers,double global_time);
};
