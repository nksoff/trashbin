#include <iostream>
#include "Item.h"
#include <string>
using namespace std;

#ifndef CLASS_MAGAZINE
#define CLASS_MAGAZINE

class Magazine : public Item {
private:
    string _title;
    int _number, _volume, _year;
    // number 1, volume 13  = 1(13)
public:
    Magazine(int invNumber = 0, bool taken = false, string title = "",
        int number = 1, int volume = 1, int year = 2015)
        : Item(invNumber, taken), _title(title), _number(number), _volume(volume),
        _year(year) {}

    string getTitle() const { return _title; }
    int getVolume() const { return _volume; }
    int getNumber() const { return _number; }
    int getYear() const { return _year; }

    void show() const {
        cout << (isAvailable() ? "+++" : "---");
        cout << "Magazine #" << getInvNumber() << " "
        << endl
        << "      " << _title << " "
        << " #" << _number << "(" << _volume << ")"
        << endl
        << "      Published in " << _year
        << endl;
    }
};

#endif