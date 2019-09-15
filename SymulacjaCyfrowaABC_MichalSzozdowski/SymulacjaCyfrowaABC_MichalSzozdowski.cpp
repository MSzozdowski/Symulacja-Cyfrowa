#include "Buffet.h"
#include "QueueToBuffet.h"
#include "Cashier.h"
#include "QueueToCashiers.h"
#include "GroupOfClients.h"
#include "Manager.h"
#include "QueueToTable.h"
#include "Restaurant.h"
#include "GenerateNewClients.h"
#include "StartBuffetService.h"
#include "StartManagerService.h"
#include "FinishManagerService.h"
#include "FinishBuffetService.h"
#include "StartCashierService.h"
#include "FinishCashierService.h"
#include "AlarmGenerator.h"
#include "StartDrinkService.h"
#include "FinishDrinkService.h"
#include "StartMealService.h"
#include "FinishMealService.h"
#include "StartConsumption.h"
#include "FinishConsumption.h"
#include "EventList.h"

#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <cstdlib>
#include <fstream>

bool sort_predicate(const EventList& a, const EventList& b);

using namespace std;

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	//inicjalizacja systemu
	Restaurant* restaurant = new Restaurant;
	GenerateNewClients generate_new_clients;
	AlarmGenerator* generate_new_alarm = new AlarmGenerator();
	StartBuffetService* start_buffet_service = new StartBuffetService();
	StartManagerService* start_manager_service = new StartManagerService();
	FinishManagerService* finish_manager_service = new FinishManagerService();
	FinishBuffetService* finish_buffet_service = new FinishBuffetService();
	StartCashierService* start_cashier_service = new StartCashierService();
	FinishCashierService* finish_cashier_service = new FinishCashierService();
	StartDrinkService* start_drink_service = new StartDrinkService();
	FinishDrinkService* finish_drink_service = new FinishDrinkService();
	StartMealService* start_meal_service = new StartMealService();
	FinishMealService* finish_meal_service = new FinishMealService();
	StartConsumption* start_consumption = new StartConsumption();
	FinishConsumption* finish_consumption = new FinishConsumption();

	vector<EventList>* event_list = new vector<EventList>;
	vector<GroupOfClients*>* to_alarm = new vector<GroupOfClients*>;
	queue<GroupOfClients*>* helper_queue_to_waiters_drink = new queue<GroupOfClients*>;
	queue<GroupOfClients*>* helper_queue_to_waiters_meal = new queue<GroupOfClients*>;
	queue<GroupOfClients*>* helper_queue_to_consumption = new queue<GroupOfClients*>;

	//inicjalizacja statystyk i zminnych pomocniczych do ich zebrania
	int average_groups_in_system=0;
	vector<int> average_groups_in_system_vector;
	vector<double> average_groups_in_system_vector_time;
	vector<double> average_time_waiting_for_table;
	vector<int>* helper_id_table = new vector<int>;
	vector<double>* helper_time_table = new vector<double>;
	vector<int> average_length_queue_to_table;
	vector<double> average_time_waiting_for_waiter_service;
	vector<int>* helper_id_waiter = new vector<int>;
	vector<double>* helper_time_waiter = new vector<double>;
	vector<int> average_length_queue_to_cashiers;

	int tab_seed[10];//tablica przechowujaca wartosci ziaren
	tab_seed[0] = 2000000;
	int seed_helper = 4100000;
	for (int i = 1; i < 10; i++)
	{
		tab_seed[i] = seed_helper;
		seed_helper += 100000;
	}

	//zainicjalizowanie poczatku i konca generowania alarmu 
	double global_alarm_time = 1;
	const double time_of_simulation_alarm = 500000;

	//zainicjalizowanie generatora alarmu
	default_random_engine generator = default_random_engine(3300000);
	normal_distribution<double> distribution_of_alarm = normal_distribution<double>(4200.0, 50.0);

	//wygenerowanie wszystkich alarmow, ktore pojawia sie w resturacji do konca czasu symulacji
	while(global_alarm_time< time_of_simulation_alarm)
	{
		EventList alarm;
		alarm.step_ = 0;
		alarm.time_ = distribution_of_alarm(generator) + global_alarm_time;
		event_list->push_back(alarm);
		global_alarm_time = alarm.time_;
	}

	//inicjalizacja pomiaru czasu symulacji oraz jej konca
	const double time_of_simulation = time_of_simulation_alarm;
	double global_time = 1.0;
	bool event_trig=false;
	int which_step;
	int id_counter = 1;
	int mode;

	//wybranie trybu symulacji
	cout << "Wybierz tryb: 1.krokowy, 2.ciagly" << endl;
	cin >> mode;
	
	//dodanie pierwszego zdarzenia czasowego i ustawienie go na pierwszym miejscu na liscie
	EventList first_client;
	first_client.step_ = 1;
	first_client.time_ = 1;
	event_list->push_back(first_client);
	
	while(global_time < time_of_simulation)
	{
		average_groups_in_system_vector.push_back(average_groups_in_system);
		average_groups_in_system_vector_time.push_back(global_time);
		if (!event_list->empty()) // obsluga zdarzen czasowych
		{
			sort(event_list->begin(), event_list->end(), sort_predicate);
			global_time = event_list->at(0).time_;
			
			which_step = event_list->at(0).step_;
			switch (which_step)
			{
				case 0://absluga alarmu
					cout << "Dzwoni alarm o czasie " << global_time << "." << endl;
					average_groups_in_system = average_groups_in_system - to_alarm->size();
					generate_new_alarm->execute(to_alarm, global_time, restaurant, helper_queue_to_waiters_drink, helper_queue_to_waiters_meal, helper_queue_to_consumption);
					break;
				case 1: //pojawienie sie nowego klienta
					generate_new_clients.execute(event_list, restaurant->queue_to_table_, restaurant->queue_to_buffet_, id_counter++, global_time, to_alarm,helper_id_table,helper_time_table);
					average_length_queue_to_table.push_back(restaurant->queue_to_table_->length_of_tables());
					++average_groups_in_system;
					break;
				case 2: //zakonczenie korzystania z bufetu przez klienta
					for (int i = 0; i < restaurant->buffet_->size_of_buffet_; i++)
					{
						if (restaurant->buffet_->sitting_.at(i) != nullptr && restaurant->buffet_->sitting_[i]->time_buffet_ == global_time)
						{
							finish_buffet_service->execute(restaurant->buffet_, restaurant->queue_to_cashiers_, global_time, i);
						}
					}
					break;
				case 3://zakończenie obslugi u kasjerow
					for (int i = 0; i < restaurant->cashiers_.size(); i++)
					{
						if (restaurant->cashiers_.at(i) != nullptr && restaurant->cashiers_.at(i)->actual_group_ != nullptr && restaurant->cashiers_.at(i)->actual_group_->time_cashier_ == global_time)
						{
							finish_cashier_service->execute(restaurant->cashiers_,/*, restaurant->queue_to_cashiers_,*/ global_time, i, to_alarm);
							--average_groups_in_system;
						}
					}
					break;
				case 4: // zakonczenie obslugi przez managera
					finish_manager_service->execute(restaurant->manager_, restaurant->tables_, helper_queue_to_waiters_drink, global_time,helper_id_waiter,helper_time_waiter);
					break;
				case 5: //wydanie napoju
					finish_drink_service->execute(event_list->at(0).waiter_, helper_queue_to_waiters_meal, global_time);
					break;
				case 6: //wydanie dania glownego
					finish_meal_service->execute(event_list->at(0).waiter_, helper_queue_to_consumption, global_time);
					break;
				case 7://zakonczenie konsumpcji 
					finish_consumption->execute(event_list->at(0).table_, restaurant->queue_to_cashiers_, global_time);
					break;
			}
			if (global_time < time_of_simulation && mode==1)
				system("pause");
		}
		event_trig = true;
		while(event_trig==true) //obsluga zdarzen warunkowych
		{
			event_trig = false;
			if(!(restaurant->queue_to_buffet_)->is_queue_to_buffet_empty() && (((restaurant->buffet_->size_of_buffet_)-(restaurant->buffet_->busy_places_in_buffet_))>=restaurant->queue_to_buffet_->size_of_first_group_in_buffet_queue())) // zajecie miejsca przy bufecie
			{
				start_buffet_service->execute(event_list,restaurant->buffet_,restaurant->queue_to_buffet_,global_time);
				event_trig = true;
			}
			if(restaurant->which_cashier_free()!=1000 && !restaurant->queue_to_cashiers_->if_queue_to_cashiers_is_empty())//zajecie miejsca u kasjera
			{
				start_cashier_service->execute(event_list, restaurant->queue_to_cashiers_, restaurant->cashiers_, restaurant->which_cashier_free(), global_time);
				average_length_queue_to_cashiers.push_back(restaurant->queue_to_cashiers_->length_of_cashiers());
				event_trig = true;
			}
			if(!(restaurant->manager_->busy_manager_) && !restaurant->queue_to_table_->is_queue_to_table_empty() && restaurant->if_possible_to_sit())//poczatek obslugi grupy przez kierownika
			{	
				start_manager_service->execute(event_list,restaurant->manager_, restaurant->tables_, restaurant->queue_to_table_, global_time);
				for(int i=0;i<helper_id_table->size();i++)
				{
					if(restaurant->manager_->actual_group_->client_group_id_==helper_id_table->at(i))
					{
						double helper = global_time - helper_time_table->at(i);
						average_time_waiting_for_table.push_back(helper);
						break;
					}
				}
				event_trig = true;
			}
			if(!helper_queue_to_waiters_drink->empty() && restaurant->which_waiter_free()!=1000)//poczatek obslugi przez kelnera (podanie napoju)
			{
				int position = restaurant->which_waiter_free();
				start_drink_service->execute(event_list,helper_queue_to_waiters_drink,restaurant->waiters_,position,global_time);
				for(int i=0;i<helper_id_waiter->size();i++)
				{
					if(restaurant->waiters_[position]->actual_group_->client_group_id_==helper_id_waiter->at(i))
					{
						double helper = global_time - helper_time_waiter->at(i);
						average_time_waiting_for_waiter_service.push_back(helper);
					}
				}
				event_trig = true;
			}
			if(!helper_queue_to_waiters_meal->empty() && restaurant->which_waiter_free()!=1000)//poczatek obslugi przez kelnera (podanie dania glownego)
			{
				start_meal_service->execute(event_list,helper_queue_to_waiters_meal,restaurant->waiters_,restaurant->which_waiter_free(),global_time);
				event_trig = true;
			}
			if(!helper_queue_to_consumption->empty())//rozpoczecie konsumpcji
			{
				start_consumption->execute(event_list,helper_queue_to_consumption,restaurant->tables_, global_time);
				event_trig = true;
			}
			
		}
		
		if(event_list->size()>0)
		{
			event_list->erase(event_list->begin());
		}
				
	}
	
	//statystyki
	fstream file1;
	file1.open("clients_in_system.txt", ios::out | ios::trunc);
	for (int i = 0; i < average_groups_in_system_vector.size(); i++)
	{
		if (file1.good())
		{
			file1 << average_groups_in_system_vector.at(i) << endl;
		}
	}
	file1.close();
	cout << "Liczba klientow w systemie: " << average_groups_in_system << endl;

	fstream file2;
	file2.open("time_for_system_clients.txt", ios::out | ios::trunc);
	for (int i = 0; i < average_groups_in_system_vector_time.size(); i++)
	{
		if (file2.good())
		{
			file2 << average_groups_in_system_vector_time.at(i) << endl;
		}
	}
	file2.close();
	
	fstream file3;
	file3.open("average_time_waiting_for_table.txt", ios::out | ios::trunc);
	double final_average_time_waiting_for_table_=0;
	for(int i=0;i< average_time_waiting_for_table.size();i++)
	{
		if(file3.good())
		{
			file3<<average_time_waiting_for_table.at(i) << endl;
		}
		final_average_time_waiting_for_table_ += average_time_waiting_for_table.at(i);
	}
	file3.close();
	final_average_time_waiting_for_table_ = final_average_time_waiting_for_table_ / average_time_waiting_for_table.size();
	cout << "Sredni czas oczekiwania na stolik to: " << final_average_time_waiting_for_table_ << "." << endl;
	
	fstream file4;
	double final_average_length_queue_to_table = 0;
	file4.open("average_length_of_queue_to_table.txt", ios::out | ios::trunc);
	for (int i = 0; i <average_length_queue_to_table.size() ; i++)
	{
		if (file4.good())
		{
			file4 <<average_length_queue_to_table.at(i) << endl;
			final_average_time_waiting_for_table_ += average_length_queue_to_table.at(i);
		}
	}
	file4.close();
	final_average_length_queue_to_table = final_average_time_waiting_for_table_ / average_length_queue_to_table.size();
	cout << "Srednia dlugosc kolejki do stolikow to: " << final_average_length_queue_to_table << "." << endl;
	
	fstream file5;
	file5.open("average_time_waiting_for_waiter_service.txt", ios::out | ios::trunc);
	double final_average_time_waiting_for_waiter_service = 0;
	for (int i = 0; i <average_time_waiting_for_waiter_service.size() ; i++)
	{
		if (file5.good())
		{
			file5 <<average_time_waiting_for_waiter_service.at(i) << endl;
			final_average_time_waiting_for_waiter_service += average_time_waiting_for_waiter_service.at(i);
		}
	}
	file5.close();
	final_average_time_waiting_for_waiter_service = final_average_time_waiting_for_waiter_service / average_time_waiting_for_waiter_service.size();
	cout << "Sredni czas oczekiwania na obsluge przez kelnera to: " << final_average_time_waiting_for_waiter_service << "." << endl;

	fstream file6;
	file6.open("average_length_queue_to_cashiers.txt", ios::out | ios::trunc);
	double final_average_length_queue_to_cashiers = 0;
	for (int i = 0; i <average_length_queue_to_cashiers.size() ; i++)
	{
		if (file6.good())
		{
			file6 <<average_length_queue_to_cashiers.at(i) << endl;
			final_average_length_queue_to_cashiers += average_length_queue_to_cashiers.at(i);
		}
	}
	file6.close();
	final_average_length_queue_to_cashiers = final_average_length_queue_to_cashiers / average_length_queue_to_cashiers.size();
	cout << "Srednia dlugosc kolejki do kasjerow to: " << final_average_length_queue_to_cashiers << "." << endl;
}

bool sort_predicate(const EventList& a,const EventList& b)
{
	if (a.time_ < b.time_)
	{
		return true;
	}
	else if(a.time_ == b.time_)
	{
		return 0;
	}
	else
	{
		return false;
	}
}

