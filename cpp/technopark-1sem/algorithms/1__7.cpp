/**
Атлеты.
В город N приехал цирк с командой атлетов. Они хотят удивить горожан города N — выстроить из своих тел
башню максимальной высоты. Башня — это цепочка атлетов, первый стоит на земле, второй стоин у него
на плечах, третий стоит на плечах у второго и т.д.
Каждый атлет характеризуется силой si атлет способен держать у себя на плечах.
К сожалению ни один из атлетов не умеет программировать, так как всю жизнь они занимались физической
подготовкой, и у них не было времени на изучение языков программирования. Помогите им, напишите
программу, которая определит максимальную высоту башни, которую они могут составить.
Известно, что если атлет тяжелее, то он и сильнее
Атлеты равной массы могут иметь различную силу.
Формат входных данных:
Вход содержит только пары целых чисел — массу и силу атлетов. Число атлетов 1 ≤ n ≤ 100000. Масса и
сила являются положительными целыми числами меньше, чем 2000000.
Формат выходных данных:
Выход должен содержать натуральное число — максимальную высоту башни.
(kg) и массой mi (kg).
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {

    vector<long>    mass,
                    power;

    long m = 0,
         p = 0;
    while(scanf("%ld %ld", &m, &p) == 2) {
        mass.push_back(m);
        power.push_back(p);
    }

    sort(mass.begin(), mass.end());
    sort(power.begin(), power.end());

    long curMass = mass[0],
         curHeight = 1;
    // cout << "[" << mass[0] << ", " << power[0] << "]" << endl;

    for(size_t i = 1; i < mass.size(); i++) {

        if(power[i] >= curMass) {
            curMass += mass[i];
            curHeight++;
            // cout << "[" << mass[i] << ", " << power[i] << "]" << endl;
        }
    }

    cout << curHeight;

    return 0;
}
