/**
Хеширование кукушки
*/

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

class HashTableNode {
private:
    static const std::string EMPTY;
    std::string _key;
public:
    HashTableNode(const std::string &key = HashTableNode::EMPTY): _key(key) {}

    // возвращает ключ
    const std::string &getKey() const {
        return _key;
    }

    // сохраняет ключ
    void setKey(const std::string &key) {
        _key = key;
    }

    // пустая ячейка?
    bool isEmpty() const {
        return _key == HashTableNode::EMPTY;
    }

    // помечаем ячейку как пустую
    void setEmpty() {
        _key = HashTableNode::EMPTY;
    }

    // сравнение =
    bool is(const std::string &key) {
        return _key == key;
    }
};

const std::string HashTableNode::EMPTY = "";

class HashTable {
private:
    std::vector<HashTableNode> buffer;

    int bufferSize; // размер буфера (2^n)
    int bufferExp; // n - степень двойки для размера буфера
    int size; // реальное кол-во элементов

    // перехеширование
    void rehash() {
        std::vector<std::string> strings;

        for(size_t i = 0; i < bufferSize; i++) {
            if(!buffer[i].isEmpty()) {
                strings.push_back(buffer.at(i).getKey());
                buffer.at(i).setEmpty();
            }
        }

        bufferExp++;
        bufferSize = (2 << bufferExp);
        buffer.resize(bufferSize);

        for(size_t i = 0; i < strings.size(); i++) {
            add(strings.at(i));
        }
    }

public:
    HashTable(): bufferExp(3), size(0) {
        bufferSize = (2 << bufferExp);
        buffer.resize(bufferSize);
    }

    // добавление
    bool add(const std::string &key) {
        int h1 = hash1(key),
            h2 = hash2(key);

        if(buffer.at(h1).is(key) || buffer.at(h2).is(key)) {
            return false;
        }

        std::string cur = key,
                    tmp;
        for(size_t i = 0; i < bufferSize; i++) {
            h1 = hash1(cur);
            h2 = hash2(cur);

            if(buffer.at(h1).isEmpty()) {
                buffer.at(h1).setKey(cur);
                return true;
            }

            if(buffer.at(h2).isEmpty()) {
                buffer.at(h2).setKey(cur);
                return true;
            }

            tmp = buffer.at(h1).getKey();
            buffer.at(h1).setKey(cur);
            cur = tmp;
        }

        rehash();
        return add(cur);
    }

    // удаление
    bool remove(const std::string &key) {
        int h1 = hash1(key),
            h2 = hash2(key);

        if(buffer.at(h1).is(key)) {
            buffer.at(h1).setEmpty();
            size--;
            return true;
        }

        if(buffer.at(h2).is(key)) {
            buffer.at(h2).setEmpty();
            size--;
            return true;
        }

        return false;
    }

    // содержит?
    bool has(const std::string &key) {
        int h1 = hash1(key),
            h2 = hash2(key);

        return buffer.at(h1).is(key) || buffer.at(h2).is(key);
    }

    // hash1 = Ly [@see http://habrahabr.ru/post/219139/]
    int hash1(const std::string &key) {
        unsigned int hash = 0;
        for(size_t i = 0; i < key.size(); i++) {
            hash = (hash * 1664525) + (unsigned char)(key[i]) + 1013904223;
        }
        return abs((int) hash) % bufferSize;
    }

    // hash2 = Rs [@see http://habrahabr.ru/post/219139/]
    int hash2(const std::string &key) {
        static const unsigned int b = 378551;
        unsigned int a = 63689;
        unsigned int hash = 0;

        for(size_t i = 0; i < key.size(); i++) {
            hash = hash * a + (unsigned char)(key[i]);
            a *= b;
        }

        return abs((int) hash) % bufferSize;
    }
};

int main() {
    HashTable map;

    char command = '\0';
    std::string key("");

    bool tmpRes = false;
    while(std::cin >> command >> key) {
        switch(command) {
            case '+':
                tmpRes = map.add(key);
                break;
            case '?':
                tmpRes = map.has(key);
                break;
            case '-':
                tmpRes = map.remove(key);
                break;
            default:
                continue;
        }

        std::cout << (tmpRes ? "OK" : "FAIL") << std::endl;
    }
    return 0;
}
