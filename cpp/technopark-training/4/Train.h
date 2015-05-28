#include <iostream>
#include <string.h>
using namespace std;

#ifndef CLASS_TRAIN
#define CLASS_TRAIN

class Train {
private:
    int _number;
    char *_destination;
    short _departureHour, _departureMinute;
    int _kupePlaces, _placPlaces;
public:
    char *getDestination() const;
    int getNumber() const;
    short getDepartureHour() const;
    short getDepartureMinute() const;
    int getAllPlaces() const;
    int getKupePlaces() const;
    int getPlacPlaces() const;

    void setDestination(char*);
    void setNumber(int);
    void setDepartureHour(short);
    void setDepartureMinute(short);
    void setKupePlaces(int);
    void setPlacPlaces(int);

    void show();

    friend ostream& operator << (ostream&, Train&);
    friend ostream& operator << (ostream&, Train*);

    Train(int number,
        char *destination,
        short departureHour,
        short departureMinute,
        int kupePlaces,
        int placPlaces) :
        _number(number),
        _departureHour(departureHour),
        _departureMinute(departureMinute),
        _kupePlaces(kupePlaces),
        _placPlaces(placPlaces)
    {
        _destination = new char[strlen(destination)];
        strcpy(_destination, destination);
    }

    Train(const Train &copy)
    {
        if(this != &copy) {
            Train(copy._number,
                copy._destination,
                copy._departureHour,
                copy._departureMinute,
                copy._kupePlaces,
                copy._placPlaces);
        }
    }

    ~Train() {
        delete _destination;
    }
};

#endif
