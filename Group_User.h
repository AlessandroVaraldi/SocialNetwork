//
// Created by Utente on 28/05/2018.
//

#ifndef PROGETTO_GROUP_USER_H
#define PROGETTO_GROUP_USER_H

#include "User.h"
#include "Simple_User.h"
#include "Date.h"
#include "Graph.hpp"
#include <iostream>

using namespace std;

class Group_User: public User {

public:
    // COSTRUTTORI _edgesNumber DISTRUTTORE
    Group_User();
    Group_User( const string &ID, const string &name, const Date &date, const Address &address, const string &activity);
    ~Group_User();
    //METODO PER IL CONTEGGIO DEI MEMBRI
    int countMembers(Graph<User*,string,string> &grafo);
    //METODO SETTER PER L'ATTIVITA'
    void setActivity(const string &activity);
    //METODO GETTER PER L'ATTIVITA'
    string getActivity();

private:
    //VARIABILE PRIVATA
    string _activity;
};


#endif //PROGETTO_GROUP_USER_H
