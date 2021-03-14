#include<iostream>
#include<algorithm>
#include<chrono>
#include<vector>
#include<array>
#include<deque>
#include<list>
#include<forward_list>

using namespace std;
using namespace chrono;

template <typename T>
void time_for_sort(T x) {
	auto begin = steady_clock::now();
	sort(x.begin(), x.end());
	auto end = steady_clock::now();
	auto delta = duration_cast<nanoseconds>(end - begin);
	cout << "Длительность: " << delta.count() << " наносекунд - ";
}

template <typename P>
void time_for_sort2(P x) {
	auto begin = steady_clock::now();
	x.sort();
	auto end = steady_clock::now();
	auto delta = duration_cast<nanoseconds>(end - begin);
	cout << "Длительность: " << delta.count() << " наносекунд - ";
}


int main() {

	vector <int> v = { 1,3,5,7,9 };
	array <int, 5> a = { 1,3,5,7,9 };
	deque <int> dq = { 1,3,5,7,9 };
	list <int> ls = { 1,3,5,7,9 };
	forward_list <int> fl = { 1,3,5,7,9 };

    time_for_sort(a); 
    cout << "array" << endl;
    
	time_for_sort(v); 
    cout << "vector" << endl;

    time_for_sort2(fl); 
    cout << "forward list" << endl;

	time_for_sort(dq); 
    cout << "deque" << endl;

	time_for_sort2(ls); 
    cout << "list" << endl;

	return 0;
}

// Рейтинг по бытроте:
// 1 - array
// 2 - vector
// 3 - forward_list
// 4 - deque
// 5 - list