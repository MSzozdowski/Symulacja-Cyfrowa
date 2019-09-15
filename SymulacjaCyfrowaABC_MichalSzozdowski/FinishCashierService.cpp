#include "FinishCashierService.h"

#include <iostream>

using namespace std;

void FinishCashierService::execute( vector<Cashier*> cashiers, double global_time, int position, vector<GroupOfClients*>* to_alarm)
{
	GroupOfClients* actual_group = cashiers[position]->actual_group_;
	cashiers[position]->make_cashier_free();
	cout << "Klient o id: " << actual_group->client_group_id_ << " w grupie o licznosci: " << actual_group->size_of_client_group_ << " zakonczyl obsluge u kasjerow i wyszedl z restauracji o czasie " << global_time << "." << endl;
	for (int i = 0; i < to_alarm->size(); i++)
	{
		if (actual_group->client_group_id_ == to_alarm->at(i)->client_group_id_)
		{
			to_alarm->erase(to_alarm->begin() + i);
		}
	}
	delete actual_group;
}
