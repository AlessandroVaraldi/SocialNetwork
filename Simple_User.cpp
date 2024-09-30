//
// Created by Utente on 28/05/2018.
//

#include "Simple_User.h"
#include <algorithm>

//-------------COSTRUTTORE-------------
//costruttore di SimpleUser che setta surname e gender mentre il resto viene settato da costruttore della classe principale
Simple_User::Simple_User(const string &ID, const string &name, const string &surname, const Date &birthday,
                         const Address &address, const string &gender): User(ID,name,birthday,address) {
    _surname = surname;
    _gender = gender;
}

//------------DISTRUTTORE----------
Simple_User::~Simple_User() {}

//-------------SETTERS------------

void Simple_User::setSurname(const string &surname) {
    _surname = surname;
}

void Simple_User::setGender(const string &g) {
    _gender = g;
}
//metodo per settare l'ID del coniuge andandolo a cercare nella mappa di relazioni presa dal grafo
void Simple_User::setSpouseID(Graph<User*,string,string> &grafo) {
    bool flag_out = false;
    //prendo la mappa delle relazioni dell'utente dal grafo
    map<string,vector<string>> relationships_map = grafo.getEdges(_ID);
    //controllo se è vuota
    if(!relationships_map.empty()) {
        //scorro la mappa
        for (map<string, vector<string>>::iterator it = relationships_map.begin(); it != relationships_map.end() && flag_out != true; it++) {
            //se trovo nel vettore di stringhe (che è il secondo campo della mappa) una relazione di coniuge allora setto spouseID all'ID di quell'utente
            if (find((it->second).begin(), (it->second).end(), "coniuge") != (it->second).end()) {
                _spouseID = it->first;
                flag_out = true;
            }
        }
    }
    //se non trovo un coniuge allora metto una stringa nulla a spouseID
    if(flag_out == false){
        _spouseID = "";
    }
}

void Simple_User::setMotherID(Graph<User*,string,string> &grafo) {
    bool flag_out = false;
    string ID;
    //prendo la mappa dei nodi dal grafo
    map<string,User*> mappa_nodi = grafo.getNodes();
    //prendo la mappa delle relazioni dell'utente dal grafo
    map<string,vector<string>> relationships_map = grafo.getEdges(_ID);

    //controllo se la mappa delle relazioni è vuota
    if(!relationships_map.empty()) {
        //scorro la mappa delle relazioni
        for (map<string, vector<string>>::iterator it = relationships_map.begin(); it != relationships_map.end() && flag_out != true; it++) {
            //se trovo una relazione figlio allora setto ID all'ID con cui ho questa relazione
            if (find((it->second).begin(), (it->second).end(), "figlio") != (it->second).end()) {
                ID = it->first;
                //controllo, andando a cercare l'ID nella mappa dei nodi, se l'utente è di sesso femminile, se sì allora setto motherID
                if(((Simple_User*)(mappa_nodi.find(ID)->second))->getGender() == "F") {
                    _motherID = it->first;
                    flag_out = true;
                }
            }
        }
    }
    //se non trovo una madre allora setto la stringa nulla
    if(flag_out == false){
        _motherID = "";
    }
}

void Simple_User::setFatherID(Graph<User*,string,string> &grafo) {
    bool flag_out = false;
    string ID;
    //prendo la mappa dei nodi dal grafo
    map<string,User*> mappa_nodi = grafo.getNodes();
    //prendo la mappa delle relazioni dell'utente dal grafo
    map<string,vector<string>> relationships_map = grafo.getEdges(_ID);

    //controllo se la mappa delle relazioni è vuota
    if(!relationships_map.empty()) {
        //scorro la mappa delle relazioni
        for (map<string, vector<string>>::iterator it = relationships_map.begin(); it != relationships_map.end() && flag_out != true; it++) {
            //se trovo una relazione figlio allora setto ID all'ID con cui ho questa relazione
            if (find((it->second).begin(), (it->second).end(), "figlio") != (it->second).end()) {
                ID = it->first;
                //controllo, andando a cercare l'ID nella mappa dei nodi, se l'utente è di sesso maschile, se sì allora setto fatherID
                if(((Simple_User*)(mappa_nodi.find(ID)->second))->getGender() == "M") {
                    _fatherID = it->first;
                    flag_out = true;
                }
            }
        }
    }

    //se non trovo un padre allora setto la stringa nulla
    if(flag_out == false){
        _fatherID = "";
    }

}

