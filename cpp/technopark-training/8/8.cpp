#include <iostream>
#include "Queue.h"
using namespace std;

int main() {
    cout << (23%17+1) << " variant" << endl;

    const int QUEUES_LENGTH = 10;

    cout << "--- int ---" << endl;
    Queue<int> qInts[2], &qInt = qInts[0], &qInt1 = qInts[1];
    for(int i = 0; i < QUEUES_LENGTH; i++) {
        qInt.push(i+1);
        qInt1.push(i-1);
    }
    cout << "=int array 1=" << endl << qInt
    << "=int array 2=" << endl << qInt1;

    Queue<int> qIntSum = qInt + qInt1, qIntDiff = qInt - qInt1;
    cout << "=int array 1 + 2=" << endl << qIntSum
    << "=int array 1 - 2=" << endl << qIntDiff;

    cout << "--- /int ---" << endl << endl << endl;

    cout << "--- double ---" << endl;
    Queue<double> q2;
    for(int i = 0; i < QUEUES_LENGTH; i++) {
        q2.push(i+1+(0.01*(i+1)));
    }
    cout << q2;
    removeByTwo(q2);
    cout << "=removed odd elements=" << endl << q2;
    cout << "--- /double ---" << endl << endl << endl;

    cout << "--- char ---" << endl;
    Queue<char> q3;
    for(int i = 0; i < QUEUES_LENGTH; i++) {
        char* nchar = new char((i+97)%256);
        q3.push(*nchar);
        delete nchar;
    }
    cout << q3;
    removeByTwo(q3, false);
    cout << "=removed even elements=" << endl << q3;
    cout << "--- /char ---" << endl << endl << endl;

    return 0;
}
