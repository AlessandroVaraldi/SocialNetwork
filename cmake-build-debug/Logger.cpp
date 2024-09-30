//
// Created by Utente on 28/05/2018.
//

#include "Logger.h"
#include "User.h"
#include "Simple_User.h"
#include "Company_User.h"
#include "Group_User.h"
#include "News.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

/*Cose da fare:
 * controllare se la template del grafo è giusta;
 * definire bene le funzioni di ricerca per simpatia aziende;
 * i file;
 * controllare che tra due utenti non sia presente più di una relazione di parentela
 * fare mostEmployeePartners
*/
Logger::Logger(const string &file_name_1, const string &file_name_2, const string &file_name_3) {

    bool _areFilesOpen = true;

    char gender = 'M';
    vector <string> ID_likes;
    vector <string> ID_dislikes;
    string ID1,ID2,ID3,relationship,user_type,activity,address,product,date,name,surname,message,str_to_ignore;
    string line;
    istringstream s;
    ifstream file_info, file_relationship, file_news;

    file_info.open(file_name_1);
    file_relationship.open(file_name_2);
    file_news.open(file_name_3);

    if(file_info.is_open()){
        while(!file_info.eof()){
            file_info >> line;
            s.clear();
            s.str(line);

            if(_isLineUserFileGood(line)){

                replace(line.begin(),line.end(), ':', ' ');
                replace(line.begin(),line.end(), ',', ' ');
                replace(line.begin(),line.end(), '{', ' ');
                replace(line.begin(),line.end(), '}', ' ');
                replace(line.begin(),line.end(), '-', ' ');

                s >> ID1 >> user_type;

                if (user_type == "simple"){
                    //fare delete
                    s >> str_to_ignore >> name >> str_to_ignore >> surname >> str_to_ignore >> date >> str_to_ignore >> address >> str_to_ignore >> gender;
                    Simple_User *s_u = new Simple_User(ID1, name, surname, Date(date), Address(address),gender);
                    _graph.InsertNode(ID1, s_u);
                } else if (user_type == "company") {
                    s >> str_to_ignore >> name >> str_to_ignore >> date >> str_to_ignore >> address >> str_to_ignore >> product;
                    Company_User *company = new Company_User(ID1, name, Date(date), Address(address),product);
                    _graph.InsertNode(ID1, company);
                } else if (user_type == "group") {
                    s >> str_to_ignore >> name >> str_to_ignore >> date >> str_to_ignore >> address >> str_to_ignore >> activity;
                    Group_User *group = new Group_User(ID1, name, Date(date), Address(address),activity);
                    _graph.InsertNode(ID1, group);
                }
            }
        }
    }
    else{
        _areFilesOpen = false;
    }

    s.clear();

    if(file_relationship.is_open()){
        while(!file_relationship.eof()) {
            getline(file_relationship, line);
            if (_isLineUserRelationshipsFileGood(line)) {

                replace(line.begin(),line.end(),',',' ');
                s.clear();
                s.str(line);
                s >> ID2 >> ID3 >> relationship;

                if(relationship == "padre" || relationship == "madre"){
                    _graph.InsertEdge(ID2,ID3,relationship,_graph.SI);
                    _graph.InsertEdge(ID3,ID2,"figlio",_graph.SI);

                }

                if(relationship == "figlio"){
                    _graph.InsertEdge(ID2,ID3,relationship,_graph.SI);
                    if(((Simple_User*) _graph.GetNodes().find(ID3)->second)->getGender()=='M') {
                        _graph.InsertEdge(ID3, ID2, "padre", _graph.SI);
                    }else{
                        _graph.InsertEdge(ID3, ID2, "madre", _graph.SI);
                    }
                }

                if(relationship == "coniuge"){
                    _graph.InsertEdge(ID2,ID3,relationship,_graph.NO);
                }

                if(relationship == "fratello" || relationship == "sorella"){
                    _graph.InsertEdge(ID2,ID3,relationship,_graph.SI);
                    if(((Simple_User*) _graph.GetNodes().find(ID3)->second)->getGender()=='M') {
                        _graph.InsertEdge(ID3, ID2, "fratello", _graph.NO);
                    }else{
                        _graph.InsertEdge(ID3, ID2, "sorella", _graph.NO);
                    }
                }

                //fare per gruppi e aziende
                if(relationship == "consociata"){
                    _graph.InsertEdge(ID2,ID3,relationship,_graph.NO);
                }

                if(relationship == "membro"){
                    _graph.InsertEdge(ID2,ID3,relationship,_graph.NO);
                }
            }
        }
    }
    else{
        _areFilesOpen = false;
    }

    for(map<string,User*>::iterator it = _graph.GetNodes().begin(); it != _graph.GetNodes().end(); it++){
        if(_isSimple(it->second)) {
            ((Simple_User*)((it)->second))->setFatherID(_graph);
            ((Simple_User*)((it)->second))->setMotherID(_graph);
            ((Simple_User*)((it)->second))->setBrotherID(_graph);
            ((Simple_User*)((it)->second))->setSisterID(_graph);
            ((Simple_User*)((it)->second))->setSpouseID(_graph);
        }

        if(_isCompany(it->second)){
            ((Company_User*)((it)->second))->countEmployees(_graph);
            ((Company_User*)((it)->second))->countPartners(_graph);
        }

        if(_isGroup(it->second)){
            ((Group_User*)((it)->second))->countMembers(_graph);
        }

    }

    //lettura file news

    if(file_news.is_open()) {
        while (!file_news.eof()) {
            getline(file_news, line);
            if (_isLineNewsFileGood(line)){

                replace(line.begin(),line.end(), ':', ' ');
                replace(line.begin(),line.end(), ',', ' ');
                replace(line.begin(),line.end(), '{', ' ');
                replace(line.begin(),line.end(), '}', ' ');

                s.clear();
                s >> ID1;
                getline(s,message,']');
                s >> date;
                s >> str_to_ignore;

                do{
                    s >> ID2;
                    if(ID2 != "dislikes"){
                        ID_likes.push_back(ID2);
                        ((Simple_User*)(_graph.GetNodes().find(ID2)->second))->addLikesNumber();
                    }
                }while(ID2 != "dislikes");

                while(!s.eof()){
                    s >> ID3;
                    ID_dislikes.push_back(ID3);
                    ((Simple_User*)(_graph.GetNodes().find(ID2)->second))->addDislikesNumber();
                }

                News* news = new News(Date(date),message,ID1,ID_likes,ID_dislikes);
                _newsList.push_back(news);

            }
        }
    }

    else{
        _areFilesOpen = false;
    }

    if(areFilesOpen()){
        file_news.close();
        file_relationship.close();
        file_info.close();
    }
}

