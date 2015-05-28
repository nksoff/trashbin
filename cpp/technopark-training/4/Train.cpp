#include <iostream>
#include "Train.h"
using namespace std;

char *Train::getDestination() const {
    return _destination;
}
int Train::getNumber() const {
    return _number;
}
short Train::getDepartureHour() const {
    return _departureHour;
}
short Train::getDepartureMinute() const {
    return _departureMinute;
}
int Train::getAllPlaces() const {
    return _kupePlaces + _placPlaces;
}
int Train::getKupePlaces() const {
    return _kupePlaces;
}
int Train::getPlacPlaces() const {
    return _placPlaces;
}

void Train::setDestination(char *val) {
    _destination = val;
}
void Train::setNumber(int val) {
    _number = val;
}
void Train::setDepartureHour(short val) {
    if(val < 0 || val > 23) return;
    _departureHour = val;
}
void Train::setDepartureMinute(short val) {
    if(val < 0 || val > 59) return;
    _departureMinute = val;
}
void Train::setKupePlaces(int val) {
    _kupePlaces = val;
}
void Train::setPlacPlaces(int val) {
    _placPlaces = val;
}

ostream& operator << (ostream &stream, Train &obj) {
    stream << endl << "---Train #" << fixed << obj._number << endl;
    stream << "Destination: " << obj._destination << endl;
    stream << "Departure at: " << obj._departureHour << ":" << obj._departureMinute << endl;
    stream << "Places: " << obj._kupePlaces << " (kupe) + " << obj._placPlaces << " (plac) = " << obj.getAllPlaces() << endl;
    cout << "---" << endl;
    return stream;
}

ostream& operator << (ostream &stream, Train *obj) {
    return stream << *obj;
}

void Train::show() {
    cout << *this;
}