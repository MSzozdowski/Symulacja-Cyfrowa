#include "FinishDrinkService.h"
#include <iostream>
#include <queue>

void FinishDrinkService::execute(Waiter* waiter,queue <GroupOfClients*>* helper_queue_to_waiters_meal,double global_time)
{
	if(waiter!=nullptr)
		if(waiter->actual_group_!=nullptr && waiter->actual_group_->client_group_id_>0)
	{
		cout << "Klient o id: " << waiter->actual_group_->client_group_id_ << " w grupie o licznosci: " << waiter->actual_group_->size_of_client_group_ << " otrzymal napoj od kelnera o czasie " << global_time << "." << endl;
		helper_queue_to_waiters_meal->push(waiter->actual_group_);
		waiter->actual_group_ = nullptr;
	}
}
