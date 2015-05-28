#include <iostream>
#include <string>
#include "Item.h"
using namespace std;

#ifndef CLASS_BOOK
#define CLASS_BOOK

class Book : public Item {
private:
    string _author, _title, _publisher;
    int _year;
public:
    Book(int invNumber = 0, bool taken = false, string title = "",
        string author = "", string publisher = "", int year = 2015)
    : Item(invNumber, taken), _author(author),
    _title(title), _publisher(publisher), _year(year) {
    }

    string getAuthor() const { return _author; }
    string getTitle() const { return _title; }
    string getPublisher() const { return _publisher; }
    int getYear() const { return _year; }

    void show() const {
        cout << (isAvailable() ? "+++" : "---");
        cout << "Book #" << getInvNumber() << " "
        << endl
        << "      " << _title << " by " << _author
        << endl
        << "      Published by " << _publisher << " in " << _year
        << endl;
    }

};

#endif