#pragma once
#include "GroupOfClients.h"

class Waiter
{
public:
	GroupOfClients* actual_group_; //wskaznik na aktualna grupe klientow
	
	Waiter()
	{
		actual_group_ = nullptr;
	}
};

