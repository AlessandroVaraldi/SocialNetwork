//
// Created by Utente on 28/05/2018.
//

#include "Address.h"

#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

Address::Address(string &address) {
    if(!address.empty()) {
        replace(address.begin(), address.end(), '-', ' ');
        istringstream s(address);
        s >> _streetName >> _number >> _city >> _region >> _country;
    }else{
        _streetName = "";
        _number = '\0';
        _city = "";
        _region = "";
        _country = "";
    }

}

Address::Address(const Address &to_copy) {

    this->_city = to_copy._city;
    this->_number = to_copy._number;
    this->_country = to_copy._country;
    this->_region = to_copy._region;
    this->_streetName = to_copy._streetName;

}

Address::Address() {

}

string Address::str() const {
    ostringstream line;
    line << _streetName << "-" << _number << "-" << _city << "-" << _region << "-" << _country;
    return line.str();
}
