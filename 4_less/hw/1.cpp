#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

vector <int> creation();
vector <int> increase (vector <int>);
vector <int> without_dobles(vector <int>);
int nechet( vector <int>);
int min_v( vector <int> );
int max_v( vector <int> );
void easy_number (vector <int>);
vector <int> second_degree (vector <int>);
vector <int> creation_2( vector <int>);
int sum_2 (vector <int> & );
vector <int> change (vector <int> & );
vector <int> creation_3( vector <int>, vector <int>);
vector <int> nul (vector <int>& );
vector <int> del_nul (vector <int> &);
void three_big (vector <int> &);
vector <int> creation_4 (vector <int> &, vector <int> &);
void diapazon (vector <int> &) ;
void vivod (vector <int> &, vector <int> &, vector <int> &, vector <int> & );
int main() {

    try {
    vector <int> V = creation(); // создаю последовательность
    V = increase(V); // увеличиваю размер
    for (auto i : V) {
         cout << i << " " ;
    } 
    cout << endl;
    random_shuffle(V.begin(), V.end()); //перемешиваю
    for (auto i : V) {
         cout << i << " " ;
    } 
    cout << endl;
    V = without_dobles(V);
    cout << "В последовательности " << nechet(V) << "нечетных чисел" << endl;
    cout << "Максимум последовательности " << max_v(V) << ", минимум последовательности:" << min_v(V) << endl;
    easy_number(V);
    V = second_degree(V);
    vector <int> V_2 = creation_2(V); 
    cout << "Сумма членов второй последовательности: "<< sum_2(V_2) << endl;
    V_2 = change(V_2);
    vector <int> V_3 = creation_3(V, V_2);
    V_3 = nul(V_3);
    V_3 = del_nul(V_3);
    reverse(V_3.begin(), V_3.end());
    cout << "Полученная 3 последовательность: " << " ";
    for (auto i : V_3) {
         cout << i << " " ;
    } 
    cout << endl;
    three_big(V_3);
    sort(V.begin(), V.end());
    cout << "Отсортированная 1 последовательность: " << " ";
    for (auto i : V) {
         cout << i << " " ;
    } 
    cout << endl;

    sort(V_2.begin(), V_2.end());
    cout << "Отсортированная 2 последовательность: " << " ";
    for (auto i : V_2) {
         cout << i << " " ;
    } 
    cout << endl;
    vector <int> V_4 = creation_4 (V, V_2);
    vivod(V, V_2, V_3, V_4);
    }
    catch (const char* exeption){
        cerr << "Error" << exeption << endl;
    };


    return 0;
}

vector <int> creation(){
    cout << "Введите колчество элементов поледовательности" << endl;
    int n;
    cin >> n;
    cout << "Введите " << n << " элемент(a/ов) от 1 до 10" << endl;
    vector <int> v(n);
    int k;
    for (int i = 0; i < n; i++) {
        cin >> k;
        if (k<1 || k> 10) {
            throw "out of range";
        }
        v[i] = k;
    }
    cout << "Полученная последовательность: " << " ";
    for (auto i : v) {
         cout << i << " " ;
    } 
    cout << endl;
    return v;
};

vector <int> increase (vector <int> v_) {
    cout << "Введите количество элементов, которые Вы хотите добавить" << endl;
    int n, k;
    cin >> n;
    vector <int> v = v_;
    cout << "Введите эти элементы" << endl;
    for (int i = 0; i < n; i++) {
        cin >>  k;
        if (k<1 || k> 10) {
            throw "out of range";
        }
        vector <int> :: iterator  it = v.end();
        v.insert(it, k);
    }
    cout << "Полученная последовательность: " << " ";
    for (auto i : v) {
         cout << i << " " ;
    } 
    cout << endl;
    return v;
}

vector <int> without_dobles(vector <int> v_){
    vector <int> v = v_;
    vector <int> vec(10, 0);

    for (int i = 0; i < v.size(); i++) {
        vec[v[i]]++;
    }
    for (int i = 0; i < 10 ; i++) {
        if (vec[i] > 1) {
            int n = vec[i];
            vector <int> :: iterator it;
            while ( n > 1) {
                it = v.end();
                while (*it != i) {
                     it--;
                }
                if (it == v.end())
                    vec.pop_back();
                else {
                    it = v.erase(it);
                }
                n--;
            }
        }
    }
    cout << "Полученная последовательность: " << " ";
    for (auto i : v) {
         cout << i << " " ;
    } 
    cout << endl;
    return v;
};

int nechet( vector <int> v) {
    int n = 0;
    for (auto i : v) {
        if ( n % 2 ) {
            n++;
        }
    }
    return n;
}

int max_v( vector <int> v) {
    int n = 0;
    for (auto i : v) {
        if ( i > n ) {
            n = i;
        }
    }
    return n;
}

