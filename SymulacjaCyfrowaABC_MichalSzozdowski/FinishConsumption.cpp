#include "FinishConsumption.h"
#include "QueueToCashiers.h"

#include <iostream>

using namespace std;
void FinishConsumption::execute(Table* table, QueueToCashiers* queue_to_cashiers,double global_time)
{
	if(table->actual_client_!=nullptr)
	{
		queue_to_cashiers->add_on_cashiers_queue(table->actual_client_);
		cout << "Klient o id: " << table->actual_client_->client_group_id_ << " w grupie o licznosci " << table->actual_client_->size_of_client_group_ << " zakonczyl konsumpcje i ustawil sie w kolejce do kasjerow o czasie " << global_time << "." << endl;
		table->actual_client_ = nullptr;
	}
}
