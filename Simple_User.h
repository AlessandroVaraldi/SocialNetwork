//
// Created by Utente on 28/05/2018.
//

#ifndef PROGETTO_SIMPLE_USER_H
#define PROGETTO_SIMPLE_USER_H

#include "User.h"
#include "Date.h"
#include "Graph.hpp"
#include <iostream>
#include <vector>

using namespace std;

class Simple_User : public User {

public:
    //COSTRUTTORI _edgesNumber DISTRUTTORE
    Simple_User(const string &ID, const string &name, const string &surname, const Date &birthday, const Address &address, const string &gender);
    Simple_User(){};
    ~Simple_User();
    //METODI SETTERS
    void setSurname(const string &surname);
    void setGender(const string &g);
    void setSpouseID(Graph<User*,string,string> &grafo);
    void setMotherID(Graph<User*,string,string> &grafo);
    void setFatherID(Graph<User*,string,string> &grafo);
    //METODI GETTERS
    string getGender();
    string getSurname();
    string getSpouseID();
    string getMotherID();
    string getFatherID();
    int getDislikesNumber();
    int getLikesNumber();
    //ALTRI METODI GETTERS PER IL CONTEGGIO DI AMICI,PARENTI _edgesNumber CONOSCENTI
    int getFriendsNumber(Graph<User*,string,string> &grafo);
    int getAcquaintancesNumber(Graph<User*,string,string> &grafo);
    int getRelativesNumber(Graph<User*,string,string> &grafo, int &cont, bool risali, string startid, bool count_wife);
    //METODI PER AGGIUNTA DI UN LIKE O DISLIKE DA PARTE DELL'UTENTE
    void addDislikesNumber();
    void addLikesNumber();

private:

    //VARIABILI PRIVATE
    int _likesNumber = 0;
    int _dislikesNumber = 0;
    string _gender;
    string _surname;
    string _fatherID = "";
    string _motherID = "";
    string _spouseID = "";
};


#endif //PROGETTO_SIMPLE_USER_H
