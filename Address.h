//
// Created by Utente on 28/05/2018.
//

#ifndef PROGETTO_ADDRESS_H
#define PROGETTO_ADDRESS_H

#include <iostream>

using namespace std;

class Address {
public:
    Address();
    Address(string &address);
    Address(const Address &to_copy);
    string str() const;



private:
    string _number;
    string _streetName;
    string _city;
    string _region;
    string _country;
};


#endif //PROGETTO_ADDRESS_H
