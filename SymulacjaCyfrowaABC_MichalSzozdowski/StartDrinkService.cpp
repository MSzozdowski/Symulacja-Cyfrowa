#include "StartDrinkService.h"
#include "EventList.h"

#include <iostream>
#include <vector>
#include <queue>


using namespace std;

void StartDrinkService::execute(vector<EventList>* event_list, queue<GroupOfClients*>* helper_queue_to_waiters_drink, vector<Waiter*> waiter, const int position, double global_time)
{
	GroupOfClients* actual_group = helper_queue_to_waiters_drink->front();
	helper_queue_to_waiters_drink->pop();
	waiter[position]->actual_group_ = actual_group;

	cout << "Klient o id: " << actual_group->client_group_id_ << " i licznosci grupy: " << actual_group->size_of_client_group_ << " rozpoczal obsluge u kelnera o czasie " << global_time << " i czeka na wydanie napoju." << endl;
	
	EventList current_event;
	current_event.step_ = 5;
	current_event.time_ = actual_group->time_drink_ + global_time;
	current_event.waiter_ = waiter[position];
	actual_group->time_drink_ = current_event.time_;
	event_list->push_back(current_event);
}
