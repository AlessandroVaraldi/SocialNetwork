//
// Created by Utente on 28/05/2018.
//

#include "News.h"
#include "Date.h"
#include "Graph.hpp"

#include <map>

//---------------COSTRUTTORE---------------
News::News(const Date &date, const string &message, const string &publisherID, vector<string> likes_vett, vector <string> dislikes_vett){
    _message = message;
    _date = date;
    _publisherID = publisherID;
    _likes = likes_vett;
    _dislikes = dislikes_vett;
}

//--------------GETTERS----------------
int News::getLikesNumber() {
    return _likes.size();
}

int News::getDislikesNumber() {
    return _dislikes.size();
}

vector<string> News::getLikesID() {
    return _likes;
}

vector<string> News::getDislikesID() {
    return _dislikes;
}

string News::getMessage() {
    return _message;
}

Date News::getDate() {
    return _date;
}

string News::getPublisherID() {
    return _publisherID;
}
 //-------------SETTERS---------------
void News::setMessage(const string &message) {
    _message = message;
}

void News::setDate(const Date &date) {
    _date = date;
}

void News::setPublisherID(const string &publisherID) {
    _publisherID = publisherID;
}

//--------------SETTERS/REMOVER--------------
void News::setNewLike(const string &new_like_ID) {
    _likes.push_back(new_like_ID);
}

void News::setNewDislike(const string &new_dislike_ID) {
    _dislikes.push_back(new_dislike_ID);
}
void News::removeLike(const string &remove_ID) {
    _likes.erase(find(_likes.begin(),_likes.end(),remove_ID));
}

void News::removeDislike(const string &remove_ID) {
    _dislikes.erase(find(_dislikes.begin(),_dislikes.end(),remove_ID));
}