//-----------------------DISTRUTTORE------------------------------
Logger::~Logger(){
    for(map<string,User*>::iterator it = _graph.GetNodes().begin(); it != _graph.GetNodes().end(); it++){
        delete (it->second);
    }

    for(list<News*>::iterator it = _newsList.begin(); it != _newsList.end(); it++){
        delete(*it);
    }
}

//-----------------------METODI BOOLEANI------------------------------

//Metodi booleani passate come "predicato" alle funzioni che si occupano di testare la validità dell' ID, data, ecc.
bool boolIsAlpha(char i){
    return isalpha(i) != 0;
}

bool boolIsDigit(char i){
    return isdigit(i) != 0;
}

bool boolIsBlank(char i){
    return isblank(i) != 0;
}

bool boolIsPunct(char i){
    return ispunct(i) != 0;
}

//Funzioni booleane che si occupano di testare, attraverso il dynamic cast,
// se il parametro passato di tipo puntatore a User sia convertibile a puntatore a SimpleUser, CompanyUser, GroupUser.
bool Logger::_isSimple(User* &user_to_check) {
    return dynamic_cast<Simple_User*>(user_to_check) != nullptr;
}

bool Logger::_isCompany(User* &user_to_check) {
    return dynamic_cast<Company_User*>(user_to_check) != nullptr;
}

bool Logger::_isGroup(User* &user_to_check) {
    return dynamic_cast<Group_User*>(user_to_check) != nullptr;
}

//Metodi booleani per testare la validità dei campi relativi agli utenti che sono presenti nel file.
bool Logger::_isID(string &ID_to_check) {
    int count_alpha = 0,count_num = 0,count_other_c = 0;

    count_alpha = count_if(ID_to_check.begin(),ID_to_check.end(),boolIsAlpha);
    count_num = count_if(ID_to_check.begin(),ID_to_check.end(),boolIsDigit);
    count_other_c = count_if(ID_to_check.begin(),ID_to_check.end(),boolIsBlank);
    count_other_c = count_other_c + count_if(ID_to_check.begin(),ID_to_check.end(), boolIsPunct);

    return !(count_alpha < 4 || count_num > 3 || count_other_c > 0);
}

bool Logger::_isNameOrSurname(string &name_or_surname_to_check) {
    string::iterator it = name_or_surname_to_check.begin();

    while(it != name_or_surname_to_check.end()){
        if(!isalpha(*it)){
            return false;
        }
        it++;
    }
    return true;
}

