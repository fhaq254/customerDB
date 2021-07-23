// Project7.cpp
// EE 312 Project 7 submission by
// Fawadul Haq
// fh5277
// Slip days used: 0
// Spring 2018

/*
 * Name:
 * EID:
 * Project 7, CRM part 2
 * EE 312, Spring 2017
 */

#include <stdio.h>
#include <iostream>
#include "String.h"
#include "Customer.h"
#include "CustomerDB.h"

void readString(String&);
void readNum(int&);

CustomerDB database;

int num_bottles = 0;
int num_rattles = 0;
int num_diapers = 0;

/* clear the inventory and reset the customer database to empty */
void reset(void) {
	database.clear();
	num_bottles = 0;
	num_rattles = 0;
	num_diapers = 0;
}

/*
 * selectInventItem is a convenience function that allows you
 * to obtain a pointer to the inventory record using the item type name
 * word must be "Bottles", "Diapers" or "Rattles"
 * for example the expression *selectInventItem("Bottles") returns the
 * current global variable for the number of bottles in the inventory
 */
int* selectInventItem(String word) {
	if (word == "Bottles") {
		return &num_bottles;
	} else if (word == "Diapers") {
		return &num_diapers;
	} else if (word == "Rattles") {
		return &num_rattles;
	}

	/* NOT REACHED */
	return 0;
}

/*
 * this overload of selectInventItem is similar to selectInventItem above, however
 * this overload takes a Customer as a second argument and selects the data member
 * of that Customer that matches "word". The function returns a pointer to one of the three data
 * members from the specified customer.
 */
int* selectInventItem(String word, Customer& cust) {
	if (word == "Bottles") {
		return &cust.bottles;
	} else if (word == "Diapers") {
		return &cust.diapers;
	} else if (word == "Rattles") {
		return &cust.rattles;
	}

	/* NOT REACHED */
	return 0;
}

/*
 * findMax searches through the CustomerDB "database" and returns the Customer
 * who has purchased the most items of the specified type.
 * type must be one of "Bottles", "Rattles" or "Diapers".
 *
 * Note: if two or more Customers are tied for having purchased the most of that item type
 * then findMax returns the first Customer in the CustomerDB who has purchased that maximal
 * quantity.
 *
 * Note: in the special case (invalid case) where there are zero Customers in the
 * CustomerDB, fundMax returns a null pointer (0)
 */
Customer* findMax(String type) {
	Customer* result = 0;
	int max = 0;
	// return result;
	for (int k = 0; k < database.size(); k += 1) {
		Customer& cust = database[k];
		int *p = selectInventItem(type, cust);
		if (*p > max) {
			max = *p;
			result = &cust;
		}
	}

	return result;
}


void processPurchase() {
	String name;
	String item;
	int quantity;

	readString(name);
	readString(item);
	readNum(quantity);
	int* requested_item = selectInventItem(item);

	// Error handling:
	// If asked for zero items,
	if(quantity == 0) return;
	// If not enough items in inventory,
	if(quantity > *requested_item){
		std::cout << "Sorry ...\n" ;
		return;
	}

	// Updating database and inventory

	//Customer whodunit = database[name];
	//int* new_item = selectInventItem(item,whodunit);
    printf("first\n");

	if(item == "Bottles") { *selectInventItem(item,database[name]) += quantity; *requested_item -= quantity;}
	if(item == "Diapers") { *selectInventItem(item,database[name]) += quantity; *requested_item -= quantity;}
	if(item == "Rattles") { *selectInventItem(item,database[name]) += quantity; *requested_item -= quantity;}
}

void processSummarize() {
	// Inventory
	std::cout << "There are " << num_bottles << " Bottles, " << num_diapers << " Diapers and " << num_rattles << " Rattles in inventory\n";
	std::cout << "we have had a total of " << database.size() << " different customers\n";

	// Maximum Purchases
	Customer* max_bottles = findMax("Bottles");
	Customer* max_diapers = findMax("Diapers");
	Customer* max_rattles = findMax("Rattles");
	if(max_bottles){
		std::cout << max_bottles->name.c_str() << " has purchased the most Bottles" << "(" << max_bottles->bottles << ")\n";
	} else { std::cout << "no one has purchased any Bottles\n";}

	if(max_diapers){
		std::cout << max_diapers->name.c_str() << " has purchased the most Diapers" << "(" << max_diapers->diapers << ")\n";
	} else { std::cout << "no one has purchased any Diapers\n";}

	if(max_rattles){
		std::cout << max_rattles->name.c_str() << " has purchased the most Rattles" << "(" << max_rattles->rattles << ")\n";
	} else { std::cout << "no one has purchased any Rattles\n";}

}

void processInventory() {
	// Reading inputs
	String item;   // type of item
	int quantity;  // amount
	readString(item);
	readNum(quantity);

	int* new_item = selectInventItem(item);
	*new_item += quantity;
}

