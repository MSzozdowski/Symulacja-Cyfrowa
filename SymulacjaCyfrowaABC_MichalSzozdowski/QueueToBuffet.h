#pragma once
#include "GroupOfClients.h"

#include <queue>

using namespace std;

class QueueToBuffet
{
public:
	queue<GroupOfClients*> queue_to_buffet_; //kolejka klientow do bufetu
	
	void add_on_buffet_queue(GroupOfClients* group_of_clients);//funkcja dodajaca podanego za argument klienta na poczatek kolejki do bufetu
	bool is_queue_to_buffet_empty();//funkcja sprawdzajaca czy kolejka do bufetu jest pusta
	int length_of_queue_to_buffet();//funkcja zwracajaca dlugosc kolejki do bufetu
	void pop_clients_from_queue_to_buffet();//funkcja sciagajaca pierwszego klienta z kolejki do buffetu
	int size_of_first_group_in_buffet_queue();//funkcja zwracajaca rozmiar pierwszej grupy klientow w kolejce do bufetu
	GroupOfClients* take_clients_from_queue_to_buffet();//funkcja zwracajaca wskaznik na pierwszego klienta w kolejce do bufetu
};


