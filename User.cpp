//
// Created by Utente on 28/05/2018.
//

#include "User.h"

User::User(const string &ID, const string &name, const Date &date, const Address &address) {
    _ID = ID;
    _name = name;
    _date = date;
    _address = address;
}

User::User() {

}

User::~User() {}

//---------------SETTERS--------------

void User::setID(const string &ID) {
    _ID = ID;
}

void User::setName(const string &name) {
    _name = name;
}

void User::setDate(const Date &date) {
    _date = date;
}

void User::setAddress(const Address &address) {
    _address = address;
}

//---------------GETTERS--------------

string User::getID() {
    return _ID;
}

string User::getName() {
    return _name;
}

Date User::getDate() {
    return _date;
}

Address User::getAddress() {
    return _address;
}

