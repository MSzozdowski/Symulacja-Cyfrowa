#pragma once

#include "EventList.h"
#include "QueueToTable.h"
#include "QueueToBuffet.h"
#include "GroupOfClients.h"

#include <random>
#include <iostream>

using namespace std;

class GenerateNewClients
{
public:
	GroupOfClients* group_of_clients_;
	double new_clients_group_time_;
	double time_in_buffet_;
	double time_in_cashier_;
	double time_drink_;
	double time_meal_;
	double time_consumption_;
	double time_manager_ = 40.0;
	
	default_random_engine generator;
	normal_distribution<double> distribution_of_appear_=normal_distribution<double>(350.0, 50.0);
	normal_distribution<double> distribution_time_in_buffet_ = normal_distribution<double>(2900.0, 80.0); 
	exponential_distribution<double> distribution_in_cashier_ = exponential_distribution<double>(1 / 2500.0);
	exponential_distribution<double> distribution_in_drink_ = exponential_distribution<double>(1 / 2500.0);
	exponential_distribution<double> distribution_in_meal_ = exponential_distribution<double>(1 /2500.0);
	exponential_distribution<double> distribution_in_consumption_ = exponential_distribution<double>(1 / 2020.0); 

	void execute(vector<EventList>* event_list, QueueToTable* queue_to_table, QueueToBuffet* queue_to_buffet, int id_i,double global_t,vector<GroupOfClients*>* to_alarm,vector<int>* helper_id, vector<double>* helper_time_table);
};


