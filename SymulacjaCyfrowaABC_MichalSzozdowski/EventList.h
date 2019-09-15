#pragma once

#include "Waiter.h"
#include "Table.h"

class EventList
{
public:
	int step_; // okresla sposob obslugi zdarzenia
	double time_; // czas trwania zdarzenia
	Waiter* waiter_;//kelner przypisany do obslugi danego zdarzenia
	Table* table_;//stolik przypisany do obslugi danego zdarzenia
	
	EventList(const int step=0, const int time=0)
	{
		step_ = step;
		time_ = time;
		waiter_ = nullptr;
		table_ = nullptr;
	}

};

