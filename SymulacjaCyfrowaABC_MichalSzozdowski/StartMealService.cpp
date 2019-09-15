#include "StartMealService.h"
#include <iostream>
using namespace std;
void StartMealService::execute(vector<EventList>* event_list, queue<GroupOfClients*>* helper_queue_to_waiters_meal, vector<Waiter*> waiter, const int position, double global_time)
{
	GroupOfClients* actual_group = helper_queue_to_waiters_meal->front();
	helper_queue_to_waiters_meal->pop();
	waiter[position]->actual_group_ = actual_group;
	cout << "Klient o id: " << actual_group->client_group_id_ << " i licznosci grupy: " << actual_group->size_of_client_group_ << " czeka na wydanie dania glownego przez kelnera o czasie " << global_time<<"." << endl;
	EventList current_event;
	current_event.step_ = 6;
	current_event.time_ = actual_group->time_meal_ + global_time;
	current_event.waiter_ = waiter[position];
	actual_group->time_meal_ = current_event.time_;
	event_list->push_back(current_event);
}
