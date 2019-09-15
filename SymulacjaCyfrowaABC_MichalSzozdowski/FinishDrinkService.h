#pragma once
#include "Waiter.h"

#include <queue>

using namespace std;

class FinishDrinkService
{
public:
	void execute(Waiter* waiter, queue<GroupOfClients*>* helper_queue_to_waiters_meal,double global_time);
};

