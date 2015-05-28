#include <iostream>
#include "Train.h"
using namespace std;

struct Node {
    Train *train;
    Node *next;
};
typedef Node* TrainsList;

int main() {
    cout << (23%17+1) << " variant" << endl;

    FILE *inFile = fopen("trains.txt", "r");

    if(!inFile) {
        cout << "[ERROR] Couldn't open database file" << endl;
        return -2;
    }

    TrainsList head = NULL, tail = NULL;

    double number;
    char destination[100];
    short departureHour, departureMinute;
    int kupePlaces, placPlaces;

    while(fscanf(inFile, "%lf %s %hd:%hd %d %d",
        &number, destination, &departureHour,
        &departureMinute, &kupePlaces, &placPlaces) == 6) {
        Train* currentTrain = new Train(
            number, destination, departureHour,
            departureMinute, kupePlaces, placPlaces);
        Node* node = new Node;
        node->train = currentTrain;
        if(head == NULL) {
            head = node;
        }
        if(tail != NULL) {
            tail->next = node;
        }
        tail = node;
    }

    fclose(inFile);

    while(true) {
        cout << "Select mode:" << endl;
        cout << "1. all trains" << endl;
        cout << "2. trains to Moscow" << endl;
        cout << "3. trains to Kiev before 07:00" << endl;
        cout << "4. trains to Moscow with kupe places" << endl;
        cout << "0. exit" << endl;
        cout << ">> ";
        int mode;
        cin >> mode;

        if(mode == 0) {
            break;
        }

        cout << endl << "------------------------------------------------------------";
        tail = head;
        int found = 0;
        while(tail != NULL) {
            switch(mode) {
            case 1:
                cout << tail->train;
                found++;
            break;
            case 2:
                if(strcmp(tail->train->getDestination(), "Moscow") == 0) {
                    cout << tail->train;
                    found++;
                }
            break;
            case 3:
                if(strcmp(tail->train->getDestination(), "Kiev") == 0 &&
                    tail->train->getDepartureHour() < 7) {
                    cout << tail->train;
                    found++;
                }
            break;
            case 4:
                if(strcmp(tail->train->getDestination(), "Moscow") == 0 &&
                    tail->train->getKupePlaces() > 0) {
                    cout << tail->train;
                    found++;
                }
            break;
            }

            tail = tail->next;
        }
        cout << endl << "found: " << found << " trains";
        cout << endl << "------------------------------------------------------------" << endl;
    }
    return 0;
}