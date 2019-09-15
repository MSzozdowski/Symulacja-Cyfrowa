#include "QueueToBuffet.h"

void QueueToBuffet::add_on_buffet_queue(GroupOfClients* group_of_clients)
{
	queue_to_buffet_.push(group_of_clients);
}

bool QueueToBuffet::is_queue_to_buffet_empty()
{
	return queue_to_buffet_.empty();
}

int QueueToBuffet::size_of_first_group_in_buffet_queue()
{
	return (queue_to_buffet_.front())->size_of_client_group_;
}

GroupOfClients* QueueToBuffet::take_clients_from_queue_to_buffet()
{
	return queue_to_buffet_.front();
}

void QueueToBuffet::pop_clients_from_queue_to_buffet()
{
	queue_to_buffet_.pop();
}

int QueueToBuffet::length_of_queue_to_buffet()
{
	return queue_to_buffet_.size();
}

