#include <iostream>
#include "Queue.h"
using namespace std;

void removeByTwo(Queue &obj, bool odd = true) { // odd - нечет,
    int from = (odd) ? 0 : 1, to = obj.getCount(), removed = 0;
    for(int i = from; i < to; i+=2) {
        obj.pop(i - (removed++));
    }
}

int main() {
	cout << (23%17+1) << " variant" << endl;

    const int QUEUES_COUNT = 2;
    const int QUEUES_LENGTH = 15;

	Queue queues[QUEUES_COUNT];
    for(int i = 0; i < QUEUES_COUNT; i++) {
        for(int j = 0; j < QUEUES_LENGTH; j++) {
            queues[i].push((j+1)*(i+1));
        }
        cout << "---" << endl;
        queues[i].show();

        bool odd = i%2 != 0;
        removeByTwo(queues[i], odd);

        cout
            << "removed "
            << (odd ? "odd" : "even")
            << " elements of queue" << endl;

        queues[i].show();
    }

	return 0;
}
