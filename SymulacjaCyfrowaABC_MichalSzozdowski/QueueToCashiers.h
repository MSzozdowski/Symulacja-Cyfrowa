#pragma once
#include "GroupOfClients.h"

#include <queue>

using namespace std;

class QueueToCashiers
{
public:
	queue <GroupOfClients*> queue_to_cashiers_;//kolejka klientow do kasjerow
	
	void add_on_cashiers_queue(GroupOfClients* group_of_clients);//funkcja dodajaca podanego za argument klienta na poczatek kolejki do kasjerow
	bool if_queue_to_cashiers_is_empty();//funkcja sprawdzajaca czy kolejka do kasjerow jest pusta 
	int length_of_cashiers();//funkcja zwracajaca dlugosc kolejki do bufetu
	void pop_from_queue_to_cashiers();//funkcja sciagajaca pierwszego klienta z kolejki do kasjerow
	GroupOfClients* take_from_queue_to_cashiers();//funkcja zwracajaca wskaznik na pierwszego klienta w kolejce do kasjerow
};


