#include "StartCashierService.h"

#include <iostream>

using namespace std;

void StartCashierService::execute(vector<EventList>* event_list, QueueToCashiers* queue_to_cashiers, vector<Cashier*> cashier, const int which_cashier, double global_time)
{
	GroupOfClients* actual_client= queue_to_cashiers->take_from_queue_to_cashiers();
	cashier[which_cashier]->make_cashier_busy(actual_client);
	queue_to_cashiers->pop_from_queue_to_cashiers();

	cout << "Klient o id: " << actual_client->client_group_id_ << " i licznosci grupy: " << actual_client->size_of_client_group_ << " rozpoczal obsluge u kasjerow o czasie " << global_time << "." << endl;
	
	EventList current_event;
	current_event.step_ = 3;
	current_event.time_ = actual_client->time_cashier_ + global_time;
	actual_client->time_cashier_ = current_event.time_;
	event_list->push_back(current_event);	
}
