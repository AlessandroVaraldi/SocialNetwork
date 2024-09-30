//
// Created by Utente on 28/05/2018.
//

#ifndef PROGETTO_LOGGER_H
#define PROGETTO_LOGGER_H

#include <vector>
#include <list>
#include <algorithm>

#include "Graph.hpp"
#include "Date.h"
#include "News.h"
#include "Simple_User.h"
#include "Company_User.h"
#include "Group_User.h"

using namespace std;

class Logger {

public:
    Logger(const string &file_name_1, const string &file_name_2, const string &file_name_3);
    ~Logger();

    bool areFilesOpen();

    void familyTree(string id_utente);

    int simpleUsersNumber();
    int companyUsersNumber();
    int groupUsersNumber();
    int bornAfterDate(Date date);
    float ageAverage();

    int friendsNumberSimpleUser(const string &ID);
    int acquaintancesNumberSimpleUser(const string &ID);
    int relativesNumberSimpleUser(const string &ID);
    int partnersNumberCompanyUser(const string &ID);
    int employeesNumberCompanyUser(const string &ID);
    int membersNumberGroupUser(const string &ID);

    Company_User* mostEmployees();
    Company_User* mostEmployeesPartners();
    News* mostLikes();
    News* mostDislikes();
    Simple_User* mostFriends();
    Simple_User* mostAcquaintances();

    void modifyGroupUser(const string &ID_to_modify, const string& name, const Date& date, const Address& address,
                         const string &activity);
    void modifyCompanyUser(const string &ID_to_modify, const string& name, const Date& date, const Address& address,
                                   const string &product);
    void modifySimpleUser(const string &ID_to_modify, const string& name,
                                  const string& surname, const Date& date, const Address& address,
                                  const char& gender);

    void removeGroupUser(const string &ID_to_delete);
    void removeCompanyUser(const string &ID_to_delete);
    void removeSimpleUser(string &ID_to_delete);

    void addGroupUser(Group_User &g_u);
    void addCompanyUser(Company_User &c_u);
    void addSimpleUser(Simple_User &s_u);

    void addLikeToNews(const string &ID, const string &publisherID, const string &Date);
    void addDisikeToNews(const string &ID, const string &publisherID, const string &Date);
    void removeLikeToNews(const string &ID, const string &publisherID, const string &Date);
    void addDislikeToNews(const string &ID, const string &publisherID, const string &Date);

    void addNews(Company_User* pointer, string message);

    vector<Simple_User*> loneWolves();
    vector<Company_User*> nicestCompany();
    vector<Company_User*> nicestCompanyPartners();

private:

    bool _isID(string &ID_to_check);
    bool _isNameOrSurname(string &name_or_surname_to_check);
    bool _isDate(string &date_to_check);
    bool _isAddress(string &address_to_check);
    bool _isLineUserFileGood(const string &user_file_line);
    bool _isRelationshipGood(const string &ID1,const string &ID2,const string &relationship)
    bool _isLineUserRelationshipsFileGood(const string &rel_file_line);
    bool _isLineNewsFileGood(const string &news_file_line);
    bool _isSimple(User* &user_to_check);
    bool _isCompany(User* &user_to_check);
    bool _isGroup(User* &user_to_check);
    bool _isMember(Simple_User* i);
    bool _isEmployee(Simple_User* i);
    int _reactionsNumber(Simple_User* i);
    int _relationshipsNumber(Simple_User* i);
    bool _ratioComp(Company_User* i,Company_User* j);
    bool _partnersRatioComp(Company_User* i, Company_User* j);
    float _getLikesDislikesRatio(Company_User* c_user);
    bool _lonelinessComp (Simple_User* i,Simple_User* j);
    void DisplayTreeR(Simple_User* user, bool risali);

    Graph<User*,string,string> _graph;
    list<News*> _newsList;
    bool _areFilesOpen;
};



#endif //PROGETTO_LOGGER_H
