#include "GenerateNewClients.h"

#include <vector>
#include <iostream>

using namespace std;

void GenerateNewClients::execute(vector<EventList>* event_list, QueueToTable* queue_to_table, QueueToBuffet* queue_to_buffet,int id_i,double global_t,vector<GroupOfClients*>* to_alarm, vector<int>* helper_id, vector<double>* helper_time_table)
{
	int tab_of_probability[100];//tablica pomocnicza do losowania rozmiaru grupy z zadanym prawdopodobienstwem
	for(int i=0;i<11;i++)
		tab_of_probability[i] = 1;
	for (int i = 11; i < 44; i++)
		tab_of_probability[i] = 2;
	for (int i=44;i<77;i++)
		tab_of_probability[i] = 3;
	for(int i=77;i<100;i++)
		tab_of_probability[i] = 4;

	bool tab_of_probability_alarm[10];//tablica pomocnicza do losowania wrazliwosci na alarm
	for (int i = 0; i < 7; i++)
		tab_of_probability_alarm[i] = false;
	for (int i = 7; i < 10; i++)
		tab_of_probability_alarm[i] = true;

	int tab_seed[10];//tablica przechowujaca wartosci ziaren
	tab_seed[0] = 2000000;
	int seed_helper = 4100000;
	for(int i=1;i<10;i++)
	{
		tab_seed[i] = seed_helper;
		seed_helper += 100000;
	}
	
	generator = default_random_engine(2000000);
	const int size_of_group = tab_of_probability[rand ()% 100];
	const bool sensitivity_on_alarm_ = tab_of_probability_alarm[rand() % 10];
	new_clients_group_time_ = abs(distribution_of_appear_(generator));
	time_in_buffet_ = abs(distribution_time_in_buffet_(generator));
	time_in_cashier_ = abs(distribution_in_cashier_(generator));
	time_drink_ = abs(distribution_in_drink_(generator));
	time_meal_ = abs(distribution_in_meal_(generator));
	time_consumption_ = abs(distribution_in_consumption_(generator));
	const int type_of_client = rand() % 2 ;
	
	if(type_of_client==1)
	{
		group_of_clients_ = new GroupOfClients(id_i, size_of_group, new_clients_group_time_, time_manager_, time_meal_, time_drink_, time_consumption_, time_in_cashier_, sensitivity_on_alarm_);
		queue_to_table->add_on_table_queue(group_of_clients_);
		
		if(sensitivity_on_alarm_)
		{
			to_alarm->push_back(group_of_clients_);
		}
		cout << "Klient do stolika o id: " << id_i << " i licznosci grupy: " << size_of_group << " ustawil sie w kolejce do stolikow o czasie " <<  global_t <<"." <<endl;
		helper_id->push_back(group_of_clients_->client_group_id_);
		helper_time_table->push_back(global_t);
	}
	else if(type_of_client==0)
	{
		group_of_clients_ = new GroupOfClients(id_i, size_of_group, new_clients_group_time_, time_in_buffet_, time_in_cashier_, sensitivity_on_alarm_);
		queue_to_buffet->add_on_buffet_queue(group_of_clients_);
		if (sensitivity_on_alarm_)
		{
			to_alarm->push_back(group_of_clients_);
		}
		cout << "Klient do bufetu o id: " << id_i << " i licznosci grupy: " << size_of_group << " ustawil sie w kolejce do bufetu o czasie "<<  global_t << "." << endl;
	}
	
	EventList current_event;
	current_event.step_ = 1;
	current_event.time_ = new_clients_group_time_+global_t;
	group_of_clients_->time_appear_ = current_event.time_;
	event_list->push_back(current_event);
}
