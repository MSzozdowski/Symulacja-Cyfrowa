#pragma once

#include "GroupOfClients.h"
#include "QueueToCashiers.h"

using namespace std;

class Cashier {
public:
	GroupOfClients* actual_group_; //wskaznik na aktualna grupe klientow

	Cashier()
	{
		actual_group_ = nullptr;
	}
	
	bool if_cashier_free();//funkcja zwraca wartosc true jesli kasjer jest wolny
	void make_cashier_busy(GroupOfClients* group);//funkcja przydzilajaca kasjerowi grupe klientow podana w argumencie
	void make_cashier_free();//funkcja zwalniajaca kasjera
};

