//
// Created by Utente on 28/05/2018.
//

#ifndef PROGETTO_DATE_H
#define PROGETTO_DATE_H

#include <iostream>

using namespace std;

class Date {
public:
    Date();
    Date(int d, int m, int y);
    Date(const string &date_str);
    Date(const Date & to_copy);

    int year() const;
    int month() const;
    int day() const;

    int yearsFrom(Date d = Date());
    bool operator < (const Date &to_be_compared);
    bool operator == (const Date &to_be_compared);

    string str() const;
    bool isValid() const;

private:


    int _year;
    int _month;
    int _day;
};


#endif //PROGETTO_DATE_H