bool Logger::_isDate(string &date_to_check) {
    string::iterator it = date_to_check.begin();

    if(date_to_check.size() != 10){
        return false;
    }

    if((!isdigit(*it) && *it != '/') || (it == date_to_check.begin()+2 && *it != '/') || (it == date_to_check.begin()+5 && *it != '/')){
        return false;
    }

    Date *date = new Date(date_to_check);
    if(!date->isValid()){
        delete date;
        return false;
    }

    delete date;

    return true;
}

bool Logger::_isAddress(string &address_to_check) {
    string field_to_check;
    int n =0;

    replace(address_to_check.begin(),address_to_check.end(),'-',',');
    istringstream s;
    s.str(address_to_check);

    s >> field_to_check;
    if(!_isNameOrSurname(field_to_check)){
        return false;
    }

    s >> field_to_check;
    n = n + count_if(field_to_check.begin(),field_to_check.end(),[this](char i) {return !boolIsDigit(i); });
    if(n != 0 ){
        return false;
    }

    while(!s.eofbit){
        s >> field_to_check;
        if(!_isNameOrSurname(field_to_check)){
            return false;
        }
    }
}

//Metodi per testare la validità delle singole righe dei tre file facendo uso dei metodi prima implementati.
bool Logger::_isLineUserFileGood(const string &user_file_line) {
    string s_to_check;
    string user_type;
    istringstream s;

    s.clear();
    s.str(user_file_line);

    //controllo su ID e la validità
    getline(s,s_to_check,',');
    if(!_isID(s_to_check)){
        if(_graph.GetNodes().find(s_to_check)== _graph.GetNodes().end()) {
            return false;
        }
    }

    //controllo su usertype
    getline(s,s_to_check,',');
    if(s_to_check != "simple" && s_to_check != "company" && s_to_check != "group"){
        return false;
    }else{
        user_type = s_to_check;
    }

    if(user_type == "simple") {
        //controllo sull'aperta parentesi graffa
        if (s.peek() != '{') {
            return false;
        }

        //controllo su "nome:"
        getline(s, s_to_check, ':');
        if (s_to_check != "nome") {
            return false;
        }

        //controllo sul nome effettivo che deve essere composto da sole lettere
        getline(s, s_to_check, ',');
        if(!_isNameOrSurname(s_to_check)){
            return false;
        }


        //controllo su "cognome:"
        getline(s, s_to_check, ':');
        if (s_to_check != "cognome") {
            return false;
        }

        //controllo sul cognome effettivo che deve essere composto da sole lettere
        getline(s, s_to_check, ',');
        if(!_isNameOrSurname(s_to_check)){
            return false;
        }

        //controllo su "data:"
        getline(s, s_to_check, ':');
        if (s_to_check != "data") {
            return false;
        }

        //controllo su data effettiva
        getline(s, s_to_check, ',');
        if(!_isDate(s_to_check)){
            return false;
        }

        //controllo su "indirizzo:"
        getline(s, s_to_check, ':');
        if (s_to_check != "indirizzo") {
            return false;
        }

        //controllo su indirizzo effettivo
        getline(s, s_to_check, ',');
        if(!_isAddress(s_to_check)){
            return false;
        }

        //controllo su "genere:"
        getline(s, s_to_check, ':');
        if(s_to_check != "genere:"){
            return false;
        }

        //controllo genere effettivo
        getline(s, s_to_check, '}');
        if(s_to_check != "M" || s_to_check != "F" ){
            return false;
        }

    }else{
        if (s.peek() != '{') {
            return false;
         }

        //controllo su "nome:"
        getline(s, s_to_check, ':');
        if (s_to_check != "nome") {
            return false;
        }


        //controllo sul nome effettivo che deve essere composto da sole lettere
        getline(s, s_to_check, ',');
        if(!_isNameOrSurname(s_to_check)){
            return false;
        }

        //controllo su "data:"
        getline(s, s_to_check, ':');
        if (s_to_check != "data") {
            return false;
        }

        //controllo su data effettiva
        getline(s, s_to_check, ',');
        if(!_isDate(s_to_check)){
            return false;
        }

        //controllo su "indirizzo:"
        getline(s, s_to_check, ':');
        if (s_to_check != "indirizzo") {
            return false;
        }

        //controllo su indirizzo effettivo
        getline(s, s_to_check, ',');
        if(!_isAddress(s_to_check)){
            return false;
        }

        if(user_type == "company"){
            //controllo su "prodotto:"
            getline(s,s_to_check,':');
            if(s_to_check != "prodotto"){
                    return false;
            }
            //controllo su prodotto

        }else if (user_type == "group"){
            //controllo su "attività:"
            getline(s,s_to_check,':');
            if(s_to_check != "attività"){
                return false;
            }

            //controllo attività
            getline(s,s_to_check,'}');
            int count_other_c = count_if(s_to_check.begin(),s_to_check.end(),boolIsBlank);
            count_other_c = count_other_c + count_if(s_to_check.begin(),s_to_check.end(), boolIsPunct);
            if(count_other_c != 0){
                return false;
            }
        }


    }

    return true;
}

