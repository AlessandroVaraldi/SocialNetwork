//
// Created by Utente on 28/05/2018.
//

#ifndef PROGETTO_LOGGER_H
#define PROGETTO_LOGGER_H

#include <vector>
#include <list>
#include <algorithm>
#include <fstream>

#include "Graph.hpp"
#include "Date.h"
#include "News.h"
#include "Simple_User.h"
#include "Company_User.h"
#include "Group_User.h"

using namespace std;

class Logger {

public:
    //COSTRUTTORE _edgesNumber DISTRUTTORE
    Logger(const string &file_name_1, const string &file_name_2, const string &file_name_3);
    ~Logger();
    bool updateFiles(const string &file_name_1, const string &file_name_2, const string &file_name_3);
    //METODI RICERCA
    vector<Simple_User*> loneWolves();
    vector<Company_User*> nicestCompany();
    vector<Company_User*> nicestCompanyPartners();
    void familyTree(string ID, const string &filename);
    //METODI PER SIMPLE_USER
    int simpleUsersNumber();
    float ageAverage();
    int bornAfterDate(Date date);
    int friendsNumberSimpleUser(const string &ID);
    int acquaintancesNumberSimpleUser(const string &ID);
    int relativesNumberSimpleUser(const string &ID);
    void mostFriends();
    void mostAcquaintances();
    //METODI PER COMPANY_USER
    int companyUsersNumber();
    int partnersNumberCompanyUser(const string &ID);
    int employeesNumberCompanyUser(const string &ID);
    void mostEmployees();
    //METODI PER GROUP_USER
    int groupUsersNumber();
    int membersNumberGroupUser(const string &ID);
    //METODI PER NEWS
    void mostLikes();
    void mostDislikes();
    //METODI PER RIMOZIONE/AGGIUNTA/MODIFICA
    void modifyGroupUser(const string &ID_to_modify, string fields_to_assign[]);
    void modifyCompanyUser(const string &ID_to_modify, string fields_to_assign[]);
    void modifySimpleUser(const string &ID_to_modify, string field_to_assign[]);

    void removeGroupUser(const string &ID_to_delete);
    void removeCompanyUser(const string &ID_to_delete);
    void removeSimpleUser(const string &ID_to_delete);

    void addGroupUser(const string &ID, const string & name, const string &date, string &address, const string &activity);
    void addCompanyUser(const string &ID, const string & name, const string &date, string &address, const string &product);
    void addSimpleUser(const string &ID, const string & name, const string & surname, const string &date, string &address, const string &gender);

    void addLikeToNews(const string &ID, const string &publisherID, const string &Date, const string &message);
    void addDislikeToNews(const string &ID, const string &publisherID, const string &Date, const string &message);
    void removeLikeToNews(const string &ID, const string &publisherID, const string &Date, const string &message);
    void removeDislikeToNews(const string &ID, const string &publisherID, const string &Date, const string &message);
    //METODO CHE TESTA LA PRESENZA DI UN UTENTE
    bool findUser(const string &ID);
    //METODI PER TESTA LA VALIDITA' CAMPI DI UN UTENTE
    bool isID(string &ID_to_check);
    bool isNameOrSurname(string &name_or_surname_to_check);
    bool isDate(string &date_to_check);
    bool isAddressFieldGood(const string &strfield);
    bool isAddress(string &address_to_check);
    //METODO CHE TORNA IL FLAG SUI FILE
    bool areFilesOpen(){
        return _areFilesOpen;
    }
    bool isUserFileCorrect(){
        return _isUserFileCorrect;
    }
    bool isRelFileCorrect(){
        return _isRelFileCorrect;
    }
    bool isNewsFileCorrect(){
        return _isNewsFileCorrect;
    }
    int errorLine(){
        return _errorLineNum;
    }

private:
    //METODO PER TESTARE LA VALIDITA' DI UNA RELAZIONE
    bool _isRelationshipGood(const string &ID1,const string &ID2,const string &relationship);
    //METODI COMPLESSIVI PER TESTARE LA GIUSTA FORMATTAZIONE DELLE LINEE
    bool _isLineUserRelationshipsFileGood(const string &rel_file_line);
    bool _isLineNewsFileGood(const string &news_file_line);
    //METODI PER TESTARE SE UN UTENTE APPARTIENE AD UNA DELLE CLASSI DERIVATE DA USER
    bool _isSimple(User* &user_to_check);
    bool _isCompany(User* &user_to_check);
    bool _isGroup(User* &user_to_check);
    //METODI PER TESTARE L'APPARTENENZA DI UN SIMPLE_USER AD UN GRUPPO O AZIENDA
    bool _isMember(Simple_User* i);
    bool _isEmployee(Simple_User* i);
    //METODI CHE TORNANO IL NUMERO DI REAZIONI _edgesNumber RELAZIONI DI UN SIMPLE_USER DI CUI RICEVONO L'ID
    int _reactionsNumber(Simple_User* i);
    int _relationshipsNumber(Simple_User* i);
    //METODI CHE SERVONO PER LA CLASSIFICA DI SIMPATIA DELLE AZIENDE
    float _getLikesDislikesRatio(Company_User* c_user);
    bool _ratioComp(Company_User* i,Company_User* j);
    bool _partnersRatioComp(Company_User* i, Company_User* j);
    //METODO PER LA RICERCA DEI LUPI SOLITARI
    bool _lonelinessComp (Simple_User* i,Simple_User* j);
    //METODO PER LA CREAZIONE DI ALBERO GENEALOGICO
    void displayTree(Simple_User *user, bool is_founder, ofstream &file);

    //VARIABILI PRIVATE
    Graph<User*,string,string> _graph;
    list<News*> _newsList;
    bool _areFilesOpen = true;
    bool _isUserFileCorrect = true;
    bool _isRelFileCorrect = true;
    bool _isNewsFileCorrect = true;
    int _errorLineNum = 0;

};



#endif //PROGETTO_LOGGER_H
