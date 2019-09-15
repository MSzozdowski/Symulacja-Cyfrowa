#pragma once
#include "GroupOfClients.h"

class Table
{
public:
	GroupOfClients* actual_client_;//klient zajmujacy stolik
	int size_of_table_; //liczba miejsc przy danym stoliku

	explicit Table(const int size=0)
	{
		actual_client_ = nullptr;
		size_of_table_ = size;
	};
};

