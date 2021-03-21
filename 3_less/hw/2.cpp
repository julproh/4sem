#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>

using namespace std;

unsigned my_hash(float k) {
		
	union 
	{
		float f;
		unsigned u;
	};

	f = k;
	return u;
}

int main() {

	using namespace std::chrono;
	float q = 1.23;

	auto begin_1 = steady_clock::now();
	cout << "result: " << my_hash(q) << endl;
	auto end_1 = steady_clock::now();
	auto delta_1 = duration_cast<nanoseconds>(end_1 - begin_1);
	std::cout << "Time: " << delta_1.count() << " nanoseconds" << std::endl;

	vector<float> v;

	cout << "Введите 10 чисел с плавающей точкой" << endl;
	for (auto i = 0; i < 10; i++) 
	{
		float f;
		cin >> f;
		v.push_back(f);
	}

	sort(v.begin(), v.end());
	
	cout << "number" << setw(10) << setfill(' ') << "hash" << endl;
	
	for (auto it = v.begin(); it < v.end(); it++) 
	{
		cout << left << setw(10) << setfill(' ') 
		<< *it << setw(10) << setfill(' ') 
		<< my_hash(*it) << endl;
	}

	return 0;
}