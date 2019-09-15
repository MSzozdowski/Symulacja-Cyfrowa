#include "QueueToTable.h"

void QueueToTable::add_on_table_queue(GroupOfClients* group_of_clients)
{
	queue_to_table_.push(group_of_clients);
}

bool QueueToTable::is_queue_to_table_empty()
{
	 return queue_to_table_.empty();
}

int QueueToTable::length_of_tables()
{
	 return queue_to_table_.size();
}

void QueueToTable::pop_from_queue_to_table()
{
	 queue_to_table_.pop();
}

GroupOfClients* QueueToTable::take_from_queue_to_table()
{
	return  queue_to_table_.front();
}
