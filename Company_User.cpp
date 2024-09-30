//
// Created by Utente on 28/05/2018.
//

#include "Company_User.h"
#include <algorithm>

Company_User::Company_User(const string &ID, const string &name, const Date &date, const Address &address,const string &product)
        :User(ID,name,date,address){
    _product = product;
}

Company_User::~Company_User() {

}
 //---------------SETTERS-------------

void Company_User::setProduct(const string &product) {
    _product = product;
}

//---------------GETTERS---------------

string Company_User::getProduct() {
    return _product;
}

//----------------COUNTERS----------------

int Company_User::countEmployees(Graph<User*,string,string> &grafo) {
    int cont=0;
    //prendo la mappa delle relazioni di un utente
    map<string,vector<string>> relationships_map = grafo.getEdges(_ID);
    //scorro la mappa
    for(map<string,vector<string>>::iterator it = relationships_map.begin(); it != relationships_map.end(); it++){
        //se trovo una relazione di dipendente incremento il contatore
        if(find((it->second).begin(), (it->second).end(), "dipendente") != (it->second).end() ) {
            cont++;
        }
    }

    return cont;
}

int Company_User::countPartners(Graph<User*,string,string> &grafo) {
    int cont=0;
    //prendo la mappa delle relazioni di un utente
    map<string,vector<string>> relationships_map = grafo.getEdges(_ID);
    //scorro la mappa
    for(map<string,vector<string>>::iterator it = relationships_map.begin(); it != relationships_map.end(); it++){
        //se trovo una relazione di dipendente incremento il contatore
        if(find((it->second).begin(), (it->second).end(), "consociata") != (it->second).end() ) {
            cont++;
        }
    }

    return cont;
}


