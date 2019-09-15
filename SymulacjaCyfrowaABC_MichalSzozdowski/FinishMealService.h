#pragma once
#include "Waiter.h"

#include <queue>

using namespace std;

class FinishMealService
{
public:
	void execute(Waiter* waiter, queue<GroupOfClients*>* queue_to_consumption ,double global_time);
};
