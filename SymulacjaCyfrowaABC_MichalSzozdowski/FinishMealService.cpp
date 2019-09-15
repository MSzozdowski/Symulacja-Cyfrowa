#include "FinishMealService.h"
#include "Waiter.h"

#include <iostream>

using namespace std;

void FinishMealService::execute(Waiter* waiter, queue<GroupOfClients*>* queue_to_consumption,double global_time)
{
	if(waiter!=nullptr)
	{
		if (waiter->actual_group_ != nullptr && waiter->actual_group_->client_group_id_ > 0)
		{
			cout << "Klient o id: " << waiter->actual_group_->client_group_id_ << " w grupie o licznosci: " << waiter->actual_group_->size_of_client_group_ << " otrzymal danie glowne o czasie " << global_time << "." << endl;
			queue_to_consumption->push(waiter->actual_group_);
			waiter->actual_group_ = nullptr;
		}
	}	
}
	