int min_v( vector <int> v) {
    int n = 11;
    for (auto i : v) {
        if ( i < n )  {
            n = i;
        }
    }
    return n;
}

void easy_number (vector <int> v){
    int n = 0;
    for (int i = 0; i < v.size(); i++) {
        if ((v[i] == 2 || v[i] == 3 || v[i] == 5 || v[i] == 7) && (n == 0)) {
            cout << "Простое число последовательности: " << v[i] 
            << ",  оно стоит на " << i+1 << "-ом(ем) месте"<< endl;
            n++;
        }
    }
    if (n == 0) {
        cout << "В последовательности нет ни одного простого числа" << endl;
    }
};

vector <int> second_degree (vector <int> v_){
    vector <int> v = v_;
    for (int i = 0; i < v.size(); i++) {
        v[i] = v[i]*v[i]; 
    }
    cout << "Полученная последовательность: " << " ";
    for (auto i : v) {
         cout << i << " " ;
    } 
    cout << endl;
    return v;
}

vector <int> creation_2( vector <int> v){
    vector <int> vec(v.size());
    for (auto &i : vec) {
        i = rand() % 50;
    }
    cout << "Полученная 2 последовательность: " << " ";
    for (auto i : vec) {
         cout << i << " " ;
    } 
    cout << endl;
    return vec;
};

int sum_2 (vector <int> & v) {
    int sum = 0;
    for (auto i : v) {
        sum +=i;
    }
    return sum;
}

vector <int> change (vector <int> & v) {

    vector <int> vec = v;
    int n = rand() % v.size();
    for(int i = 0; i < n; i ++) {
        vec[i] =1;
    }
    cout << "Полученная 2 последовательность: " << " ";
    for (auto i : vec) {
         cout << i << " " ;
    } 
    cout << endl;
    return vec;
}

vector <int> creation_3( vector <int> v1, vector <int> v2) {
    vector <int > v3 = v1;
    for (int i = 0; i < v3.size(); i++) {
        v3[i] -=v2[i];
    }
    cout << "Полученная 3 последовательность: " << " ";
    for (auto i : v3) {
         cout << i << " " ;
    } 
    cout << endl;
    return v3;
};

vector <int> nul (vector <int>& v) {
    vector <int> v3 = v;
    for (int i = 0 ; i < v3.size(); i++){
        if (v3[i] < 0) {
            v3[i] = 0;
        }
    }
    cout << "Полученная 3 последовательность: " << " ";
    for (auto i : v3) {
         cout << i << " " ;
    } 
    cout << endl;
    return v3;
}

vector <int> del_nul (vector <int> & v) {
    vector <int> v_ = v;
    for (auto it = v_.begin(); it != v_.end();)
    {
        if (*it ==0){
           it = v_.erase(it);
        }
        else ++it;
    }
    return v_;
}

void three_big (vector <int> & v) {

    vector <int> vv = v;
    sort(vv.begin(), vv.end());
    if (vv.size() < 3) {
        for (auto i : vv) {
            cout << "Элементы: " << i <<  " ";
        }
        cout << endl;
    } else if ( vv.size() == 0){
        cout << "No elements" << endl;}
        else { for (auto it = vv.begin(); it < vv.begin() + 3; it++) {
            cout << "Элементы: " << *it <<  " ";
        }
        cout << endl;

    }
}

vector <int> creation_4 (vector <int>& v1, vector <int>& v2) {
    vector <int> v(v1.size()+v2.size());
    for (int i = 0; i < v1.size(); i++) {
        v[i] = v1[i];
    }
    for (int i = v1.size()+1;i < v1.size()+v2.size(); i++) {
        v[i] = v2[i - v2.size()-1];
    }
    cout << "Полученная 4 последовательность: " << " ";
    for (auto i : v) {
         cout << i << " " ;
    } 
    cout << endl;
    return v;
}

void diapazon (vector <int> & v) {

    vector <int> V(v.size(), 0);
    for (int i = 0; i < v.size(); i++) {
        if (v[i]< 1) {
            V[i]++;
        }
    }
    for (int i = 0; i < V.size(); i++) {
        if (V[i] != 0)
        cout << "Единицу можно вставить перед " << i+1 << "элементом" << endl;
    }
}

void vivod (vector <int> &v1, vector <int> &v2, vector <int> &v3, vector <int> &v4 ) {
    cout << "1 последовательность: " << " ";
    for (auto i : v1) {
         cout << i << " " ;
    } 
    cout << endl;
    cout << "2 последовательность: " << " ";
    for (auto i : v2) {
         cout << i << " " ;
    } 
    cout << endl;
    cout << "3 последовательность: " << " ";
    for (auto i : v3) {
         cout << i << " " ;
    } 
    cout << endl;cout << "4 последовательность: " << " ";
    for (auto i : v4) {
         cout << i << " " ;
    } 
    cout << endl;
}