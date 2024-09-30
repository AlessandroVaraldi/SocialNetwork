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
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

/*Cose da fare:
 * -parametri da utente sia lonewolves sia nicestcompany e nicestcompanypartners;
 * -fare metodi const;
*/

//-----------------------METODO CONTEGGIO PARENTESI GRAFFA------------------------

bool parNumber(const string &s){
    if(s.back() == '}'){
        return true;
    }else return false;
}

Logger::Logger(const string &file_name_1, const string &file_name_2, const string &file_name_3) {
    //variabili d'appoggio mentre leggo il file da passare ai costruttori in una fase successiva
    vector <string> ID_likes;
    vector <string> ID_dislikes;
    string ID1,ID2,ID3,relationship,user_type,activity,address,address_c,product,date,name,surname,gender,message,str_desc,str_to_ignore;
    int par_num =0;
    bool flag = true;
    //variabile in cui salvo ogni riga dei file
    string line;
    //dichiarazione variabili file e stream da cui leggo ciò che mi serve mettere nelle variabili d'appoggio
    istringstream s;
    ifstream file_info, file_relationship, file_news;
    //apertura file
    file_info.open(file_name_1);
    file_relationship.open(file_name_2);
    file_news.open(file_name_3);

    //controllo apertura file informazioni su utenti
    if(file_info.is_open()){
        while(!file_info.eof()) {
            //prende una linea dal file fino al primo spazio, che è alla fine della riga
            getline(file_info, line);
            //condizione che permette di non leggere una linea vuota o uno spazio (creato dalla replace) alla fine del file, prima che la condizione nel while non sia più verificata
            if (!line.empty() && _isUserFileCorrect) {
                par_num = 0;
                flag = true;
                _errorLineNum++;

                s.clear();
                s.str(line);

                getline(s, ID1, ',');
                if(!isID(ID1)){
                    _isUserFileCorrect = false;
                }
                getline(s, user_type, ',');
                if(user_type != "simple" && user_type != "company" && user_type != "group"){
                    _isUserFileCorrect = false;
                }
                //controllo aperta graffa
                s.ignore();
                getline(s, str_desc, ':');
                name.clear(); surname.clear(); date.clear(); address.clear(); address_c.clear(); gender.clear(); product.clear(); activity.clear();
                while ((!str_desc.empty() && flag) && (str_desc == "nome" || str_desc == "cognome" || str_desc == "genere"
                        || str_desc == "data" || str_desc == "indirizzo" || str_desc == "sede_legale" || str_desc == "prodotto" || str_desc == "attività")) {

                    if (str_desc == "cognome") {
                        getline(s, surname, ',');
                        if(parNumber(surname)){ par_num++; surname.pop_back(); flag = false;}
                        getline(s, str_desc, ':');
                        if (!isNameOrSurname(surname) || surname.empty()) {
                            _isUserFileCorrect = false;
                        }
                    }

                    if (str_desc == "nome") {
                        getline(s, name, ',');
                        if(parNumber(name)){ par_num++; name.pop_back(); flag = false;}
                        getline(s, str_desc, ':');
                        if (!isNameOrSurname(name) || name.empty()) {
                            _isUserFileCorrect = false;
                        }

                    }

                    if (str_desc == "data") {
                        getline(s, date, ',');
                        if(parNumber(date)){ par_num++; date.pop_back(); flag = false;}
                        getline(s, str_desc, ':');
                        if (!date.empty() && !isDate(date)) {
                            _isUserFileCorrect = false;
                        }

                    }

                    if (str_desc == "indirizzo") {
                        getline(s, address, ',');
                        if(parNumber(address)){ par_num++; address.pop_back(); flag = false;}
                        getline(s, str_desc, ':');
                        if (!address.empty() && !isAddress(address)) {
                            _isUserFileCorrect = false;
                        }
                    }

                    if (str_desc == "sede_legale") {
                        getline(s, address_c, ',');
                        if(parNumber(address_c)){ par_num++; address_c.pop_back(); flag = false;}
                        getline(s, str_desc, ':');
                        if (!address.empty() && !isAddress(address_c)) {
                            _isUserFileCorrect = false;
                        }
                    }
                    if (str_desc == "genere") {
                        getline(s, gender, ',');
                        if(parNumber(gender)){ par_num++; gender.pop_back(); flag = false;}
                        getline(s, str_desc, ':');
                        if (!gender.empty() && gender != "M" && gender != "F") {
                            _isUserFileCorrect = false;
                        }
                    }

                    if (str_desc == "prodotto") {
                        getline(s, product, ',');
                        if(parNumber(product)){ par_num++; product.pop_back(); flag = false;}
                        getline(s, str_desc, ':');
                    }

                    if (str_desc == "attività") {
                        getline(s, activity, ',');
                        if(parNumber(activity)){ par_num++; activity.pop_back(); flag = false;}
                        getline(s, str_desc, ':');
                    }
                }

            }

            if(par_num > 1){
                _isUserFileCorrect = false;
            }
            if(str_desc != "nome" && str_desc != "cognome" && str_desc != "genere"
               && str_desc != "data" && str_desc != "indirizzo" && str_desc != "sede_legale" && str_desc != "prodotto" && str_desc != "attività") {
                _isUserFileCorrect = false;
            }

            //prendo prima l'ID e il tipo dell'utente in modo da sapere quest'ultimo parametro e regolarmi di conseguenza
            //a seconda del tipo di utente leggo la linea di conseguenza e creo un puntatore ad un oggetto delle classi derivate da User usando la new, e poi lo inserisco nel grafo
            if (_isUserFileCorrect) {
                if (user_type == "simple") {
                    Simple_User *s_ptr = new Simple_User(ID1, name, surname, Date(date), Address(address), gender);
                    _graph.insertNode(ID1, s_ptr);
                } else if (user_type == "company") {
                    Company_User *c_ptr = new Company_User(ID1, name, Date(date), Address(address_c), product);
                    _graph.insertNode(ID1, c_ptr);
                } else if (user_type == "group") {
                Group_User *g_ptr = new Group_User(ID1, name, Date(date), Address(address), activity);
                _graph.insertNode(ID1, g_ptr);
                }
        }

        }
    }else{
        //se il file non è aperto metto un flag a false che ritornerò con un metodo nel main
        _areFilesOpen = false;
    }

    //controllo apertura file sulle relazioni
    if(file_relationship.is_open()){
        if(_isUserFileCorrect){_errorLineNum = 0;}
        //leggo fino ad eof
        while( !file_relationship.eof()){
            //prendo una linea fino al primo spazio ossia fino alla fine
            getline(file_relationship, line);
            //condizione che permette di non leggere una linea vuota o uno spazio (creato dalla replace) alla fine del file, prima che la condizione nel while non sia più verificata
            if(!line.empty() && line != " " && _isUserFileCorrect && _isRelFileCorrect) {
                //chiamo il metodo di test sul file delle relazioni
                if (_isLineUserRelationshipsFileGood(line)) {
                    _errorLineNum++;
                    //rimpiazzo i caratteri di formato con degli spazi
                    replace(line.begin(), line.end(), ',', ' ');
                    //clear dello stream a cui passo in seguito la linea
                    s.clear();
                    s.str(line);
                    //leggo i due ID e la loro relazione
                    s >> ID2 >> ID3 >> relationship;
                    //se leggo padre o madre aggiungo anche la relazione figlio al contrario nel grafo (directed = arco direzionato)
                    if (relationship == "padre" || relationship == "madre") {
                        _graph.insertEdge(ID2, ID3, relationship);
                        _graph.insertEdge(ID3, ID2, "figlio");

                    }
                    //se leggo figlio aggiungo anche la relazione al contrario facendo prima un controllo sul genere del secondo utente
                    if (relationship == "figlio") {
                        _graph.insertEdge(ID2, ID3, relationship);
                        if (((Simple_User *) _graph.getNodes().find(ID3)->second)->getGender() == "M") {
                            _graph.insertEdge(ID3, ID2, "padre");
                        } else {
                            _graph.insertEdge(ID3, ID2, "madre");
                        }
                    }
                    //se leggo amico la relazione al contrario, in questo caso, non essendo descritta da un arco direzionato, è inserita automaticamente dalla insertEdge
                    if (relationship == "amico") {
                        _graph.insertEdge(ID2, ID3, relationship);
                    }
                    //se leggo coniuge la relazione al contrario, in questo caso, non essendo descritta da un arco direzionato, è inserita automaticamente dalla insertEdge
                    if (relationship == "coniuge") {
                        _graph.insertEdge(ID2, ID3, relationship);
                    }
                    //se leggo fratello o sorella la relazione al contrario la devo settare io con un arco direzionato poichè devo fare un controllo preliminare sul sesso
                    if (relationship == "fratello" || relationship == "sorella") {
                        _graph.insertEdge(ID2, ID3, relationship);
                        if (((Simple_User *) _graph.getNodes().find(ID3)->second)->getGender() == "M") {
                            _graph.insertEdge(ID3, ID2, "fratello");
                        } else {
                            _graph.insertEdge(ID3, ID2, "sorella");
                        }
                    }
                    //se leggo consociata la relazione al contrario, in questo caso, non essendo descritta da un arco direzionato, è inserita automaticamente dalla insertEdge
                    if (relationship == "consociata") {
                        _graph.insertEdge(ID2, ID3, relationship);
                        _graph.insertEdge(ID3,ID2,relationship);
                    }
                    //se leggo membro la relazione al contrario, in questo caso, non essendo descritta da un arco direzionato, è inserita automaticamente dalla insertEdge
                    if (relationship == "membro") {
                        _graph.insertEdge(ID2,ID3,relationship);
                        _graph.insertEdge(ID3,ID2,relationship);
                    }
                    if (relationship == "dipendente") {
                        _graph.insertEdge(ID2,ID3,relationship);
                        _graph.insertEdge(ID3,ID2,relationship);
                    }
                }else{
                    _isRelFileCorrect = false;
                }
            }
        }
    }else{
        //se il file non è aperto metto un flag a false che ritornerò con un metodo nel main
        _areFilesOpen = false;
    }

    //creazione usersMap d'appoggio in cui sono salvati i nodi del grafo tramite una chiave identificata dall'ID che permette di accedere al puntatore a User,
    //controllato e castato ogni volta a seconda del tipo di utente considerato
    map<string,User*> usersMap = _graph.getNodes();
    //scorro la usersMap e, a seconda del tipo di utente, chiamo dei metodi propri delle loro classi per settare diversi parametri propri di quei tipi di utente
    for(map<string,User*>::iterator it = usersMap.begin(); it != usersMap.end(); it++){
        if(_isSimple(it->second)){
            //se ho utente semplice setto L'ID del padre,della madre e del coniuge (che serviranno per la creazione dell'albero) chiamando un metodo
            //che vuole come parametro direttamente il grafo costituito
            ((Simple_User*)((it)->second))->setFatherID(_graph);
            ((Simple_User*)((it)->second))->setMotherID(_graph);
            ((Simple_User*)((it)->second))->setSpouseID(_graph);
        }
        if(_isCompany(it->second)){
            //se ho un utente azienda setto il suo numero di dipendenti e consociate
            ((Company_User*)((it)->second))->countEmployees(_graph);
            ((Company_User*)((it)->second))->countPartners(_graph);
        }
        if(_isGroup(it->second)){
            //se ho un utente gruppo setto il suo numero di membri
            ((Group_User*)((it)->second))->countMembers(_graph);
        }
    }

    //controllo apertura file news
    if(file_news.is_open()) {
        if(_isUserFileCorrect && _isRelFileCorrect){_errorLineNum = 0;}
        //leggo fino ad eof
        while (!file_news.eof()) {
            //prendo una linea fino allo spazio ossia fino alla fine della linea
            getline(file_news, line);
            //condizione che permette di non leggere una linea vuota o uno spazio (creato dalla replace) alla fine del file, prima che la condizione nel while non sia più verificata
            if(!line.empty() && line != " " && _isUserFileCorrect && _isRelFileCorrect && _isNewsFileCorrect) {
                //controllo se la linea del file è formattata giusta
                if (_isLineNewsFileGood(line)) {
                    _errorLineNum++;
                    //rimpiazzo i caratteri di formato con degli spazi
                    replace(line.begin(), line.end(), ':', ' ');
                    replace(line.begin(), line.end(), ',', ' ');
                    replace(line.begin(), line.end(), '{', ' ');
                    replace(line.begin(), line.end(), '}', ' ');
                    //devo togliere i due spazi alla fine altrimenti leggerei o duplicati di ID o stringhe vuote dopo, poichè non si verificherebbe s.eof
                    line.erase(line.end()-2,line.end());
                    //clear dello stream e passaggio della linea
                    s.clear();
                    s.str(line);
                    //prendo l'ID del publisher
                    s >> ID1;
                    //ignoro lo spazio e la prima [
                    s.ignore();
                    s.ignore();
                    //prendo il messaggio fino alla ]
                    getline(s, message, ']');
                    //ignoro la ]
                    s.ignore();
                    //prendo la data come stringa
                    s >> date;
                    //ingoro la parola likes
                    s >> str_to_ignore;

                    //clear dei vettori di likes e dislikes
                    ID_dislikes.clear();
                    ID_likes.clear();
                    //fino a quando non trovo la parola dislikes setto il vettore dei likes con gli ID dei likes
                    do {
                        s >> ID2;
                        if (ID2 != "dislikes") {
                            ID_likes.push_back(ID2);
                            //incremento il numero di likes del simpleuser che ha messo like
                            ((Simple_User *) (usersMap.find(ID2)->second))->addLikesNumber();
                        }
                    } while (ID2 != "dislikes");
                    //fino a s.eof  setto il vettore dei dislikes con gli ID dei dislikes
                    while (!s.eof()) {
                        s >> ID3;
                        ID_dislikes.push_back(ID3);
                        //incremento il numero di dislikes del simpleuser che ha messo dislike
                        ((Simple_User *) (usersMap.find(ID3)->second))->addDislikesNumber();
                    }
                    //creo un puntatore ad un oggetto news creato con la new e poi lo metto nella lista di puntatori a news
                    News *news = new News(Date(date), message, ID1, ID_likes, ID_dislikes);
                    _newsList.push_back(news);
                } else {
                    //se la linea del file non è formattata correttamente metto un flag a false che ritornerò con un metodo nel main
                    _isNewsFileCorrect = false;
                }
            }
        }
    }else{
        //se il file non è aperto metto un flag a false che ritornerò con un metodo nel main
        _areFilesOpen = false;
    }
    if(_areFilesOpen){
        file_info.close();
        file_news.close();
        file_relationship.close();
    }
}

