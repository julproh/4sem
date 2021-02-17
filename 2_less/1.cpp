/*
1 - untracked
2 - unmodifed
3 - modified
4 - staged (add)

done - клонирование репозитория
add - добавить файл к commity
remove - убрать файл из commity
pull - стянуть commity  из irigin и применить
commit - утвердить изменения в репозитории
fetch - -//- без приминения
push - закинуть commit  с локального в origin
branch - работа с ветками
checkout - переключение между вектами
merge - c   и   н   я
rebase -  л   я   и 
hist / log
status
tag - добавляет меточку
*/

/* Standart Template library

Программа = структуры данных + алгоритмы
                        Класс, объекты
1 - Контейнеры ("Умные структуры данных")
2 - Агоритмы (sort, find, ..)
    Работа с контейнерами требует итераторы - объекты, указатели на элемент объекта
3 - Итераторы

vector <int> v(10);
vector <int> :: iterator it;
it = v.begin(); // итератор на начало вектора
it++ // -> v[1]
it+3 // -> v[4]
auto it_1 = v.begin();
std::begin(v);
it = v.end(); // элемент следующий за последним
for (auto it = v.begin(); it!=v.end();++t) {};

for (auto i: v) {}; - присвоение
for (auto &i : v) {}; - ссылаемся на элемент
for (const auto &i : v) {};

pair <X, Y>;

*/

#include <iostream>
#include <map>
#include <utility>
#include <functional>

using namespace std;

int main() {
    
    pair <int, double> p(23, 84.54);
    cout << "first = " << p.first << endl;
    cout << "second = " << p.second << endl;

    int i = 0;
    auto p1 = make_pair(ref(i), ref(i));
    p1.first++;
    p1.second++;
    cout << "first = " << p1.first << endl;
    cout << "second = " << p1.second << endl;

    //tuple<N1, N2, N3, ... > - кортеж
    //get, make_tuple, tie
    //tule_size<тип кортежа> :: value - количество
    //tuple_element<индекс, тип кортежа> :: type
    //tuple_cat() - объединяет два кортежа


    return 0;
}