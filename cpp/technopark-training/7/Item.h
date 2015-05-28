#include <iostream>
using namespace std;

#ifndef CLASS_ITEM
#define CLASS_ITEM

class Item {
private:
    int _invNumber;
    bool _taken;
public:
    Item(int invNumber = 0, bool taken = false)
        : _invNumber(invNumber), _taken(taken) {}

    bool isAvailable() const { return !_taken; }
    int getInvNumber() const { return _invNumber; }
    void take() { _taken = true; }
    void giveBack() { _taken = false; }
    
    virtual void show() const = 0;

    virtual ~Item() {}
};

#endif