/*
 * Name: Fawadul Haq
 * EID: fh5277
 * Project 7, CRM part 2
 * EE 312, Spring 2017
 */
#include <iostream>
#include <cassert>
#include "String.h"
#include "CustomerDB.h"

using namespace std;

const int default_capacity = 1;

// Customer Constructor
Customer::Customer(String name) { // done, please do not edit
    this->bottles = 0;
    this->rattles = 0;
    this->diapers = 0;
    this->name = name;
}

// Constructor
CustomerDB::CustomerDB(void) { // done, please do not edit
    this->capacity = default_capacity;
    this->data = new Customer[this->capacity];
    this->length = 0;
}

// returns number of customers in database
int CustomerDB::size(void) { // done, please do not edit
    return this->length;
}

// Destructor
CustomerDB::~CustomerDB(void) { // done, please do not edit
    delete[] this->data;
}

// deletes all customers and converts to a fresh, new database
void CustomerDB::clear(void) { // done, please do not edit
    delete[] this->data;
    this->capacity = default_capacity;
    this->data = new Customer[this->capacity];
    this->length = 0;
}

// returns a customer as a reference when given their "index" value
Customer& CustomerDB::operator[](int k) { // done, please do not edit
    printf("Byeeee\n");
    assert(k >= 0 && k < this->length);
    return this->data[k];
}

// returns a customer as a reference when given their name,
// if no name found, creates a new, blank customer to reference
Customer& CustomerDB::operator[](String name) { // not done, your effort goes here

    printf("HIIIII\n");

    // If we have a customer
    int numCust = this->length;
    int k = 0;
    while(k < numCust){
        if(this->data[k].name == name) return this->data[k];
        k++;;
    }

    // Otherwise, no customer yet, so make one
    if(this->length == this->capacity) { // Amortized doubling:
        // 1) make more, new space
        Customer* new_data = new Customer[(this->capacity) * 2];

        // 2) DEEP copy the structs
        int i;
        for (i = 0; i < this->length; i++) {
            new_data[i].name    = this->data[i].name;
            new_data[i].diapers = this->data[i].diapers;
            new_data[i].rattles = this->data[i].rattles;
            new_data[i].bottles = this->data[i].bottles;
        }

        // Add new customer
        new_data[i] = Customer(name);

        // Update capacity and length
        this->length   += 1;
        this->capacity *= 2;

        // Replace old data
        delete[] this->data;
        this->data = new_data;
        return new_data[i];
    }

    // No doubling, add customer regularly
    this->data[this->length] = Customer(name);
    this->length += 1;
    return this->data[this->length];

}

bool CustomerDB::isMember(String name) { // not done, your effort goes here
    int numCust = this->length;
    int k = 0;

    while(k < numCust){  // find "name"
        if(this->data[k].name == name) return true;
        k++;;
    } // otherwise,
    return false;
}
