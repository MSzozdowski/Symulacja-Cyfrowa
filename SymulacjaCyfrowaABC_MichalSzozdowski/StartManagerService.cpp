#include "StartManagerService.h"

#include <vector>
#include <iostream>

using namespace std;

void StartManagerService::execute(std::vector<EventList>* event_list, Manager* manager, vector<Table*> tables, QueueToTable* queue_to_table, double global_time)
{
	int max_group_size=0;
	GroupOfClients* selected_group = nullptr;
	int max_table_size=0;
	bool do_not_look_for_anymore = false;
	
	for(int i=0;i<tables.size();i++)
	{
		if(max_table_size<(tables[i]->size_of_table_) && tables[i]->actual_client_==nullptr)
		{
			max_table_size = tables[i]->size_of_table_;
		}		
	}
	
	for(int i=0;i<queue_to_table->length_of_tables();i++)
	{
		GroupOfClients* actual_clients = queue_to_table->take_from_queue_to_table();
		queue_to_table->pop_from_queue_to_table();
		int temp= actual_clients->size_of_client_group_;
		
		if (max_group_size < temp && temp <= max_table_size)
		{
			max_group_size = temp;	
		}
		queue_to_table->add_on_table_queue(actual_clients);
	}
	
	for (int i = 0; i < queue_to_table->length_of_tables(); i++)
	{
		GroupOfClients* actual_clients = queue_to_table->take_from_queue_to_table();
		queue_to_table->pop_from_queue_to_table();
		int temp = actual_clients->size_of_client_group_;
		
		if (max_group_size == temp && do_not_look_for_anymore==false)
		{
			selected_group = actual_clients;
			do_not_look_for_anymore = true;
		}
		else
		{
			queue_to_table->add_on_table_queue(actual_clients);
		}
	}
	if (selected_group != nullptr && max_table_size>=selected_group->size_of_client_group_) {
		manager->busy_manager_ = true;
		manager->actual_group_ = selected_group;
		cout << "Klient o id: " << selected_group->client_group_id_ << " i licznosci grupy: " << selected_group->size_of_client_group_ << " jest prowadzony przez managera do stolika o czasie " << global_time << "." << endl;
		EventList current_event;
		current_event.step_ = 4;
		current_event.time_ = selected_group->time_manager_ + global_time;
		selected_group->time_manager_ = current_event.time_;
		event_list->push_back(current_event);
	}
}
