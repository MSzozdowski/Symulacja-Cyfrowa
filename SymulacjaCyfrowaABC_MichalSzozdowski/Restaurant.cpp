#include "Restaurant.h"


int Restaurant::which_cashier_free()
{
	for(auto i=0;i<cashiers_.size();i++)
	{
		if (cashiers_[i]->if_cashier_free())
			return i;
	}
	return 1000;
}

bool Restaurant::if_possible_to_sit()
{
	int max_group_size = 0;
	GroupOfClients* selected_group = nullptr;
	int max_table_size = 0;
	bool do_not_look_for_anymore = false;
	for (auto i = 0; i < tables_.size(); i++)
	{
		if (max_table_size < (tables_[i]->size_of_table_) && tables_[i]->actual_client_ == nullptr)
		{
			max_table_size = tables_[i]->size_of_table_;
		}
	}

	for (auto i = 0; i < queue_to_table_->length_of_tables(); i++)
	{
		GroupOfClients* actual_clients = queue_to_table_->take_from_queue_to_table();
		queue_to_table_->pop_from_queue_to_table();
		int temp = actual_clients->size_of_client_group_;

		if (max_group_size < temp && temp <= max_table_size)
		{
			max_group_size = temp;
		}
		queue_to_table_->add_on_table_queue(actual_clients);
	}

	for (auto i = 0; i < queue_to_table_->length_of_tables(); i++)
	{
		GroupOfClients* actual_clients = queue_to_table_->take_from_queue_to_table();
		queue_to_table_->pop_from_queue_to_table();
		int temp = actual_clients->size_of_client_group_;

		if (max_group_size == temp && do_not_look_for_anymore == false)
		{
			selected_group = actual_clients;
			do_not_look_for_anymore = true;
		}
		queue_to_table_->add_on_table_queue(actual_clients);
	}
	
	if(selected_group!=nullptr && max_table_size >= selected_group->size_of_client_group_ && max_table_size>0)
	{
		return true;
	}
	else
	{
		return false;
	}	
}

int Restaurant::which_waiter_free()
{
	for (auto i = 0; i < waiters_.size(); i++)
	{
		if (waiters_[i]->actual_group_==nullptr)
			return i;
	}
	return 1000;
}
