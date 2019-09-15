#pragma once
#include "Buffet.h"
#include "Table.h"
#include "Waiter.h"
#include "Cashier.h"
#include "QueueToTable.h"
#include "QueueToBuffet.h"
#include "QueueToCashiers.h"
#include "Manager.h"

#include <vector>


using namespace std;
class Restaurant
{
public:
	//model restauracji 
	const int double_table_=4; 
	const int triple_table_=14;
	const int four_person_table_=4;
	const int number_of_waiters_ = 13;
	const int number_of_cashiers_ = 6;
	const int places_in_buffet_ = 20;
	vector<Table*> tables_;
	vector<Waiter*> waiters_;
	vector<Cashier*> cashiers_;
	QueueToTable* queue_to_table_ = new QueueToTable;
	QueueToBuffet* queue_to_buffet_ = new QueueToBuffet;
	QueueToCashiers* queue_to_cashiers_ = new QueueToCashiers;
	Manager* manager_ = new Manager;
	Buffet* buffet_ = new Buffet(places_in_buffet_);
	
	Restaurant() {
		for (auto i = 0; i < double_table_; i++)       //dodanie odpowiedniej liczebnosci i rodzaju stolikow do wektora stolikow
			tables_.push_back(new Table(2));
		
		for (auto i = 0; i < triple_table_; i++)
			tables_.push_back(new Table(3));
		
		for (auto i = 0; i < four_person_table_; i++)
			tables_.push_back(new Table(4));

		for (auto i = 0; i < number_of_waiters_; i++) //inicjalizacja odpowiedniej liczby kelnerow i dodanie ich do wektora kelnerow
			waiters_.push_back(new Waiter);

		for (auto i = 0; i < number_of_waiters_; i++) //inicjalizacja odpowiedniej liczby kasjerow i dodanie ich do wektora kasjerow
			cashiers_.push_back(new Cashier);
		
	};
	
	int which_cashier_free();//funkcja zwracajaca indeks (w tablicy kasjerow) pierwszego znalezionego wolnego kasjera
	bool if_possible_to_sit();//funkcja sprawdzajaca czy usadzenie jest mozliwe (zgodna z warunkami metody usadzania)
	int which_waiter_free();//funkcja zwracajaca indeks (w tablicy kelnerow) pierwszego znalezionego wolnego kelnera
};