bool Logger::_isRelationshipGood(const string &ID1,const string &ID2,const string &relationship){
    User* p1 = _graph.findNode(ID1);
    User* p2 = _graph.findNode(ID2);

    if(dynamic_cast<Simple_User*>(p1)!=nullptr) {
        Simple_User *sp1 = (Simple_User *) p1;
        if (relationship == "padre" && sp1->getGender() != 'M')
            return false;
    }

    if(dynamic_cast<Simple_User*>(p1)!=nullptr) {
        Simple_User *sp1 = (Simple_User *) p1;
        if (relationship == "madre" && sp1->getGender() != 'F')
            return false;
    }

    if(dynamic_cast<Simple_User*>(p1)!=nullptr) {
        Simple_User *sp1 = (Simple_User *) p1;
        if (relationship == "fratello" && sp1->getGender() != 'M')
            return false;
    }

    if(dynamic_cast<Simple_User*>(p1)!=nullptr) {
        Simple_User *sp1 = (Simple_User *) p1;
        if (relationship == "sorella" && sp1->getGender() != 'F')
            return false;
    }

    if(dynamic_cast<Simple_User*>(p1)!=nullptr && dynamic_cast<Simple_User*>(p2)!=nullptr) {
        Simple_User *sp1 = (Simple_User *) p1;
        Simple_User *sp2 = (Simple_User *) p2;
        if (relationship == "figlio" && sp1->getDate().yearsFrom() > sp2->getDate().yearsFrom()-16)
            return false;
    }

    if(dynamic_cast<Simple_User*>(p1)!=nullptr && dynamic_cast<Simple_User*>(p2)!=nullptr) {
        Simple_User *sp1 = (Simple_User *) p1;
        Simple_User *sp2 = (Simple_User *) p2;
        if (relationship == "genitore" && sp1->getDate().yearsFrom() > sp2->getDate().yearsFrom()+16)
            return false;
    }
}

bool Logger::_isLineUserRelationshipsFileGood(const string &rel_file_line) {
    string ID1_to_check,ID2_to_check,str_to_check;
    istringstream s;
    s.clear();
    s.str(rel_file_line);

    getline(s,ID1_to_check,',');
    if(!_isID(ID1_to_check)){
        return false;
    }
    getline(s,ID2_to_check,',');
    if(!_isID(ID2_to_check)){
        return false;
    }

    s >> str_to_check;
    if(str_to_check != "padre" && str_to_check != "madre" && str_to_check != "amico" &&
             str_to_check != "conoscente" && str_to_check != "coniuge" && str_to_check != "figlio" &&
             str_to_check != "consociata" && str_to_check != "dipendente" && str_to_check != "membro"&&
             str_to_check != "fratello" && str_to_check != "sorella"){
        return false;
    }

    if(!_isRelationshipGood(ID1_to_check,ID2_to_check,str_to_check)){
        return false;
    }
}

bool Logger::_isLineNewsFileGood(const string &news_file_line) {
    string ID_to_check,s_to_check;
    istringstream s;
    s.clear();
    s.str(news_file_line);

    getline(s,ID_to_check,',');

    if(!_isID(ID_to_check) || _graph.GetNodes().find(ID_to_check)== _graph.GetNodes().end()) {
        return false;
    }

    if(s.peek() != '['){
        return false;
    }else{
        s.ignore('[');
    }

    getline(s,s_to_check,']');

    getline(s,s_to_check,',');
    if(!_isDate(s_to_check)){
        return false;
    }

    getline(s,s_to_check,':');
    if(s_to_check != "likes"){
        return false;
    }

    s.ignore('{');

    s_to_check = "";
    while((*(s_to_check.end()) != '}')){
        getline(s, s_to_check, ',');
        if((*(s_to_check.end()) != '}')) {
            if (!_isID(s_to_check) || _graph.GetNodes().find(s_to_check) == _graph.GetNodes().end()) {
                return false;
            }
        }else{
            s_to_check.pop_back();
            if(!_isID(s_to_check) || _graph.GetNodes().find(s_to_check) == _graph.GetNodes().end()){
                return false;
            }
        }
    }

    getline(s,s_to_check,':');
    if(s_to_check != "dislikes"){
        return false;
    }

    s.ignore('{');

    //modifica perchè alla fine non c'è la virgola
    s_to_check = "";
    while((*(s_to_check.end()) != '}')){
        getline(s, s_to_check, ',');
        if((*(s_to_check.end()) != '}')) {
            if (!_isID(s_to_check) || _graph.GetNodes().find(s_to_check) == _graph.GetNodes().end()) {
                return false;
            }
        }else{
            s_to_check.pop_back();
            if(!_isID(s_to_check) || _graph.GetNodes().find(s_to_check) == _graph.GetNodes().end()){
                return false;
            }
        }
    }

    return true;
}

