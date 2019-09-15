#include "AlarmGenerator.h"
#include "EventList.h"

#include <iostream>

using namespace  std;

void AlarmGenerator::execute(vector<GroupOfClients*>* to_alarm, double global_time, Restaurant* restaurant, queue<GroupOfClients*>* helper_queue_drink, queue<GroupOfClients*>* helper_queue_meal, queue<GroupOfClients*>* queue_to_consumption)
{
	for(int j=0;j<to_alarm->size();j++)
	{
		GroupOfClients* group = to_alarm->at(j);
		cout << "Klient o id: " << group->client_group_id_ << " i licznosci grupy " << group->size_of_client_group_ << " wyszedl z restauracji na skutek alarmu o czasie " << global_time << "." << endl;

		for(auto i=0;i<restaurant->buffet_->sitting_.size();i++)//zwolnienie miejsc w bufecie jesli klient w czasie dzwonka alarmu byl w bufecie
		{
			if(restaurant->buffet_->sitting_[i]!=nullptr)
			{
				if(restaurant->buffet_->sitting_[i]->client_group_id_==group->client_group_id_)
				{
					restaurant->buffet_->sitting_[i] = nullptr;
					--restaurant->buffet_->busy_places_in_buffet_;
				}
			}
		}
		
		for(auto i=0;i<restaurant->cashiers_.size();i++)//zwolnienie miejsc u kasjera jesli klient w czasie dzwonka alarmu byl u kasjera
		{
			if(restaurant->cashiers_[i]->actual_group_!=nullptr)
			{
				if(restaurant->cashiers_[i]->actual_group_->client_group_id_==group->client_group_id_)
				{
					restaurant->cashiers_[i]->actual_group_ = nullptr;
				}
			}
		}

		for(auto i=0;i<restaurant->queue_to_buffet_->length_of_queue_to_buffet();i++)//opuszczenie kolejki do bufetu jesli klient w czasie dzwonka alarmu byl w kolejce do bufetu
		{
			GroupOfClients* in_queue = restaurant->queue_to_buffet_->take_clients_from_queue_to_buffet();
			restaurant->queue_to_buffet_->pop_clients_from_queue_to_buffet();
			if (in_queue->client_group_id_ != group->client_group_id_)
			{
				restaurant->queue_to_buffet_->add_on_buffet_queue(in_queue);
			}		
		}

		for (auto i = 0; i < restaurant->queue_to_table_->length_of_tables(); i++)//opuszczenie kolejki do stolikow jesli klient w czasie dzwonka alarmu byl w kolejce do stolikow
		{
			GroupOfClients* in_queue = restaurant->queue_to_table_->take_from_queue_to_table();
			restaurant->queue_to_table_->pop_from_queue_to_table();
			if (in_queue->client_group_id_ != group->client_group_id_)
			{
				restaurant->queue_to_table_->add_on_table_queue(in_queue);
			}
		}

		for(auto i=0;i<restaurant->queue_to_cashiers_->length_of_cashiers();i++)//opuszczenie kolejki do kasjerow jesli klient w czasie dzwonka alarmu byl w kolejce do kasjerow
		{
			GroupOfClients* in_queue = restaurant->queue_to_cashiers_->take_from_queue_to_cashiers();
			restaurant->queue_to_cashiers_->pop_from_queue_to_cashiers();
			if(in_queue->client_group_id_!=group->client_group_id_)
			{
				restaurant->queue_to_cashiers_->add_on_cashiers_queue(in_queue);
			}
		}

		if(restaurant->manager_->actual_group_!=nullptr)//zwolnienie kierownika jesli klient w trakcie alarmu byl u kierownika
		{
			if (restaurant->manager_->actual_group_->client_group_id_ == group->client_group_id_)
			{
				restaurant->manager_->actual_group_ = nullptr;
				restaurant->manager_->busy_manager_ = false;
			}
		}
		
		for(auto  i=0; i<restaurant->tables_.size(); i++)//zwolnienie stolika jesli klient w trakcie alarmu byl przy stoliku
		{
			if(restaurant->tables_[i]->actual_client_!=nullptr)
			{
				if (restaurant->tables_[i]->actual_client_->client_group_id_ == group->client_group_id_)
				{
					restaurant->tables_[i]->actual_client_ = nullptr;
				}
			}	
		}

		for(auto i=0; i<helper_queue_drink->size(); i++)//opuszczenie kolejki oczekiwania na napoj jesli w trakcie alarmu klient byl w kolejce oczekiwania na napoj
		{
			GroupOfClients* in_queue = helper_queue_drink->front();
			helper_queue_drink->pop();
			if(in_queue->client_group_id_!=group->client_group_id_)
			{
				helper_queue_drink->push(in_queue);
			}
		}
		
		for (auto i = 0; i < helper_queue_meal->size(); i++)//opuszczenie kolejki oczekiwania na danie glowne jesli w trakcie alarmu klient byl w kolejce oczekiwania na danie
		{
			GroupOfClients* in_queue = helper_queue_meal->front();
			helper_queue_meal->pop();
			if (in_queue->client_group_id_ != group->client_group_id_)
			{
				helper_queue_meal->push(in_queue);
			}
		}
		
		for (auto i = 0; i < queue_to_consumption->size(); i++)//opuszczenie kolejki oczekiwania na konsumpcje jesli w trakcie alarmu klient byl w kolejce oczekiwania na konsumpcje
		{
			GroupOfClients* in_queue = queue_to_consumption->front();
			queue_to_consumption->pop();
			if (in_queue->client_group_id_ != group->client_group_id_)
			{
				queue_to_consumption->push(in_queue);
			}
		}

		for(auto i=0;i<restaurant->waiters_.size();i++)//zwolnienie kelnera jesli klient w trakcie alarmu byl w trakcie obslugi przez kelnera
		{
			if(restaurant->waiters_[i]->actual_group_!=nullptr)
			{
				if (restaurant->waiters_[i]->actual_group_->client_group_id_ == group->client_group_id_)
				{
					restaurant->waiters_[i]->actual_group_ = nullptr;
				}
			}	
		}
		delete group;
	}
	to_alarm->clear();

	
}
