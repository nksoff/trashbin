#include "Replace.h"

#include <iostream>

#include <vector>
#include <deque>
#include <list>
#include <map>

#include <set>

using namespace std;

int main() {
    vector<double> contVector;
    deque<double> contDeque;
    list<double> contList;

    map<int, double> contMap;
    multimap<int, double> contMultimap;

    set<double> contSet;
    multiset<double> contMultiset;

    for(int i = 0; i < 15; i++) {
        double n = (rand() % 17) + (0.1 * (rand() % 10));
        contVector.push_back(n);
        contDeque.push_front(n);
        contList.push_front(n);
        contMap[i] = n;
        contMultimap.insert( pair<int, double>(i,n) );
        contMultimap.insert( pair<int, double>(i,n) );

        contSet.insert(n);
        contMultiset.insert(n);
        contMultiset.insert(n);
    }

    LessThan<double> lessThan10 = 10, lessThan6 = 6;
    MoreThan<double> moreThan5 = 5, moreThan7 = 7;

    int replaced;

    // vector
    show(contVector.begin(), contVector.end(), "vector");
    replaced = f<double>(contVector.begin(), contVector.end(), lessThan10);
    cout << "---> replaced (less than 10) with 0 (by default) in vector: " << replaced << endl;
    show(contVector.begin(), contVector.end(), "vector");

    //deque
    show(contDeque.begin(), contDeque.end(), "deque");
    replaced = f<double>(contDeque.begin(), contDeque.end(), lessThan6, 0.8);
    cout << "---> replaced (less than 6) with 0.8 in deque: " << replaced << endl;
    show(contDeque.begin(), contDeque.end(), "deque");

    // list
    show(contList.begin(), contList.end(), "list");
    replaced = f<double>(contList.begin(), contList.end(), moreThan5, 8.88);
    cout << "---> replaced (more than 5) with 8.88 in list: " << replaced << endl;
    show(contList.begin(), contList.end(), "list");

    // map
    show(contMap.begin(), contMap.end(), "map");
    replaced = f<double>(contMap.begin(), contMap.end(), moreThan7);
    cout << "---> replaced (more than 7) with 0 (by default) in map: " << replaced << endl;
    show(contMap.begin(), contMap.end(), "map");

    // multimap
    show(contMultimap.begin(), contMultimap.end(), "multimap");
    replaced = f<double>(contMultimap.begin(), contMultimap.end(), lessThan10, 55555);
    cout << "---> replaced (less than 10) with 55555 in multimap: " << replaced << endl;
    show(contMultimap.begin(), contMultimap.end(), "multimap");

    // set
    show(contSet.begin(), contSet.end(), "set");
    // replaced = f<double>(contSet.begin(), contSet.end(), lessThan10, 55555);
    cout << "<--- const only!" << endl;
    
    // multiset
    show(contMultiset.begin(), contMultiset.end(), "multiset");
    cout << "<--- const only!" << endl;

    return 0;
}