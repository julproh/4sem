#include <iostream>
#include <vector>

using namespace std;

void print_size_and_capacity(const vector<int>& v){
    cout << "size = " << v.size() << endl;
    cout << "capacity = " << v.capacity() << endl;
}
int main () {

    vector<int> v1;
    vector<int> v2(4);
    vector<int> v3(128);

    print_size_and_capacity(v1);
    print_size_and_capacity(v2);
    print_size_and_capacity(v3);

    v3.resize(100);
    print_size_and_capacity(v3);

    v3.resize(200);
    print_size_and_capacity(v3);

//
    vector<bool> v; // реализован особенно

    return 0;
}

//push_back - помещаем элемент в конец
//emplace_back - можно без конструктора
//size 
//begin / end
// operator[]
//at - может кинуть исключение
//capacity - емкость
//  size  может быть меньше capacity
// remove - 
// erase - удаляет 
//resize - изменяет размер

/*
array
deque - двусторонняя очередь
    push_back
    push_forvard
    emplace_back
list - двусвязный список
forvard_list - односвязный список
stack - работаем с последним элементом
    top
    pop
    push
queue выгружаем начало, загружаем в конец
    back 
    front
    pop
    push
priority_queque - очередь с приоритетом
bitset - битовая карта

*/