//Due Metodi per testa l'appartenenza ad un gruppo o l'essere dipendente di un'azienda di un SimpleUser utilizzati nel metodo utile per il sort dei SimpleUser in base alla loro "solitudine"
bool Logger::_isMember(Simple_User* i) {

    for(map<string,vector<string>>::iterator it = _graph.GetEdges(i->getID()).begin(); it != _graph.GetEdges(i->getID()).end(); it++){
        if(find((it->second).begin(),(it->second).end(),"membro") != (it->second).end()){
            return true;
        }
    }

    return false;

}

bool Logger::_isEmployee(Simple_User* i){

    for(map<string,vector<string>>::iterator it = _graph.GetEdges(i->getID()).begin(); it != _graph.GetEdges(i->getID()).end(); it++){
        if(find((it->second).begin(),(it->second).end(),"dipendente") != (it->second).end()){
            return true;
        }
    }

    return false;

}

//Metodo booleano per il sort che ritorna la comparazione tra il rapporto tra like e dislike di due aziende.
bool Logger::_ratioComp (Company_User* i,Company_User* j) {
    return (_getLikesDislikesRatio(i) < _getLikesDislikesRatio(j));
}

//Metodo booleano per il sort che ritorna la comparazione tra il rapporto tra like e dislike di due aziende.
bool Logger::_partnersRatioComp(Company_User* i, Company_User* j) {
    float count_i = 0;
    float count_j = 0;

    for(map<string,vector<string>>::iterator it = _graph.GetEdges(i->getID()).begin(); it != _graph.GetEdges(i->getID()).end(); it++){
        if(find((it->second).begin(), (it->second).end(), "consociata") != (it->second).end()){
            count_i = count_i + _getLikesDislikesRatio((Company_User*)(_graph.GetNodes().find(it->first)->second));
        }
    }

    for(map<string,vector<string>>::iterator it = _graph.GetEdges(j->getID()).begin(); it != _graph.GetEdges(j->getID()).end(); it++){
        if(find((it->second).begin(), (it->second).end(), "consociata") != (it->second).end()){
            count_j = count_j + _getLikesDislikesRatio((Company_User*)(_graph.GetNodes().find(it->first)->second));
        }
    }

    return (count_i < count_j);
}

bool Logger::_lonelinessComp (Simple_User* i,Simple_User* j){
    if ((_reactionsNumber(i) < _reactionsNumber(j))
        && (_isEmployee(i) < _isEmployee(j))
        && (_isMember(i) < _isMember(j))
        && (_relationshipsNumber(i) < _relationshipsNumber(j)))
        return true;

    else if ((_isEmployee(i) < _isEmployee(j))
             && (_isMember(i) < _isMember(j))
             && (_relationshipsNumber(i) < _relationshipsNumber(j)))
        return true;

    else if ((_isMember(i) < _isMember(j))
             && (_relationshipsNumber(i) < _relationshipsNumber(j)))
        return true;

    else return _relationshipsNumber(i) < _relationshipsNumber(j);
}

//-----------------------METODI AZIENDE------------------------------

//Metodo per il calcolo del rapporto tra likes e dislikes per le notizie pubblicate da un'azienda
float Logger::_getLikesDislikesRatio(Company_User *c_user) {
    int tot_likes = 0;
    int tot_dislikes = 0;

    for(list<News*>::iterator it = _newsList.begin();it != _newsList.end(); it++){
        if((*it)->getPublisherID() == (*c_user).getID()){
            tot_likes = tot_likes + (*it)->getDislikesNumber();
            tot_dislikes = tot_dislikes +(*it)->getDislikesNumber();
        }
    }

    return (float)tot_likes/tot_dislikes;
}


int Logger::companyUsersNumber() {

    map<string,User*> tab = _graph.GetNodes();
    int cont = 0;

    for(map<string,User*>::iterator it = tab.begin(); it!=tab.end(); it ++){
        if(_isCompany(it->second)){
            cont++;
        }
    }

    return cont;
}

