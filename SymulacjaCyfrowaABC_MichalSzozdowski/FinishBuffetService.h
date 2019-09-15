#pragma once
#include "QueueToCashiers.h"
#include "Buffet.h"

class FinishBuffetService
{
public:
	void execute(Buffet* buffet, QueueToCashiers* queue_to_cashiers,double global_time,int position_in_buffet);
};

