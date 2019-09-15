#include "Buffet.h"
#include <iostream>

using namespace std;

bool Buffet::sitting_in(GroupOfClients* group_of_clients)
{
	auto size_of_group=group_of_clients->size_of_client_group_;
	for(auto i=0;i<size_of_buffet_;i++)
	{
		if(sitting_[i]==nullptr && size_of_group!=0)
		{
			sitting_[i] = group_of_clients;
			size_of_group--;
		}
			
	}
	
	if (size_of_group == 0)
	{
		busy_places_in_buffet_ = busy_places_in_buffet_ + group_of_clients->size_of_client_group_;
		return true;
	}
	else
	{
		return false;
	}
}

GroupOfClients* Buffet::sitting_out(int position)
{
	int id = sitting_[position]->client_group_id_;
	int size_of_group = sitting_[position]->size_of_client_group_;
	GroupOfClients* group_of_clients = sitting_[position];
	
	for (int i = 0; i < size_of_buffet_; i++)
	{
		if(sitting_[i]!=nullptr)
		{
			if (sitting_[i]->client_group_id_ == id && size_of_group > 0)
			{
				sitting_[i] = nullptr;
				size_of_group--;
			}
			if (size_of_group == 0)
			{
				busy_places_in_buffet_ = busy_places_in_buffet_ - group_of_clients->size_of_client_group_;
				break;
			}
		}
		
	}
	return group_of_clients;
}


