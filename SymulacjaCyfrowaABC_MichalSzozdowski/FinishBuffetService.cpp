#include "FinishBuffetService.h"

#include <iostream>

using namespace std;

void FinishBuffetService::execute(Buffet* buffet, QueueToCashiers* queue_to_cashiers, double global_time,int position_in_buffet)
{
	GroupOfClients* actual_client=buffet->sitting_out(position_in_buffet);
	queue_to_cashiers->add_on_cashiers_queue(actual_client);
	cout << "Klient o id: " << actual_client->client_group_id_ << " w grupie o licznosci: " << actual_client->size_of_client_group_ << " zakonczyl korzystanie z bufetu i ustawil sie w kolejce do kasjerow o czasie " << global_time <<"." <<endl;
}
