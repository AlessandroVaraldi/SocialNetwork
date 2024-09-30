//
// Created by Utente on 28/05/2018.
//

#include "Date.h"

#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;

Date::Date() {
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    _year = 1900 + ltm->tm_year;
    _month = 1 + ltm->tm_mon;
    _day = ltm->tm_mday;
}

Date::Date(int d, int m, int y) {
    _year = y;
    _month = m;
    _day = d;
}

int Date::year() const {
    return _year;
}

int Date::month() const {
    return _month;
}

int Date::day() const {
    return _day;
}

bool Date::isValid() const {
    if(_year<1 || _month<1 || _month>12 || _day<1 || _day>31)
        return false;
    else if((_month == 2 || _month == 4 || _month == 6 || _month == 9 || _month == 11) && _day == 31)
        return false;
    else if(_month == 2 && _day == 30)
        return false;
    else if(_year%4!=0 && _month == 2 && _day == 29)
        return false;
    else if(_year>1582 && _year%100==0 && _month == 2 && _day == 29)
        return false;
    else if((_year == 1582 && _month == 10 && _day>5 && _day<15))
        return false;
    else
        return true;
}

int Date::yearsFrom(Date d) {
    if(d.isValid()) {
        time_t now = time(nullptr);
        tm *ltm = localtime(&now);
        return ltm->tm_year - d._year + 1900;
    }
    else{
        std::cerr << "Invalid date!" << std::endl;
        return -1;
    }
}

Date::Date(const Date &to_copy) {
    this->_year = to_copy._year;
    this->_month = to_copy._month;
    this->_day = to_copy._day;
}

std::string Date::str() const {
    std::ostringstream date;
    date << std::setw(2) << std::setfill('0') << _day << "/" << std::setw(2) << std::setfill('0') << _month << "/" << std::setw(4) << std::setfill('0') <<  _year;
    return date.str();
}

bool Date::operator<(const Date &to_be_compared) {
    if(this-> _year < to_be_compared.year())
        return true;
    else if(this-> _year == to_be_compared.year() && this->_month < to_be_compared.month())
        return true;
    else return this-> _year == to_be_compared.year() && this->_month == to_be_compared.month() && this->_day < to_be_compared.day();
}

Date::Date(const string &date_str) {
    string day, month, year;
    istringstream s(date_str);
    istringstream string;

    if (!date_str.empty()) {
        getline(s, day, '/');
        string.str(day);
        string >> _day;

        getline(s, month, '/');
        string.clear();
        string.str(month);
        string >> _month;

        getline(s, year);
        string.clear();
        string.str(year);
        string >> _year;
    }else{
        _day = '\0';
        _month = '\0';
        _year = '\0';
    }


}

bool Date::operator==(const Date &to_be_compared) {
    return (_day == to_be_compared._day && _month == to_be_compared._month && _year == to_be_compared._year);
}
