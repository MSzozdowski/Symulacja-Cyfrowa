#pragma once


class GroupOfClients
{
public:
	int client_group_id_; // unikatowe id dla kazdej grupy klientow
	int size_of_client_group_; //licznosc danej grupy klientow
	double time_appear_; // czas pojawienia sie klienta w systemie
	double time_manager_; // czas obslugi przez kierownika
	double time_meal_; // czas oczekiwania na danie glowne
	double time_drink_; // czas oczekiwania na napoj
	double time_consumption_; // czas konsumpcji
	double time_buffet_; // czas pobytu w bufecie
	double time_cashier_; // czas obslugi przez kasjera
	bool sensitivity_on_alarm_; // czy klient reaguje na alarm

	GroupOfClients(const int client_id,const int size, const double t_appear,const double t_manager,const double t_meal,const double t_drink,const double t_consumption,const double t_cashier,const bool alarm_sens) // konstruktor dla klienta korzystajacego ze stolikow
	{
		client_group_id_ = client_id;
		size_of_client_group_ = size;
		time_appear_ = t_appear;
		time_manager_ = t_manager;
		time_meal_ = t_meal;
		time_drink_ = t_drink;
		time_consumption_ = t_consumption;
		time_cashier_ = t_cashier;
		sensitivity_on_alarm_ = alarm_sens;
	}
	GroupOfClients(const int client_id, const int size, const double t_appear,const double t_buffet, const double t_cashier,const bool alarm_sens) // konstruktor dla klienta korzystajacego z bufetu
	{
		client_group_id_ = client_id;
		size_of_client_group_ = size;
		time_appear_ = t_appear;
		time_buffet_ = t_buffet;
		time_cashier_ = t_cashier;
		sensitivity_on_alarm_ = alarm_sens;
	}
};


