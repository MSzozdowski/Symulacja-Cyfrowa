#include "StartConsumption.h"
#include "Table.h"

#include <iostream>

using namespace std;

void StartConsumption::execute(vector<EventList>* event_list, queue<GroupOfClients*>* helper_queue_to_consumption, vector<Table*> table,double global_time)
{
	GroupOfClients* actual_client = helper_queue_to_consumption->front();
	helper_queue_to_consumption->pop();
	Table* owned_table=nullptr;
	for(auto i = 0; i < table.size(); i++)
	{
		if(table[i]->actual_client_!=nullptr)
		{
			if(table[i]->actual_client_->client_group_id_==actual_client->client_group_id_)
			{
				owned_table = table[i];
				break;
			}
		}
	}
	if(owned_table!=nullptr)
	{
		cout << "Klient o id: " << actual_client->client_group_id_ << " i licznosci grupy: " << actual_client->size_of_client_group_ << " rozpoczal konsumpcje o czasie " << global_time << "." << endl;
		EventList current_event;
		current_event.step_ = 7;
		current_event.time_ = actual_client->time_consumption_ + global_time;
		current_event.table_ = owned_table;
		actual_client->time_consumption_ = current_event.time_;
		event_list->push_back(current_event);
	}
	
}
