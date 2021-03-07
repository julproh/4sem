#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

vector <int> creation();
vector <int> increase (vector <int>);
vector <int> without_dobles(vector <int>);
void prime_number (vector <int>);
vector <int> creation_2( vector <int>);
vector <int> change (vector <int> & );
vector <int> creation_3( vector <int>, vector <int>);
void three_big (vector <int> &);
vector <int> creation_4 (vector <int> &, vector <int> &);
void diapazon (vector <int> &) ;
int main() {

    try {
    vector <int> V = creation(); // создаю последовательность
    
    random_device rd;
    for (int i = 0; i < 5; i++){
        V.insert(V.end(), rd()%10);
    }

    random_shuffle(V.begin(), V.end()); //перемешиваю

    V = without_dobles(V);

    
    cout << "В последовательности " << count_if(V.begin(), V.end(), [](int i) { return i % 2 != 0; }) << " нечетных чисел" << endl;

    cout << "Максимум последовательности " << *max_element(V.begin(), V.end()) << ", минимум последовательности:" << *min_element(V.begin(), V.end()) << endl;


    prime_number(V);

    for_each(V.begin(), V.end(), [](int& i) { i = i * i; });

    vector <int> V_2 = creation_2(V); 

    cout << "Сумма членов второй последовательности: "<< accumulate(V_2.begin(), V_2.end(), 0, [](int sum, int elem) {return sum +=elem;}) << endl;
    
    fill_n(V_2.begin(), rand()%V_2.size(), 1);

    vector <int> V_3 = creation_3(V, V_2);
    
    for_each(V_3.begin(), V_3.end(), [](int &n){if (n < 0) n = 0;
    return true;}); // меняем отрицательные на нули

    
    while (find(V_3.begin(), V_3.end(), 0) != V_3.end()) {
			V_3.erase(find(V_3.begin(), V_3.end(), 0));
    } //удаляем нули


    reverse(V_3.begin(), V_3.end());

    cout << "Полученная 3 последовательность: " << " ";
    for (auto i : V_3) {
         cout << i << " " ;
    } 
    cout << endl;

    sort(V_3.begin(),V_3.end());
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
    
    diapazon (V_4);
    
	cout << "V_1:" << endl;
	for_each(V.begin(), V.end(), [](int i) {cout << i << " "; });
	cout << endl << "V_2:" << endl;;
	for_each(V_2.begin(), V_2.end(), [](int i) {cout << i << " "; });
	cout << endl << "V_3:" << endl;;
	for_each(V_3.begin(), V_3.end(), [](int i) {cout << i << " "; });
	cout << endl << "V_4:" << endl;;
	for_each(V_4.begin(), V_4.end(), [](int i) {cout << i << " "; });
	cout << endl;

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


void prime_number (vector <int> v){
    int n = 0;
    for (auto i:v) {
        if (i > 1 && n ==0) {
        for (int j = 2; j < i*i; j++) 
        {   if (i % j ==0) {
            cout << "Простое число последовательности: " << i << endl;
            n++;
            break; }
        } }
    }
    if (n == 0) {
        cout << "В последовательности нет ни одного простого числа" << endl;
    }
};


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


void three_big (vector <int> & v) {

    if (v.size() < 3) {
        for (auto i : v) {
            cout << "Элементы: " << i <<  " ";
        }
        cout << endl;
    } else if ( v.size() == 0){
        cout << "No elements" << endl;}
        else { for (auto it = v.begin(); it < v.begin() + 3; it++) {
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

