//
// Created by Utente on 28/05/2018.
//

#ifndef PROGETTO_COMPANY_USER_H
#define PROGETTO_COMPANY_USER_H

#include "User.h"
#include "Simple_User.h"
#include <iostream>

using namespace std;

class Company_User : public User {

public:
    //COSTRUTTORE _edgesNumber DISTRUTTORE
    Company_User( const string &ID, const string &name, const Date &date, const Address &address, const string &product);
    ~Company_User();
    //METODI PER IL CONTEGGIO DEGLI IMPIEGATI _edgesNumber DELLE CONSOCIATE
    int countEmployees(Graph<User*,string,string> &grafo);
    int countPartners(Graph<User*,string,string> &grafo);
    //METODO PER SETTARE IL PRODOTTO
    void setProduct(const string &product);
    //METODO GETTER PER IL PRODOTTO
    string getProduct();

private:
    //VARIABILE PRIVATA
    string _product;
};


#endif //PROGETTO_COMPANY_USER_H
