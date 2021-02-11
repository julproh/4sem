//BOOST
//SFML
//QT

//Разработка программного обеспечения
//
// 1 - Выработка требований - Диздок
// 2 - Планирование ресурсов
// 3 - Разработка архитектуры(схемы, модули)
// 4 - Детальное проектирование
/* 5 - Кодирование и отладка
   6 - Блочные тестирования (юнит тестирование)
   7 - Итеграционное тестирование  // тесты бывают ручные и автоматические
   8 - В - тестирование
   9 - Релиз
   10 - Внедрение
   11 - Поддержка

________________________________
где хранить код?
репозиторий локальный/удаленный

существуют системы контроля версий
1 - резервное копирование "Коммит"
2 - администрирование
3 - разделение
Коммит /net/gui/logic

GIT
SVN

1 Console 
gitinit
.GITATTRIBUTES
.GITIGNORE
.


git checkout <commit_num>
git merge
  
*/
#include <iostream>
#include <ratio>
#include <chrono>
#include <vector>
#include <algorithm>
/*
*/
using namespace std;
using namespace chrono;

void sort(vector<int>& v) {
    for (size_t i =0; i < v.size() -1; i++) {
            for(size_t j = i+ 1; j < v.size(); ++j) {
                if (v[i] > v[j]) {
                    swap(v[i], v[j]);
                }
            }
    }
}
int main() {

    // auto now =  chrono::system_clock::now();
    // for (auto i = 0; i < 10000000; ++i);
    // auto end = chrono::system_clock::now();

    // auto elapsed = chrono::duration_cast<chrono::milliseconds> (end - now);
    //cout << "Tschuuus" << endl;

    const auto size = 10000;
    vector< int> v_1(size, 0);

    chrono::duration<chrono::seconds> dur{5min};
    chrono::duration<chrono::seconds> operator "" _min(int);
    for (size_t i = 0; i <v_1.size(); ++i) {
        v_1[i] = v_1.size() - i;
    }

    auto v_2 = v_1;
    sort(v_1);
    sort(v_2.begin(), v_2.end());

    return 0;
}