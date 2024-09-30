//
// Created by Utente on 28/05/2018.
//

#ifndef PROGETTO_NEWS_H
#define PROGETTO_NEWS_H

#include <iostream>
#include <vector>
#include "User.h"

using namespace std;

class News {

public:
    //COSTRUTTORI
    News(){};
    News(const Date &date, const string &message, const string &publisherID, vector<string> likes_vett, vector <string> dislikes_vett);
    //METODI GETTERS
    int getLikesNumber();
    int getDislikesNumber();
    vector<string> getLikesID();
    vector<string> getDislikesID();
    string getMessage();
    Date getDate();
    string getPublisherID();
    //METODI SETTERS
    void setMessage(const string &message);
    void setDate(const Date &date);
    void setPublisherID(const string &publisherID);
    //METODI SETTERS _edgesNumber REMOVER PER I LIKES _edgesNumber DISLIKES
    void setNewLike(const string &new_like_ID);
    void setNewDislike(const string &new_dislike_ID);
    void removeLike(const string &remove_ID);
    void removeDislike(const string &remove_ID);

private:
    //VARIABILI PRIVATE
    string _message;
    Date _date;
    string _publisherID;
    vector<string> _likes;
    vector<string> _dislikes;
};


#endif //PROGETTO_NEWS_H