Company_User* Logger::mostEmployees() {

    map<string,User*> tab = _graph.GetNodes();
    Company_User* company = nullptr;
    Company_User* final_company=nullptr;
    int n;
    int max_employees=0;

    for(map<string,User*>::iterator it = tab.begin(); it!=tab.end(); it++){
        if(_isCompany(it->second)){
            company = (Company_User*)it->second;
            n = company->countEmployees(_graph);
            if(n>=max_employees){
                max_employees=n;
                final_company=company;
            }
        }
    }

    return final_company;
}


//-----------------------METODI GRUPPI------------------------------
int Logger::groupUsersNumber() {

    map<string,User*> tab = _graph.GetNodes();
    int cont = 0;

    for(map<string,User*>::iterator it = tab.begin(); it!=tab.end(); it ++){
        if(_isGroup(it->second)){
            cont++;
        }
    }

    return cont;
}


//-----------------------METODI UTENTI_SEMPLICI------------------------------

//Due altri metodi per il calcolo delle reazioni complessive alle notizie e il numero totale di relazioni di un singolo SimpleUser, utilizzati anch'essi nel sort dei SimpleUser in base alla "solitudine"
int Logger::_reactionsNumber(Simple_User* i){

    return i->getLikesNumber() + i->getDislikesNumber();

}
int Logger::_relationshipsNumber(Simple_User* i){

    int cont = 0;

    cont = i->getFriendsNumber(_graph) + i->getAcquaintancesNumber(_graph) + i->getRelativesNumber(_graph);

    //deve contare anche dipendenti e membri?
    return cont;
}

int Logger::simpleUsersNumber() {
    map<string,User*> tab = _graph.GetNodes();
    int cont = 0;

    for(map<string,User*>::iterator it = tab.begin(); it!=tab.end(); it ++){
        if(_isSimple(it->second)){
            cont++;
        }
    }

    return cont;
}

int Logger::bornAfterDate(Date date) {
    map<string,User*> tab = _graph.GetNodes();
    int cont = 0;

    for(map<string,User*>::iterator it = tab.begin(); it!=tab.end(); it ++){
        if(_isSimple(it->second) && date < it->second->getDate()){
            cont++;
        }
    }

    return cont;
}

Simple_User *Logger::mostFriends() {

    map<string,User*> tab = _graph.GetNodes();
    int max_friends=0;
    int n;
    Simple_User* us = nullptr;
    Simple_User* final_user= nullptr;

    for(map<string,User*>::iterator it = tab.begin(); it!=tab.end(); it++) {
        if (_isSimple(it->second)) {
            us = ((Simple_User *) it->second);
            n = us->getFriendsNumber(_graph);
            if (n >= max_friends) {
                max_friends = n;
                final_user=us;
            }
        }
    }


    return final_user;
}



Simple_User *Logger::mostAcquaintances(){

    map<string,User*> tab = _graph.GetNodes();
    int max_acquaintances=0;
    int n;
    Simple_User* us = nullptr;
    Simple_User* final_user= nullptr;

    for(map<string,User*>::iterator it = tab.begin(); it!=tab.end(); it++) {
        if (_isSimple(it->second)) {
            us = ((Simple_User *) it->second);
            n = us->getAcquaintancesNumber(_graph);
            if (n >= max_acquaintances) {
                max_acquaintances = n;
                final_user = us;
            }

        }
    }

    return final_user;
}

float Logger::ageAverage() {
    unsigned int age_sum = 0;
    map<string,User*> tab = _graph.GetNodes();

    for(map<string,User*>::iterator it = tab.begin(); it != tab.end(); it++) {
        if (_isSimple(it->second)){
            Date* birth_date = new Date(it->second->getDate().str());
            age_sum = age_sum + birth_date->yearsFrom(*birth_date);
            delete birth_date;
        }
    }

    return (float)age_sum/simpleUsersNumber();
}


//-----------------------METODI NEWS------------------------------


News* Logger::mostLikes() {
    News* news = nullptr;
    News *final_news = nullptr;
    int max_likes = 0;
    int n;

    for(list<News*>::iterator it = _newsList.begin(); it != _newsList.end(); it++){
        news = *it;
        n = news->getLikesNumber();
        if (n >= max_likes) {
            max_likes = n;
            final_news = news;
        }
    }

    return final_news;
}

News* Logger::mostDislikes() {
    News* news = nullptr;
    News *final_news = nullptr;
    int max_dislikes = 0;
    int n;

    for(list<News*>::iterator it = _newsList.begin(); it != _newsList.end(); it++){
        news = *it;
        n = news->getLikesNumber();
        if (n >= max_dislikes) {
            max_dislikes = n;
            final_news = news;
        }
    }

    return final_news;
}

