//
// Created by Utente on 28/05/2018.
//

#include "Group_User.h"

//--------------COSTRUTTORI-------------
Group_User::Group_User(const string &ID, const string &name, const Date &date, const Address &address,const string &activity)
        :User(ID,name,date,address){
    _activity = activity;
}

Group_User::Group_User() = default;

//-------------DISTRUTTORE-----------
Group_User::~Group_User() {

}

//--------------SETTERS------------
void Group_User::setActivity(const string &activity) {
    _activity = activity;
}

//--------------GETTERS------------

string Group_User::getActivity() {
    return _activity;
}

//-------------COUNTERS-----------

int Group_User::countMembers(Graph<User*,string,string> &grafo) {
    int cont=0;
    //prendo la mappa delle relazioni del gruppo
    map<string,vector<string>> relationships_map = grafo.getEdges(_ID);
    //scorro la mappa
    for(map<string,vector<string>>::iterator it = relationships_map.begin(); it != relationships_map.end(); it++){
        //se trovo una relazione membro allora incremento il contatore
        if(find((it->second).begin(), (it->second).end(), "membro") != (it->second).end() ) {
            cont++;
        }
    }

    return cont;
}