//-----------------------DISTRUTTORE------------------------------
Logger::~Logger(){
    map<string,User*> usersMap = _graph.getNodes();
    for(map<string,User*>::iterator it = usersMap.begin(); it != usersMap.end(); it++){
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
//-------------------------METODI PER IL CONTROLLO DEL TIPO DI UTENTE------------------------------
//Funzioni booleane che si occupano di testare, attraverso il dynamic cast,
// se il parametro passato di tipo puntatore a User sia convertibile a puntatore a SimpleUser, CompanyUser, GroupUser.

bool Logger::_isSimple(User* &user_to_check) {
    return dynamic_cast<Simple_User*>(user_to_check) != nullptr;
}

bool Logger::_isCompany(User* &user_to_check) {
    return dynamic_cast<Company_User*>(user_to_check) != nullptr;
}

bool Logger::_isGroup(User* &user_to_check) {
    return dynamic_cast<Group_User *>(user_to_check) != nullptr;
}
//-------------------------METODI PER IL CONTROLLO VALIDITA' CAMPI LINEA FILE UTENTE--------------------------
//Metodi booleani per testare la validità dei campi relativi agli utenti che sono presenti nel file.

//metodo per testare la validità dei cmapi dell'indirizzo
bool Logger::isAddressFieldGood(const string &strfield){
    //in un indirizzo non ci possono essere spazi(i campi sono separati da underscores) nè numeri
    int n = count_if(strfield.begin(),strfield.end(),boolIsBlank) + count_if(strfield.begin(),strfield.end(),boolIsDigit);
    return n == 0;
}
//metodo per testare validità ID che deve avere minimo 4 lettere, massimo 3 numeri e niente caratteri speciali
bool Logger::isID(string &ID_to_check) {
    /*int count_alpha = 0,count_num = 0,count_other_c = 0;

    count_alpha = count_if(ID_to_check.begin(),ID_to_check.end(),boolIsAlpha);
    count_num = count_if(ID_to_check.begin(),ID_to_check.end(),boolIsDigit);
    count_other_c = count_if(ID_to_check.begin(),ID_to_check.end(),boolIsBlank) + count_if(ID_to_check.begin(),ID_to_check.end(), boolIsPunct);

    return !(count_alpha < 4 || count_num > 3 || count_other_c > 0);*/

    return true;
}
//metodo per testare validità di un nome o di un cognome in cui non devono esserci caratteri diversi da lettere
bool Logger::isNameOrSurname(string &name_or_surname_to_check) {
    for( string::iterator it = name_or_surname_to_check.begin(); it != name_or_surname_to_check.end(); it++){
        if(!isalpha(*it)){
            return false;
        }
    }
    return true;
}
//metodo per testare il corretto formato di una data
bool Logger::isDate(string &date_to_check) {
    if(date_to_check.size() != 10){
        return false;
    }

    for(string::iterator it = date_to_check.begin(); it != date_to_check.end(); it++){
        if((!isdigit(*it) && *it != '/') || (it == date_to_check.begin()+2 && *it != '/') || (it == date_to_check.begin()+5 && *it != '/')){
            return false;
        }
    }

    Date *date = new Date(date_to_check);
    if(!date->isValid()){
        delete date;
        return false;
    }
    delete date;

    return true;
}
//metodo per testare la corretta formattazione di un indirizzo
bool Logger::isAddress(string &address_to_check) {
    string street,number,city,region,country;
    int n =0;
    //rimpiazzo i '-' con degli spazi
    replace(address_to_check.begin(),address_to_check.end(),'-',' ');

    istringstream s;
    s.str(address_to_check);

    s >> street >> number >> city >> region >> country;
    //testo i campi dell'indirizzo
    if(!isAddressFieldGood(street) || !isAddressFieldGood(city) || !isAddressFieldGood(region) || !isAddressFieldGood(
            country)){
        return false;
    }
    s.clear();
    //controllo se nella stringa numero ci sono caratteri diversi da dei numeri
    n = n + count_if(number.begin(),number.end(),[this](char i) {return !boolIsDigit(i); });
    return n == 0;

}

//-----------------------METODI PER CONTROLLO VALIDITA' RELAZIONE------------------------
bool Logger::_isRelationshipGood(const string &ID1,const string &ID2,const string &relationship){
    User* u_ptr1 = _graph.getNodes().find(ID1)->second;
    User* u_ptr2 = _graph.getNodes().find(ID2)->second;

    //controlli per vedere se c'è già la stessa relazione ed evitare ripetizioni
    if(_isSimple(u_ptr1)) {
        map<string,vector<string>> mappa_rel = _graph.getEdges(((Simple_User*)u_ptr1)->getID());
        if(_isSimple(u_ptr2)) {
            if (relationship == "padre" || relationship == "madre" || relationship == "figlio"
                || relationship == "fratello" || relationship == "sorella" || relationship == "amico" ||
                relationship == "conoscente" || relationship == "coniuge") {
                if (mappa_rel.find(((Simple_User*)u_ptr2)->getID()) != mappa_rel.end()){
                    map<string,vector<string>>::iterator it = mappa_rel.find(((Simple_User*)u_ptr2)->getID());
                    if(find((it->second).begin(),(it->second).end(),relationship) != (it->second).end()) {
                        return false;
                    }
                }
            }
        }else{
            if(_isCompany(u_ptr2)){
                if(relationship == "dipendente"){
                    if (mappa_rel.find(((Company_User*)u_ptr2)->getID()) != mappa_rel.end()){
                        return false;
                    }
                }
            }
            else{
                if(_isGroup(u_ptr2)){
                    if(relationship == "membro"){
                        if (mappa_rel.find(((Group_User*)u_ptr2)->getID()) != mappa_rel.end()){
                            return false;
                        }
                    }
                }
            }
        }
    }

    if(_isCompany(u_ptr1)){
        map<string,vector<string>> mappa_rel = _graph.getEdges(((Company_User*)u_ptr1)->getID());
        if(_isSimple(u_ptr2)){
            if(relationship == "dipendente"){
                if (mappa_rel.find(((Simple_User*)u_ptr2)->getID()) != mappa_rel.end()){
                    return false;
                }
            }
        }else{
            if(_isCompany(u_ptr2)){
                if(relationship == "consociata"){
                    if (mappa_rel.find(((Company_User*)u_ptr2)->getID()) != mappa_rel.end()){
                        return false;
                    }
                }
            }
        }
    }

    if(_isGroup(u_ptr1)){
        map<string,vector<string>> mappa_rel = _graph.getEdges(((Group_User*)u_ptr1)->getID());
        if(_isSimple(u_ptr2)) {
            if (relationship == "membro") {
                if (mappa_rel.find(((Simple_User *) u_ptr2)->getID()) != mappa_rel.end()) {
                    return false;
                }
            }
        }
    }

    if(_isSimple(u_ptr1) && _isSimple(u_ptr2)) {
        Simple_User *s_ptr1 = (Simple_User *) u_ptr1; Simple_User *s_ptr2 = (Simple_User *) u_ptr1;

        if (relationship == "padre" && s_ptr1->getGender() != "M")
            return false;
        if (relationship == "madre" && s_ptr1->getGender() != "F")
            return false;
        if (relationship == "fratello" && s_ptr1->getGender() != "M")
            return false;
        if (relationship == "sorella" && s_ptr1->getGender() != "F")
            return false;
        if(relationship == "padre")
            if(s_ptr2->getFatherID() != "")
                return false;
        if(relationship == "madre")
            if(s_ptr2->getMotherID() != "")
                return false;
    }

    if((_isSimple(u_ptr1) && _isCompany(u_ptr2) || (_isCompany(u_ptr1) && _isSimple(u_ptr2))))
            if(relationship != "dipendente")
                return false;
    if(_isCompany(u_ptr2) && _isCompany(u_ptr1))
        if(relationship != "consociata")
            return false;
    if((_isSimple(u_ptr1) && _isGroup(u_ptr2) || (_isCompany(u_ptr1) && _isGroup(u_ptr2))))
        if(relationship != "membro")
            return false;


    return true;

}

//--------------Metodi per testare la validità delle singole righe dei tre file facendo uso dei metodi prima implementati-----------------
bool Logger::_isLineUserRelationshipsFileGood(const string &rel_file_line) {
    string ID1_to_check,ID2_to_check,str_to_check;
    istringstream s;
    s.clear();
    s.str(rel_file_line);

    getline(s,ID1_to_check,',');
    if(!isID(ID1_to_check)){
        return false;
    }
    getline(s,ID2_to_check,',');
    if(!isID(ID2_to_check)){
        return false;
    }

    s >> str_to_check;
    if(str_to_check != "padre" && str_to_check != "madre" && str_to_check != "amico" &&
             str_to_check != "conoscente" && str_to_check != "coniuge" && str_to_check != "figlio" &&
             str_to_check != "consociata" && str_to_check != "dipendente" && str_to_check != "membro"&&
             str_to_check != "fratello" && str_to_check != "sorella"){
        return false;
    }

    return _isRelationshipGood(ID1_to_check, ID2_to_check, str_to_check);

}

bool Logger::_isLineNewsFileGood(const string &news_file_line) {
    string ID_to_check,s_to_check;
    istringstream s;
    s.clear();
    s.str(news_file_line);

    getline(s,ID_to_check,',');

    if(!isID(ID_to_check) || _graph.getNodes().find(ID_to_check)== _graph.getNodes().end()) {
        return false;
    }

    if(s.peek() != '['){
        return false;
    }else{
        s.ignore();
    }

    getline(s,s_to_check,']');

    if(s.peek() != ','){
        return false;
    }else{
        s.ignore();
    }

    getline(s,s_to_check,',');
    if(!isDate(s_to_check)){
        return false;
    }

    getline(s,s_to_check,':');
    if(s_to_check != "likes"){
        return false;
    }

    if(s.peek() != '{') {
        return false;
    }else{
        s.ignore();
    }

    s_to_check = "";

    while(s_to_check.back() != '}'){
        getline(s, s_to_check, ',');
        if(s_to_check.back() != '}') {
            if (!isID(s_to_check) || _graph.getNodes().find(s_to_check) == _graph.getNodes().end()) {
                return false;
            }
        }else{
            s_to_check.pop_back();
            if(!isID(s_to_check) || _graph.getNodes().find(s_to_check) == _graph.getNodes().end()){
                return false;
            }
            s_to_check.push_back('}');
        }
    }

    getline(s,s_to_check,':');
    if(s_to_check != "dislikes"){
        return false;
    }

    if(s.peek() != '{') {
        return false;
    }else{
        s.ignore();
    }

    //modifica perchè alla fine non c'è la virgola
    s_to_check = "";
    while( s_to_check.back() != '}'){
        getline(s, s_to_check, ',');
        if(s_to_check.back()  != '}') {
            if (!isID(s_to_check) || _graph.getNodes().find(s_to_check) == _graph.getNodes().end()) {
                return false;
            }
        }else{
            s_to_check.pop_back();
            if(!isID(s_to_check) || _graph.getNodes().find(s_to_check) == _graph.getNodes().end()){
                return false;
            }
            s_to_check.push_back('}');
        }
    }

    return true;
}
//-----------------------METODI AZIENDE------------------------------
//metodo che testa l'essere dipendente di un'azienda di un SimpleUser utilizzato nel metodo utile per il sort dei SimpleUser in base alla loro "solitudine"
bool Logger::_isEmployee(Simple_User* i){
    map<string,vector<string>> relationshipMap = _graph.getEdges(i->getID());
    for(map<string,vector<string>>::iterator it = relationshipMap.begin(); it != relationshipMap.end(); it++){
        if(find((it->second).begin(),(it->second).end(),"dipendente") != (it->second).end()){
            return true;
        }
    }

    return false;

}

int Logger::partnersNumberCompanyUser(const string &ID) {
    map<string,User*> usersMap = _graph.getNodes();
    if(_isCompany(usersMap.find(ID)->second)) {
        return ((Company_User *) (usersMap.find(ID)->second))->countPartners(_graph);
    }else{
        return -1;
    }
}

int Logger::employeesNumberCompanyUser(const string &ID) {
    map<string,User*> usersMap = _graph.getNodes();
    if(_isCompany(usersMap.find(ID)->second)) {
        return ((Company_User *) ((usersMap.find(ID)->second)))->countEmployees(_graph);
    }else{
        return -1;
    }
}


//Metodo booleano per il sort che ritorna la comparazione tra il rapporto tra like e dislike di due aziende, utile per la classifica di simpatia delle aziende.
bool Logger:: _ratioComp (Company_User* i,Company_User* j) {
    return (_getLikesDislikesRatio(i) > _getLikesDislikesRatio(j));
}

//Metodo booleano per il sort che ritorna la comparazione tra il rapporto tra like e dislike di due aziende considerando anche le consociate.
bool Logger::_partnersRatioComp(Company_User* i, Company_User* j) {
    float count_i = 0;
    float count_j = 0;
    map<string,vector<string>> relationshipsMap1 = _graph.getEdges(i->getID());
    map<string,vector<string>> relationshipsMap2 = _graph.getEdges(j->getID());
    map<string,User*> usersMap = _graph.getNodes();

    for(map<string,vector<string>>::iterator it = relationshipsMap1.begin(); it != relationshipsMap1.end(); it++){
        if(find((it->second).begin(), (it->second).end(), "consociata") != (it->second).end()){
            count_i = count_i + _getLikesDislikesRatio((Company_User*)(usersMap.find(it->first)->second));
        }
    }

    for(map<string,vector<string>>::iterator it = relationshipsMap2.begin(); it != relationshipsMap2.end(); it++){
        if(find((it->second).begin(), (it->second).end(), "consociata") != (it->second).end()){
            count_j = count_j + _getLikesDislikesRatio((Company_User*)(usersMap.find(it->first)->second));
        }
    }

    return (count_i > count_j);
}

//Metodo per il calcolo del rapporto tra likes e dislikes per le notizie pubblicate da un'azienda
float Logger::_getLikesDislikesRatio(Company_User *c_user) {
    int likes_number = 0;
    int dislikes_number = 0;

    for(list<News*>::iterator it = _newsList.begin();it != _newsList.end(); it++){
        if((*it)->getPublisherID() == (*c_user).getID()){
            likes_number = likes_number + (*it)->getLikesNumber();
            dislikes_number = dislikes_number +(*it)->getDislikesNumber();
        }
    }

    if(dislikes_number != 0) {
        return ((float) likes_number / (float) dislikes_number);
    }else{
        return (float)likes_number;
    }
}

//metodo per il conteggio degli utenti azienda
int Logger::companyUsersNumber() {

    map<string,User*> tab = _graph.getNodes();
    int cont = 0;

    for(map<string,User*>::iterator it = tab.begin(); it!=tab.end(); it ++){
        if(_isCompany(it->second)){
            cont++;
        }
    }

    return cont;
}

//metodo per individuare l'azienda con il maggior numero di dipendenti
void Logger::mostEmployees() {

    map<string,User*> usersMap = _graph.getNodes();
    Company_User* company = nullptr;
    Company_User* final_company = nullptr;
    vector<Company_User*> most_emp_vett;
    int n, max_employees = 0;

    for(map<string,User*>::iterator it = usersMap.begin(); it!=usersMap.end(); it++){
        if(_isCompany(it->second)){
            company = (Company_User*)it->second;
            n = company->countEmployees(_graph);
            if(n > max_employees){
                most_emp_vett.clear();
                max_employees = n;
                most_emp_vett.push_back(company);
            }else{
                if(n == max_employees){
                    most_emp_vett.push_back(company);
                }
            }
        }
    }

    if(max_employees > 0) {
        cout << "L'utente azienda con più dipendenti e'/sono: " << endl;
        for (vector<Company_User *>::iterator it = most_emp_vett.begin();
             it != most_emp_vett.end(); it++) {
            cout << (*it)->getName() << endl;
        }
    }else{
        cout << "Nessuna azienda ha dei dipendenti" << endl;
    }
}

//-----------------------METODI GRUPPI------------------------------
//metodo che testa l'appartenenza ad un gruppo  di un SimpleUser utilizzato nel metodo utile per il sort dei SimpleUser in base alla loro "solitudine"
bool Logger::_isMember(Simple_User* i) {
    map<string,vector<string>> relationshipsMap = _graph.getEdges(i->getID());
    for(map<string,vector<string>>::iterator it = relationshipsMap.begin(); it != relationshipsMap.end(); it++){
        if(find((it->second).begin(),(it->second).end(),"membro") != (it->second).end()){
            return true;
        }
    }

    return false;

}
int Logger::membersNumberGroupUser(const string &ID) {
    map<string,User*> _usersMap = _graph.getNodes();
    if(_isGroup(_usersMap.find(ID)->second)) {
        return ((Group_User *) ((_usersMap.find(ID)->second)))->countMembers(_graph);
    }else{
        return -1;
    }
}

//metodo per calcolare il numero di utenti gruppo
int Logger::groupUsersNumber() {

    map<string,User*> usersMap = _graph.getNodes();
    int cont = 0;

    for(map<string,User*>::iterator it = usersMap.begin(); it!=usersMap.end(); it ++){
        if(_isGroup(it->second)){
            cont++;
        }
    }

    return cont;
}


//-----------------------METODI UTENTI_SEMPLICI------------------------------
//metodo che compara due utenti semplici con criteri di "solitudine" quali essere o meno membro di un gruppo, numero di likes e dislikes, ecc...
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

//Due altri metodi per il calcolo delle reazioni complessive alle notizie e il numero totale di relazioni di un singolo SimpleUser, utilizzati anch'essi nel sort dei SimpleUser in base alla "solitudine"
int Logger::_reactionsNumber(Simple_User* i){
    return i->getLikesNumber() + i->getDislikesNumber();
}

int Logger::_relationshipsNumber(Simple_User* i){

    int cont = 0;
    int cont_1 = 0;
    cont = i->getFriendsNumber(_graph) + i->getAcquaintancesNumber(_graph) + i->getRelativesNumber(_graph,cont_1,true,i->getID(),true);

    return cont;
}

//metodo per il conteggio degli utenti semplici
int Logger::simpleUsersNumber() {
    map<string,User*> usersMap = _graph.getNodes();
    int cont = 0;

    for(map<string,User*>::iterator it = usersMap.begin(); it!=usersMap.end(); it ++){
        if(_isSimple(it->second)){
            cont++;
        }
    }

    return cont;
}

//metodo del conteggio degli utenti semplici nati dopo una certa data
int Logger::bornAfterDate(Date date) {
    map<string,User*> usersMap = _graph.getNodes();
    int cont = 0;

    for(map<string,User*>::iterator it = usersMap.begin(); it!=usersMap.end(); it ++){
        if(_isSimple(it->second) && date < it->second->getDate()){
            cont++;
        }
    }

    return cont;
}

int Logger::friendsNumberSimpleUser(const string &ID){
    map<string,User*> usersMap = _graph.getNodes();
    if(_isSimple(usersMap.find(ID)->second)) {
        return ((Simple_User *) ((usersMap.find(ID)->second)))->getFriendsNumber(_graph);
    }else{
        return -1;
    }
}

int Logger::acquaintancesNumberSimpleUser(const string &ID) {
    map<string,User*> usersMap = _graph.getNodes();
    if(_isSimple(usersMap.find(ID)->second)) {
        return ((Simple_User *) ((usersMap.find(ID)->second)))->getAcquaintancesNumber(_graph);
    }else{
        return -1;
    }
}

int Logger::relativesNumberSimpleUser(const string &ID) {
    map<string,User*> _usersMap = _graph.getNodes();
    Simple_User* s_ptr;
    int cont=0;
    if(_isSimple(_usersMap.find(ID)->second)) {
        s_ptr = ((Simple_User *) (_usersMap.find(ID)->second));
        return s_ptr->getRelativesNumber(_graph,cont,true,ID,true);
    }else{
        return -1;
    }
}

//metodo che ritorna un puntatore all'utente semplice con il maggior numero di amici
void Logger::mostFriends() {
    vector<Simple_User*> most_fr_vett;
    map<string,User*> usersMap = _graph.getNodes();
    int n, max_friends=0;
    Simple_User *s_ptr = nullptr, *final_user = nullptr;

    for(map<string,User*>::iterator it = usersMap.begin(); it!=usersMap.end(); it++) {
        if (_isSimple(it->second)) {
            s_ptr = ((Simple_User *) it->second);
            n = s_ptr->getFriendsNumber(_graph);
            if (n > max_friends) {
                most_fr_vett.clear();
                max_friends = n;
                most_fr_vett.push_back(s_ptr);
            }else{
                if(n == max_friends){
                    most_fr_vett.push_back(s_ptr);
                }
            }
        }
    }


    if(max_friends > 0) {
        cout << "L'utente semplice con più amici e'/sono: " << endl;
        for (vector<Simple_User *>::iterator it = most_fr_vett.begin();
             it != most_fr_vett.end(); it++) {
            cout << (*it)->getName() << endl;
        }
    }else {
        cout << "Nessun utente semplice ha degli amici" << endl;
    }
}

//metodo che ritorna un puntatore all'utente semplice con il maggior numero di conoscenti
void
Logger::mostAcquaintances(){
    vector<Simple_User*> most_acq_vett;
    map<string,User*> usersMap = _graph.getNodes();
    int n = 0, max_acquaintances = 0;
    Simple_User *us = nullptr, *final_user= nullptr;

    for(map<string,User*>::iterator it = usersMap.begin(); it!=usersMap.end(); it++) {
        if (_isSimple(it->second)) {
            us = ((Simple_User *) it->second);
            n = us->getAcquaintancesNumber(_graph);
            if (n > max_acquaintances) {
                most_acq_vett.clear();
                max_acquaintances = n;
                most_acq_vett.push_back(us);
            }else{
                if(n == max_acquaintances){
                    most_acq_vett.push_back(us);
                }
            }
        }
    }

    if(max_acquaintances > 0) {
        cout << "L'utente semplice con più conoscenti e'/sono: " << endl;
        for (vector<Simple_User *>::iterator it = most_acq_vett.begin();
             it !=most_acq_vett.end(); it++) {
            cout << (*it)->getName() << endl;
        }
    }else {
        cout << "Nessun utente semplice ha dei conoscenti" << endl;
    }
}

//metodo per il calcolo dell'età media degli utenti semplici
float Logger::ageAverage() {
    unsigned int age_sum = 0;
    map<string,User*> usersMap = _graph.getNodes();

    for(map<string,User*>::iterator it = usersMap.begin(); it != usersMap.end(); it++) {
        if (_isSimple(it->second)){
            Date* birth_date = new Date(it->second->getDate().str());
            age_sum = age_sum + birth_date->yearsFrom(*birth_date);
            delete birth_date;
        }
    }

    return (float)age_sum/(float)simpleUsersNumber();
}


//-----------------------METODI NEWS------------------------------
//metodo che ritorna un puntatore alla news con più likes
void Logger::mostLikes() {
    vector <News*> vett_max_likes;
    News *news = nullptr;
    int n, max_likes = 0;

    for(list<News*>::iterator it = _newsList.begin(); it != _newsList.end(); it++){
        news = *it;
        n = news->getLikesNumber();
        if (n > max_likes) {
            vett_max_likes.clear();
            max_likes = n;
            vett_max_likes.push_back(news);
        }else{
            if(n == max_likes){
                vett_max_likes.push_back(news);
            }
        }
    }

    if(max_likes != 0){
        cout << "La notizia con più likes e'/sono: " << endl;
        for(vector<News*>::iterator it = vett_max_likes.begin(); it != vett_max_likes.end(); it++){
            cout << (*it)->getMessage() << " pubblicata da: " << (*it)->getPublisherID() << endl;
        }
    }else{
        cout << "nessuna notizia ha dei likes" << endl;
    }
}
//metodo che ritorna un puntatore alla news con più dislikes
void Logger::mostDislikes() {
    vector <News*> vett_max_dislikes;
    News *news = nullptr;
    int n, max_dislikes = 0;

    for(list<News*>::iterator it = _newsList.begin(); it != _newsList.end(); it++){
        news = *it;
        n = news->getLikesNumber();
        if (n > max_dislikes) {
            vett_max_dislikes.clear();
            max_dislikes = n;
            vett_max_dislikes.push_back(news);
        }else{
            if(n == max_dislikes){
                vett_max_dislikes.push_back(news);
            }
        }
    }

    if(max_dislikes != 0){
        cout << "La notizia con più dislikes e'/sono: " << endl;
        for(vector<News*>::iterator it = vett_max_dislikes.begin(); it != vett_max_dislikes.end(); it++){
            cout << (*it)->getMessage() << " pubblicata da: " << (*it)->getPublisherID() << endl;
        }
    }else{
        cout << "nessuna notizia ha dei dislikes" << endl;
    }
}

//----------------------FUNZIONI DI RICERCA-----------------------
//funzione ricorsiva che costruisce e stampa l'albero genealogico
void Logger::displayTree(Simple_User *user, bool is_founder, ofstream &file){
    map<string,User*> usersMap = _graph.getNodes();
    map<string,vector<string>> relationshipsMap = _graph.getEdges(user->getID());
    string str;
    Simple_User* s_ptr;
    int i = 0 , j = 0;

    if (!user->getFatherID().empty() && is_founder) {
        str = user->getFatherID();
        s_ptr = (Simple_User *) (usersMap.find(str))->second;
        displayTree(s_ptr, is_founder, file);
        return;
    } 
    else if (user->getFatherID().empty() && is_founder) {
        is_founder = false;
        file << "Capostipite: " << user->getName() << endl;
    }
    
    for(map<string,vector<string>>::iterator it = relationshipsMap.begin(); it != relationshipsMap.end(); it++, j++){
        if(find((it->second).begin(), (it->second).end(), "padre") != (it->second).end() || find((it->second).begin(), (it->second).end(), "madre") != (it->second).end()){
            i++;
            file << " " << i << "° figlio di " << user->getName() << ": " << usersMap.find(it->first)->second->getName() << endl;
            s_ptr = (Simple_User*)usersMap.find(it->first)->second;
            displayTree(s_ptr, is_founder, file);
        }
    }
}

void Logger::familyTree(string ID, const string &filename){
    User* u_ptr;
    Simple_User* s_ptr;
    ofstream file;
    map<string,User*> usersMap = _graph.getNodes();
    u_ptr = (usersMap.find(ID))->second;

    file.open(filename);
    if(_isSimple(u_ptr)){
        s_ptr = (Simple_User*)u_ptr;
        displayTree(s_ptr, true, file);
    }
    file.close();
}
//Funzione che ritorna un vettore che contiene le Company ordinate in base al loro rapporto tra likes e dislikes
vector<Company_User*> Logger::nicestCompany() {
    map<string,User*> usersMap = _graph.getNodes();
    vector<Company_User*> vect;

    for (map<string,User*>::iterator it = usersMap.begin(); it != usersMap.end(); it++) { //Scorro la mappa
        if(_isCompany(it->second)){ //Controllo se un elemento del grafo è di tipo Company
            vect.push_back((Company_User*)(it->second)); //Popolamento del vettore di Company
        }
    }
    sort(vect.begin(), vect.end(), [this](Company_User* l, Company_User* r) {return _ratioComp(l, r); });
    return vect;
}
//Funzione che ritorna un vettore che contiene le Company ordinate in base al loro rapporto tra likes e dislikes e considerando anche le consociate
vector<Company_User*> Logger::nicestCompanyPartners() {
    map<string,User*> usersMap = _graph.getNodes();
    vector<Company_User*> vect;

    for (map<string,User*>::iterator it = usersMap.begin() ; it == usersMap.end() ; it++) {
        if(_isCompany(it->second)){
            vect.push_back((Company_User*)(it->second));
        }
    }

    sort(vect.begin(), vect.end(), [this](Company_User* l, Company_User* r) {return  _partnersRatioComp(l, r); });

    return vect;
}
//Funzione che ritorna un vettore che contiene gli utenti semplici ordinati secondo lonelinesscomp
vector<Simple_User *> Logger::loneWolves() {
    map<string,User*> usersMap = _graph.getNodes();
    vector<Simple_User*> vect;

    for (map<string,User*>::iterator it = usersMap.begin() ; it != usersMap.end() ; it++) {
        if(_isSimple(it->second)) {
            vect.push_back((Simple_User *) (it->second));
        }
    }
    sort(vect.begin(), vect.end(), [this](Simple_User* l, Simple_User* r) {return _lonelinessComp(l, r); });
    return vect;
}

//----------------------FUNZIONI PER AGGIUNTE/MODIFICHE/CANCELLAZIONI---------------------------
void Logger::addSimpleUser(const string &ID, const string & name, const string & surname, const string &date, string &address, const string &gender){
    Simple_User* s_ptr = new Simple_User(ID,name,surname,Date(date),Address(address),gender);
    _graph.insertNode(ID,s_ptr);
}
void Logger::addCompanyUser(const string &ID, const string & name, const string &date, string &address, const string &product){
    Company_User* c_ptr = new Company_User(ID,name,Date(date),Address(address),product);
    _graph.insertNode(ID,c_ptr);
}
void Logger::addGroupUser(const string &ID, const string & name, const string &date, string &address, const string &activity){
    Group_User* g_ptr = new Group_User(ID,name,Date(date),Address(address),activity);
    _graph.insertNode(ID, g_ptr);
}
void Logger::removeSimpleUser(const string &ID_to_delete){
    _graph.deleteNode(ID_to_delete);
}
void Logger::removeCompanyUser(const string &ID_to_delete){
    _graph.deleteNode(ID_to_delete);
}
void Logger::removeGroupUser(const string &ID_to_delete){
    _graph.deleteNode(ID_to_delete);
}
void Logger::modifySimpleUser(const string &ID_to_modify, string fields_to_assign[]){
    map<string,User*> usersMap = _graph.getNodes();
    int err = 0;

    if(usersMap.find(ID_to_modify) == usersMap.end()) {
        cerr << "Errore , non esiste alcun utente con questo id da modificare" << endl;
        err = -1;
    }
    else {
        if(_isSimple(usersMap.find(ID_to_modify)->second)){
            Simple_User* s_ptr = (Simple_User*)usersMap.find(ID_to_modify)->second;
            if(!fields_to_assign[0].empty()){
                s_ptr->setName(fields_to_assign[0]);
            }
            if(!fields_to_assign[1].empty()){
                s_ptr->setSurname(fields_to_assign[1]);
            }
            if(!fields_to_assign[2].empty()){
                Date data(fields_to_assign[2]);
                s_ptr->setDate(data);
            }
            if(!fields_to_assign[3].empty()){
                Address address(fields_to_assign[3]);
                s_ptr->setAddress(address);
            }
            if(!fields_to_assign[4].empty()){
                s_ptr->setGender(fields_to_assign[4]);
            }
            if(!fields_to_assign[5].empty()){
                s_ptr->setID(fields_to_assign[5]);
            }
        } else
            cerr << "L'Id fornito non corrisponde a quello di un utente semplice" << endl;
    }

    if(err != 0) {
        if (!fields_to_assign[5].empty()) {
            _graph.modifyNodesKey(ID_to_modify, fields_to_assign[5]);
            _graph.modifyEdgesKey(ID_to_modify, fields_to_assign[5]);
        }
    }
}
void Logger::modifyCompanyUser(const string &ID_to_modify, string fields_to_assign[]){
    map<string,User*> usersMap = _graph.getNodes();
    int err = 0;

    if(usersMap.find(ID_to_modify) == usersMap.end()) {
        cerr << "Errore , non esiste alcun utente con questo id da modificare" << endl;
        err = -1;
    }
    else {
        if(_isCompany(usersMap.find(ID_to_modify)->second)){
            Company_User* s_ptr = (Company_User*)usersMap.find(ID_to_modify)->second;
            if(!fields_to_assign[0].empty()){
                s_ptr->setName(fields_to_assign[0]);
            }
            if(!fields_to_assign[1].empty()){
                Date data(fields_to_assign[1]);
                s_ptr->setDate(data);
            }
            if(!fields_to_assign[2].empty()){
                Address address(fields_to_assign[2]);
                s_ptr->setAddress(address);
            }
            if(!fields_to_assign[3].empty()){
                s_ptr->setProduct(fields_to_assign[3]);
            }
            if(!fields_to_assign[4].empty()){
                s_ptr->setID(fields_to_assign[4]);
            }
        } else
            cerr << "L'Id fornito non corrisponde a quello di un utente azienda" << endl;
    }

    if(err != 0) {
        if (!fields_to_assign[4].empty()) {
            _graph.modifyNodesKey(ID_to_modify, fields_to_assign[4]);
            _graph.modifyEdgesKey(ID_to_modify, fields_to_assign[4]);
        }
    }

}

void Logger::modifyGroupUser(const string &ID_to_modify, string fields_to_assign[]){
    map<string,User*> usersMap = _graph.getNodes();
    int err = 0;

    if(usersMap.find(ID_to_modify) == usersMap.end()) {
        cerr << "Errore , non esiste alcun utente con questo id da modificare" << endl;
        err = -1;
    }
    else {
        if(_isGroup(usersMap.find(ID_to_modify)->second)){
            Group_User* s_ptr = (Group_User*)usersMap.find(ID_to_modify)->second;
            if(!fields_to_assign[0].empty()){
                s_ptr->setName(fields_to_assign[0]);
            }
            if(!fields_to_assign[1].empty()){
                Date data(fields_to_assign[1]);
                s_ptr->setDate(data);
            }
            if(!fields_to_assign[2].empty()){
                Address address(fields_to_assign[2]);
                s_ptr->setAddress(address);
            }
            if(!fields_to_assign[3].empty()){
                s_ptr->setActivity(fields_to_assign[3]);
            }
            if(!fields_to_assign[4].empty()){
                s_ptr->setID(fields_to_assign[4]);
            }
        } else
            cerr << "L'Id fornito non corrisponde a quello di un utente gruppo" << endl;
    }

    if(err != 0) {
        if (!fields_to_assign[4].empty()) {
            _graph.modifyNodesKey(ID_to_modify, fields_to_assign[4]);
            _graph.modifyEdgesKey(ID_to_modify, fields_to_assign[4]);
        }
    }
}

void Logger::addLikeToNews(const string &ID, const string &publisherID, const string &Date, const string &message) {
    News* news = nullptr;
    for(list<News*>::iterator it = _newsList.begin(); it != _newsList.end(); it++){
        news = *it;
        if(news->getPublisherID() == publisherID && news->getDate().str() == Date && news->getMessage() == message){
            news->setNewLike(ID);
        }
    }
}

void Logger::addDislikeToNews(const string &ID, const string &publisherID, const string &Date, const string &message) {
    News* news = nullptr;
    for(list<News*>::iterator it = _newsList.begin(); it != _newsList.end(); it++){
        news = *it;
        if(news->getPublisherID() == publisherID && news->getDate().str() == Date && news->getMessage() == message){
            news->setNewDislike(ID);
        }
    }
}

void Logger::removeLikeToNews(const string &ID, const string &publisherID, const string &Date,const string &message) {
    News* news = nullptr;
    for(list<News*>::iterator it = _newsList.begin(); it != _newsList.end(); it++){
        news = *it;
        if(news->getPublisherID() == publisherID && news->getDate().str() == Date && news->getMessage() == message){
            news->removeLike(ID);
        }
    }
}

void Logger::removeDislikeToNews(const string &ID, const string &publisherID, const string &Date, const string &message) {
    News* news = nullptr;
    for(list<News*>::iterator it = _newsList.begin(); it != _newsList.end(); it++){
        news = *it;
        if(news->getPublisherID() == publisherID && news->getDate().str() == Date && news->getMessage() == message){
            news->removeDislike(ID);
        }
    }
}

//funzione che permette nel menù di dire se un utente è veramente presente nella struttura dati.
bool Logger::findUser(const string &ID) {
    map<string,User*> usersMap = _graph.getNodes();
    return usersMap.find(ID) != usersMap.end();
}



bool Logger::updateFiles(const string &file_name_1, const string &file_name_2, const string &file_name_3) {

    //dichiarazione variabili file e stream da cui leggo ciò che mi serve mettere nelle variabili d'appoggio
    ofstream file_info, file_rel,file_news;
    //apertura file
    file_info.open("prova1.txt");
    file_rel.open("prova2.txt");
    file_news.open(file_name_3);
    file_info.clear();
    file_rel.clear();

    Simple_User *s_ptr;
    Company_User *c_ptr;
    Group_User *g_ptr;

    map<string, User*> user_map = _graph.getNodes();
    map<string,vector<string>> relationship_map;

    if (file_info.is_open()) {
        for (map<string, User *>::iterator it = user_map.begin(); it != user_map.end(); it++) {
            if (_isSimple(it->second)) {
                s_ptr = (Simple_User *) it->second;
                file_info << s_ptr->getID() << ",simple,{nome:" << s_ptr->getName() << ",cognome:" << s_ptr->getSurname()
                          << ",data:" << s_ptr->getDate().str() << ",indirizzo:" << s_ptr->getAddress().str() << ",genere:"
                          << s_ptr->getGender() << "}" << endl;
            }
            if (_isCompany(it->second)) {
                c_ptr = (Company_User *) it->second;
                file_info << c_ptr->getID() << ",company,{nome:" << c_ptr->getName() << ",data:" << c_ptr->getDate().str()
                          << ",sede_legale:" << c_ptr->getAddress().str() << ",prodotto:" << c_ptr->getProduct() << "}" << endl;
            }
            if (_isGroup(it->second)) {
                g_ptr = (Group_User *) it->second;
                file_info << g_ptr->getID() << ",group,{nome:" << g_ptr->getName() << ",data:" << g_ptr->getDate().str()
                          << ",indirizzo:" << g_ptr->getAddress().str() << ",attività:" << g_ptr->getActivity() << "}" << endl;
            }
        }
        file_info.close();
    }else return false;


    if(file_rel.is_open()){
        map<string, User *> usmap2 = _graph.getNodes();
        map<string,vector<string>> relmap;
        for (map<string, User *>::iterator uit = usmap2.begin(); uit != usmap2.end(); uit++){
            relmap = _graph.getEdges(uit->first);
            for(map<string,vector<string>>::iterator rit = relmap.begin(); rit != relmap.end(); rit++) {
                for(vector<string>::iterator vit = rit->second.begin(); vit != rit->second.end(); vit++) {
                    file_rel << uit->first << "," << rit->first << "," << *vit << endl;
                    if((*vit) == "coniuge" || (*vit) == "amico" || (*vit) == "conoscente" || (*vit) == "dipendente" || (*vit) == "membro") {
                        _graph.deleteEdge(uit->first, rit->first, *vit, *vit);
                    }
                    if((*vit) == "figlio"){
                        if(((Simple_User*)(usmap2.find(rit->first)->second))->getGender() == "M") {
                            _graph.deleteEdge(uit->first, rit->first, "padre", *vit);
                        }else{
                            _graph.deleteEdge(uit->first, rit->first, "madre", *vit);
                        }
                    }
                    if((*vit) == "madre"){
                        _graph.deleteEdge(uit->first, rit->first,"figlio",*vit);
                    }
                    if((*vit) == "padre"){
                        _graph.deleteEdge(uit->first, rit->first,"figlio",*vit);
                    }
                    if((*vit) == "fratello" || (*vit) == "sorella"){
                        if(((Simple_User*)(usmap2.find(rit->first)->second))->getGender() == "M") {
                            _graph.deleteEdge(uit->first, rit->first, "fratello", *vit);
                        }else{
                            _graph.deleteEdge(uit->first, rit->first, "sorella", *vit);
                        }
                    }
                }
            }
        }
        file_rel.close();
    }else return false;


    if(file_news.is_open()){
        for(list<News*>::iterator it = _newsList.begin(); it != _newsList.end(); it++){
            file_news << (*it)->getPublisherID() << ",[" << (*it)->getMessage() << "],"
                     << (*it)->getDate().str() << ',' << "likes:{";
            vector<string> likesID = (*it)->getLikesID();
            for(vector<string>::iterator lit = likesID.begin(); lit != likesID.end(); lit++ ){
                if(lit == likesID.end()-1) {
                    file_news << *lit;
                }else{
                    file_news << *lit << ',';
                }
            }
            file_news << "},dislikes:{";
            vector<string> dislikesID = (*it)->getDislikesID();
            for(vector<string>::iterator dit = dislikesID.begin(); dit != dislikesID.end(); dit++ ){
                if(dit == dislikesID.end()-1) {
                    file_news << *dit;
                }else{
                    file_news << *dit << ',';
                }
            }
            file_news << "}," << endl;
        }
    }else return false;


    return true;
}

