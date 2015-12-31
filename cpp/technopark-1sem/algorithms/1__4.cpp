/**
Во всех задачах из следующего списка следует написать структуру данных, обрабатывающую команды push* и pop*.
Формат входных данных.  
В первой строке количество команд n. n ≤ 100000.  
Каждая команда задаётся как 2 целых числа: a b.  
a = 1 ­ push front 
a = 2 ­ pop front 
a = 3 ­ push back 
a = 4 ­ pop back
Для очереди используются команды 2 и 3. Для дека используются все четыре команды.  
Если дана команда pop*, то число b ­ ожидаемое значение. Если команда pop вызвана для пустой структуры данных, то ожидается “­1”.
Формат выходных данных.  
Требуется напечатать YES ­ если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.
Реализовать очередь с динамическим зацикленным буфером.
*/

#include <iostream>
using namespace std;

class Queue {
protected:
    int *data; // массив с числами
    int dataSize; // количество элементов, на которые выделена память

    int head; // номер первого элемента
    int tail; // номер последнего элемента

    // увеличивает кол-во памяти
    void growSize() {
        int newDataSize = (dataSize > 0) ? dataSize * 2 : 10, // размер новой памяти
            *newData = new int[newDataSize]; // новая память

        if(head != tail) {
            int j = 0; // временный индекс
            for(int i = head; i < dataSize; i++) {
                if(i == tail) { // элемент следующий после последнего
                    break;
                }

                newData[j++] = data[i];

                if(i == dataSize - 1) {
                    i = -1;
                }
            }
            head = 0;
            tail = j;
        }

        if(data != NULL) {
            delete[] data;
        }

        data = newData;
        dataSize = newDataSize;
    }

public:
    Queue() {
        data = NULL;
        dataSize = 0;

        head = 0;
        tail = 0;

        growSize();
    }

    ~Queue() {
        if(data != NULL) {
            delete[] data;
        }
    }

    // удаляет первый элемент и возвращает его
    int pop() {
        if(head != tail) {
            // очередь не пуста
            int val = data[head];

            if(head == dataSize - 1) {
                head = 0;
            }
            else
            {
                head++;
            }

            return val;
        }

        // очередь пуста
        return -1;
    }

    // добавляет новый элемент в конец
    void push(int val) {
        if((tail + 1) % dataSize == head) {
            // память закончилась
            growSize();
            push(val);
        }
        else
        {
            // добавляем следующий элемент
            data[(tail) % dataSize] = val;
            tail = (tail + 1) % dataSize;
        }
    }

    // выводит массив
    /*void show() {
        printf("[%d:%d:%d]==========\n", head, tail, dataSize);
        for(int i = head; i < dataSize; i++) {
            if(i == tail) { // элемент следующий после последнего
                break;
            }

            printf("[%d] => %d\n", i, data[i]);

            if(i == dataSize - 1) {
                i = -1;
            }
        }
        printf("/==========\n");
    }*/

    // очередь пуста?
    bool isEmpty() {
        return head == tail;
    }

};

int main() {
    Queue queue;

    int commandsNumber = 0;
    cin >> commandsNumber;

    int commandNumber = 0,
        commandValue = 0;

    bool isOK = true;

    for(int i = 0; i < commandsNumber; i++) {
        cin >> commandNumber >> commandValue;
        if(!isOK) {
            continue;
        }
        switch(commandNumber) {
            case 2:
                if(queue.isEmpty()) {
                    commandValue = -1;
                }
                isOK = (queue.pop() == commandValue) && isOK;
                break;
            case 3:
                queue.push(commandValue);
                break;
        }
    }

    cout << (isOK ? "YES" : "NO");

    return 0;
}
