// Стандартные алгоритмы
/*
Генерация случайных чисел
"псевдослучайные числа"

Вихрь Месенна


*/

#include <iostream>
using namespace std;

unsigned int PRNG() {
    static unsigned int seed =1;
    seed = (82537298*seed + 2396403);
    return seed% 32769;
}

int main() 
{
    for (int count = 0; count < 1000; ++count) {
        cout << PRNG() << endl;

    if ((count+1) % 5 == 0)
        cout << endl;
    }

    return 0;
}