void Logger::DisplayTreeR(Simple_User* user, bool risali){
    if (user->getFatherID() != "" && risali) {
        DisplayTreeR((Simple_User *) (_graph.GetNodes().find(user->getFatherID()))->second, risali);
    } else if (user->getFatherID() == "") {
        risali = false;
        cout << "Capostipite : " << user->getName() << endl;
    }

    int i = 1;

    for(map<string,vector<string>>::iterator it = _graph.GetEdges(user->getID()).begin(); it != _graph.GetEdges(user->getID()).end(); it++, i++){
        if(find((it->second).begin(), (it->second).end(), "padre") != (it->second).end() ||
            find((it->second).begin(), (it->second).end(), "madre") != (it->second).end()){
            cout << i << "°Figlio di " << user->getName() << " : " << _graph.GetNodes().find(it->first)->second->getName() << endl;
            DisplayTreeR((Simple_User*)_graph.GetNodes().find(it->first)->second, risali);
        }
    }
}


//----------------------FUNZIONI DI RICERCA-----------------------

void Logger::familyTree(string id_utente){
    User* user;
    user = (_graph.GetNodes().find(id_utente))->second;
    if(_isSimple(user)){
        Simple_User* s_u = (Simple_User*)user;
        DisplayTreeR(s_u,true);
    }
}

vector<Company_User*> Logger::nicestCompany() { //Funzione che ritorna un vettore che contiene le Company in base al loro rapporto tra like e dislike
    map<string,User*> tab = _graph.GetNodes();
    vector<Company_User*> vett;

    for (map<string,User*>::iterator it = tab.begin(); it != tab.end(); it++) { //Scorro la mappa
        if(_isCompany(it->second)){ //Controllo se un elemento del grafo è di tipo Company
            vett.push_back((Company_User*)(it->second)); //Popolamento del vettore di Company
        }
    }
    sort(vett.begin(), vett.end(), [this](Company_User* l, Company_User* r) {return _ratioComp(l, r); });
    return vett;
}

vector<Company_User*> Logger::nicestCompanyPartners() {

    map<string,User*> tab = _graph.GetNodes();

    vector<Company_User*> vett;

    for (map<string,User*>::iterator it = tab.begin() ; it == tab.end() ; it++) {
        if(_isCompany(it->second)){
            vett.push_back((Company_User *) (it->second));
        }
    }

    sort(vett.begin(), vett.end(), [this](Company_User* l, Company_User* r) {return  _partnersRatioComp(l, r); });

    return vett;
}

vector<Simple_User *> Logger::loneWolves() {
    map<string,User*> tab = _graph.GetNodes();
    vector<Simple_User*> vett;
    for (map<string,User*>::iterator it = tab.begin() ; it == tab.end() ; it++) {
        if(_isSimple(it->second))
            vett.push_back((Simple_User*)it->second);
    }
    sort(vett.begin(), vett.end(), [this](Simple_User* l, Simple_User* r) {return _lonelinessComp(l, r); });
    return vett;
}

//----------------------FUNZIONI PER AGGIUNTE/MODIFICHE/CANCELLAZIONI---------------------------
void Logger::addSimpleUser(Simple_User &s_u){
    _graph.InsertNode(s_u.getID(),&s_u);
}
void Logger::addCompanyUser(Company_User &c_u){
    _graph.InsertNode(c_u.getID(),&c_u);
}
void Logger::addGroupUser(Group_User &g_u){
    _graph.InsertNode(g_u.getID(),&g_u);
}
void Logger::removeSimpleUser(string &ID_to_delete){
    _graph.DeleteNode(ID_to_delete);
}
void Logger::removeCompanyUser(const string &ID_to_delete){
    _graph.DeleteNode(ID_to_delete);
}
void Logger::removeGroupUser(const string &ID_to_delete){
    _graph.DeleteNode(ID_to_delete);
}
void Logger::modifySimpleUser(const string &ID_to_modify, const string& name,
                              const string& surname, const Date& date, const Address& address,
                              const char& gender){

    map<string,User*> mappa = _graph.GetNodes();

    if(mappa.find(ID_to_modify) == mappa.end()) {
        cerr << "Errore , non esiste alcun utente con questo id da modificare" << endl;
    }
    else {
        if(_isSimple(mappa.find(ID_to_modify)->second)){
            Simple_User* s_u = (Simple_User*)mappa.find(ID_to_modify)->second;
            if(name != ""){
                s_u->setName(name);
            }
            if(surname != ""){
                s_u->setSurname(surname);
            }
            if(date.str() != ""){
                s_u->setDate(date);
            }
            if(address.str() != ""){
                s_u->setAddress(address);
            }
            if(gender != '\0'){
                s_u->setGender(gender);
            }

        } else
            cerr << "L'Id fornito non corrisponde a quello di un utente semplice" << endl;
    }
}
void Logger::modifyCompanyUser(const string &ID_to_modify, const string& name, const Date& date, const Address& address,
                               const string &product){

    map<string,User*> mappa = _graph.GetNodes();

    if(mappa.find(ID_to_modify) == mappa.end()) {
        cerr << "Errore , non esiste alcun utente con questo id da modificare" << endl;
    }
    else {
        if(_isCompany(mappa.find(ID_to_modify)->second)){
            Company_User* c_u= (Company_User*)mappa.find(ID_to_modify)->second;
            if(name != ""){
                c_u->setName(name);
            }
            if(date.str() != ""){
                c_u->setDate(date);
            }
            if(address.str() != ""){
                c_u->setAddress(address);
            }
            if(product != ""){
                c_u->setProduct(product);
            }

        } else
            cerr << "L'Id fornito non corrisponde a quello di un utente azienda" << endl;
    }
}

