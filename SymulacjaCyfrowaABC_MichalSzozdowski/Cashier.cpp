#include "Cashier.h"


bool Cashier::if_cashier_free()
{
	if (actual_group_ == nullptr)
		return true;
	else
		return false;
}

void Cashier::make_cashier_busy(GroupOfClients* group)
{
	actual_group_ = group;
}

void Cashier::make_cashier_free()
{
	actual_group_ = nullptr;
}
