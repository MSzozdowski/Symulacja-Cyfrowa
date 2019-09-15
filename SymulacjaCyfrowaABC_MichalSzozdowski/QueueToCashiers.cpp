#include "QueueToCashiers.h"


void QueueToCashiers::add_on_cashiers_queue(GroupOfClients* group_of_clients)
{
	queue_to_cashiers_.push(group_of_clients);
}

bool QueueToCashiers::if_queue_to_cashiers_is_empty()
{
	return queue_to_cashiers_.empty();
}

GroupOfClients* QueueToCashiers::take_from_queue_to_cashiers()
{
	return queue_to_cashiers_.front();
}

void QueueToCashiers::pop_from_queue_to_cashiers()
{
	queue_to_cashiers_.pop();
}

int QueueToCashiers::length_of_cashiers()
{
	return queue_to_cashiers_.size();
}