void Logger::modifyGroupUser(const string &ID_to_modify, const string& name, const Date& date, const Address& address,
                             const string &activity){
    map<string,User*> mappa = _graph.GetNodes();

    if(mappa.find(ID_to_modify) == mappa.end()) {
        cerr << "Errore , non esiste alcun utente con questo id da modificare" << endl;
    }
    else {
        if(_isGroup(mappa.find(ID_to_modify)->second)){
            Group_User* c_u= (Group_User*)mappa.find(ID_to_modify)->second;
            if(!name.empty()){
                c_u->setName(name);
            }
            if(!date.str().empty()){
                c_u->setDate(date);
            }
            if(!address.str().empty()){
                c_u->setAddress(address);
            }
            if(!activity.empty()){
                c_u->setActivity(activity);
            }

        } else
            cerr << "L'Id fornito non corrisponde a quello di un utente gruppo" << endl;
    }
}

void Logger::addLikeToNews(const string &ID, const string &publisherID, const string &Date) {
    News* news = nullptr;
    for(list<News*>::iterator it = _newsList.begin(); it != _newsList.end(); it++){
        news = *it;
        if(news->getPublisherID() == publisherID && news->getDate().str() == Date){
            news->setNewLike(ID);
        }
    }
}

void Logger::addDisikeToNews(const string &ID, const string &publisherID, const string &Date) {
    News* news = nullptr;
    for(list<News*>::iterator it = _newsList.begin(); it != _newsList.end(); it++){
        news = *it;
        if(news->getPublisherID() == publisherID && news->getDate().str() == Date){
            news->setNewDislike(ID);
        }
    }
}

void Logger::removeLikeToNews(const string &ID, const string &publisherID, const string &Date) {
    News* news = nullptr;
    for(list<News*>::iterator it = _newsList.begin(); it != _newsList.end(); it++){
        news = *it;
        if(news->getPublisherID() == publisherID && news->getDate().str() == Date){
            news->removeLike(ID);
        }
    }
}

void Logger::addDislikeToNews(const string &ID, const string &publisherID, const string &Date) {
    News* news = nullptr;
    for(list<News*>::iterator it = _newsList.begin(); it != _newsList.end(); it++){
        news = *it;
        if(news->getPublisherID() == publisherID && news->getDate().str() == Date){
            news->removeDislike(ID);
        }
    }
}

int Logger::friendsNumberSimpleUser(const string &ID) {
    ((Simple_User*)((_graph.GetNodes().find(ID)->second)))->getFriendsNumber(_graph);
}

int Logger::acquaintancesNumberSimpleUser(const string &ID) {
    ((Simple_User*)((_graph.GetNodes().find(ID)->second)))->getAcquaintancesNumber(_graph);
}

int Logger::partnersNumberCompanyUser(const string &ID) {
    ((Company_User*)((_graph.GetNodes().find(ID)->second)))->countPartners(_graph);
}

int Logger::employeesNumberCompanyUser(const string &ID) {
    ((Company_User*)((_graph.GetNodes().find(ID)->second)))->countEmployees(_graph);
}

int Logger::membersNumberGroupUser(const string &ID) {
    ((Group_User*)((_graph.GetNodes().find(ID)->second)))->countMembers(_graph);
}

int Logger::relativesNumberSimpleUser(const string &ID) {
    ((Simple_User*)((_graph.GetNodes().find(ID)->second)))->getRelativesNumber(_graph);
}

bool Logger::areFilesOpen() {
    return _areFilesOpen;
}





