#pragma once
#include "GroupOfClients.h"

#include <queue>

using namespace std;
 
class QueueToTable
{
public:
	queue<GroupOfClients*> queue_to_table_;//kolejka klientow do stolikow
	
	void add_on_table_queue(GroupOfClients* group_of_clients);//funkcja dodajaca podanego za argument klienta na poczatek kolejki do stolikow
	bool is_queue_to_table_empty();//funkcja sprawdzajaca czy kolejka do stolikow jest pusta  
	int length_of_tables();//funkcja zwracajaca dlugosc kolejki do stolikow
	void pop_from_queue_to_table();//funkcja sciagajaca pierwszego klienta z kolejki do stolikow
	GroupOfClients* take_from_queue_to_table();//funkcja zwracajaca wskaznik na pierwszego klientaw kolejce do stolikow
};


