#include "FinishManagerService.h"

#include <iostream>
#include <vector>

using namespace std;

void FinishManagerService::execute(Manager* manager, vector<Table*> table, queue<GroupOfClients*>* helper_queue_to_waiters,double global_time, vector<int>* helper_id, vector<double>* helper_time)
{
	if (manager->actual_group_ != nullptr)
	{
		GroupOfClients* actual_client = manager->actual_group_;
		Table* selected_table = nullptr;
		const int size = actual_client->size_of_client_group_;

		for (auto i=0; i<table.size();i++)
		{
			if (actual_client->size_of_client_group_==table[i]->size_of_table_ && table[i]->actual_client_==nullptr)
			{
				table[i]->actual_client_ = actual_client;
				selected_table = table[i];
				break;
			}
		}

		if (selected_table == nullptr)
		{
			for (auto i=0;i<table.size();i++)
			{
				if (size+1==table[i]->size_of_table_ && table[i]->actual_client_==nullptr)
				{
					table[i]->actual_client_ = actual_client;
					selected_table = table[i];
					break;
				}
			}
		}

		if (selected_table == nullptr)
		{
			for (auto i=0;i<table.size();i++)
			{
				if (size+2==table[i]->size_of_table_ && table[i]->actual_client_==nullptr)
				{
					table[i]->actual_client_ = actual_client;
					selected_table = table[i];
					break;
				}
			}
		}

		if (selected_table == nullptr)
		{
			for (auto i=0; i<table.size();i++)
			{
				if (size+3==table[i]->size_of_table_ && table[i]->actual_client_==nullptr)
				{
					table[i]->actual_client_ = actual_client;
					selected_table = table[i];
					break;
				}
			}
		}

		if (selected_table != nullptr)
		{
			cout << "Klient o id: " << actual_client->client_group_id_ << " w grupie o licznosci: " << actual_client->size_of_client_group_ << " usiadl przy stoliku " << selected_table->size_of_table_ << "-osobowym o czasie " << global_time << "." << endl;
			manager->actual_group_ = nullptr;
			manager->busy_manager_ = false;
			helper_queue_to_waiters->push(actual_client);
			helper_id->push_back(actual_client->client_group_id_);
			helper_time->push_back(global_time);
		}
	}
}