//----------------GETTERS--------------

string Simple_User::getGender() {
    return _gender;
}
string Simple_User::getSpouseID() {
    return _spouseID;
}

string Simple_User::getMotherID() {
    return _motherID;
}

string Simple_User::getFatherID() {
    return _fatherID;
}

void Simple_User::addDislikesNumber() {
    _dislikesNumber++;
}

void Simple_User::addLikesNumber() {
    _likesNumber++;
}

int Simple_User::getDislikesNumber() {
    return _dislikesNumber;
}

int Simple_User::getLikesNumber() {
    return _likesNumber;
}

string Simple_User::getSurname() {
    return _surname;
}

//metodo che torna il numero di amici dell'utente
int Simple_User::getFriendsNumber(Graph<User*,string,string> &grafo){
    int cont=0;
    //prendo la mappa delle relazioni dell'utente
    map<string,vector<string>> relationships_map = grafo.getEdges(_ID);
    //scorro la mappa
    for(map<string,vector<string>>::iterator it = relationships_map.begin(); it != relationships_map.end(); it++){
        //se trovo una relazione amico incremento il contatore
        if(find((it->second).begin(), (it->second).end(), "amico") != (it->second).end() ) {
            cont++;
        }
    }

    return cont;
}

//metodo che torna il numero di conoscenti dell'utente
int Simple_User::getAcquaintancesNumber(Graph<User*,string,string> &grafo){
    int cont=0;
    //prendo la mappa delle relazioni dell'utente
    map<string,vector<string>> relationships_map = grafo.getEdges(_ID);
    //scorro la mappa
    for(map<string,vector<string>>::iterator it = relationships_map.begin(); it != relationships_map.end(); it++){
        //se trovo una relazione conoscente incremento il contatore
        if(find((it->second).begin(), (it->second).end(), "conoscente") != (it->second).end() ) {
            cont++;
        }
    }

    return cont;
}

int Simple_User::getRelativesNumber(Graph<User *, string, string> &grafo, int &cont, bool risali, string startid, bool count_wife) {
    map<string,User*>mappa_nodi= grafo.getNodes();
    map<string,vector<string>>relationhips_map = grafo.getEdges(_ID);
    Simple_User* su;
    if(mappa_nodi.find(_fatherID)!=mappa_nodi.end() && risali){
        su = ((Simple_User*)mappa_nodi.find(_fatherID)->second);
        return cont = su->getRelativesNumber(grafo,cont,risali,startid,count_wife);
    }
    if(risali) {
        risali = false;
    }
    if(!risali){
        cont++;
    }
    if(_ID==startid && !risali){cont--;}
    if(count_wife && _spouseID!="")
        cont++;
    if(_ID==startid || _fatherID==((Simple_User*)mappa_nodi.find(startid)->second)->getFatherID()){
        count_wife=false;
    }

    for(map<string,vector<string>>::iterator it = relationhips_map.begin(); it != relationhips_map.end(); it++){
        if(find((it->second).begin(), (it->second).end(), "padre") != (it->second).end() || find((it->second).begin(), (it->second).end(), "madre") != (it->second).end()){
            su = ((Simple_User*)mappa_nodi.find(it->first)->second);
            cont=su->getRelativesNumber(grafo,cont,risali,startid,count_wife);
        }
    }

    return cont;
}



