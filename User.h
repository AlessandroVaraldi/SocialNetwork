//
// Created by Utente on 28/05/2018.
//

#ifndef PROGETTO_USER_H
#define PROGETTO_USER_H

#include <iostream>
#include <map>

#include "Date.h"
#include "Address.h"
#include "Graph.hpp"

using namespace std;

class User {
public:
    virtual ~User() = 0;
    //SETTERS
    void setID(const string &ID);
    void setName(const string &name);
    void setDate(const Date &date);
    void setAddress(const Address &address);
    //GETTERS
    string getID();
    string getName();
    Date getDate();
    Address getAddress();

protected:
    User();
    User(const string &ID, const string &name, const Date &date, const Address &address);

    string _ID;
    string _name;
    Date _date;
    Address _address;
};


#endif //PROGETTO_USER_H
