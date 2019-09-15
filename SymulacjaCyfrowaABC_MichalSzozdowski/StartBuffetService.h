#pragma once
#include "EventList.h"
#include "Buffet.h"
#include "QueueToBuffet.h"

#include <vector>

using namespace  std;

class StartBuffetService
{
public:
	void execute(vector<EventList>* event_list,Buffet* buffet,QueueToBuffet* queue_to_buffet,double global_time);
};

