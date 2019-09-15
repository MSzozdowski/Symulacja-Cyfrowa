#pragma once
#include "GroupOfClients.h"

class Manager
{
public:
	bool busy_manager_; //flaga dostepnosci managera
	GroupOfClients* actual_group_;//aktualnie obslugiwana grupa

	Manager()
	{
		busy_manager_ = false;
		actual_group_ = nullptr;
	}
	
};

