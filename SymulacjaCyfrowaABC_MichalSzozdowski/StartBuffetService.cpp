#include "StartBuffetService.h"
#include <iostream>

using namespace std;

void StartBuffetService::execute(vector<EventList>* event_list, Buffet* buffet, QueueToBuffet* queue_to_buffet, double global_time)
{
	GroupOfClients* actual_group=queue_to_buffet->take_clients_from_queue_to_buffet();
	const bool are_sitting=buffet->sitting_in(actual_group);

	if (are_sitting)
	{
		cout << "Klient do bufetu o id: " << actual_group->client_group_id_ << " o licznosci grupy: " << actual_group->size_of_client_group_ << " zasiadl przy bufecie o czasie " << global_time <<"."<< endl;
		EventList current_event;
		current_event.step_ = 2;
		current_event.time_ = actual_group->time_buffet_ + global_time;
		actual_group->time_buffet_ = current_event.time_; 
		event_list->push_back(current_event);
		queue_to_buffet->pop_clients_from_queue_to_buffet();
	}
}
