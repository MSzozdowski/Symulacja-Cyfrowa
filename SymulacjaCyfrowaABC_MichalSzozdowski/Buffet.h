#pragma once
#include "GroupOfClients.h"
#include "QueueToBuffet.h"

#include <vector>

using namespace std;

class Buffet 
{
public:
	int size_of_buffet_; //calkowita liczba miejsc przy bufecie
	int busy_places_in_buffet_; //liczba zajetych miejsc przy bufecie
	vector <GroupOfClients*> sitting_; // wektor miejsc bufetu

	explicit Buffet(const int size) {
		size_of_buffet_ = size;
		busy_places_in_buffet_ = 0;
		for(int i=0; i<size;i++)
		{
			sitting_.push_back(nullptr);
		}
	}
	
	bool sitting_in(GroupOfClients* group_of_clients);//funkcja "zajmujaca" miejsca w bufecie, zwracajaca wartosc true jesli usadzenie sie powiodlo
	GroupOfClients* sitting_out(int position);//funkcja zwalniajaca miejsca w bufecie i zwracajaca grupe klientow, ktorzy te miejsca zwolnili

};


