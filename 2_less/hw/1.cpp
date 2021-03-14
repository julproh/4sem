#include <iostream>
#include <vector>

using namespace std;

int main() {

	vector <int> v1(2, 0);

	for (int i = 0; i < 7; i++) {
		if (i <v1.size()) {
			v1[i] = 0;
			cout << i<< "-ая итерация, capasity = " << v1.capacity() << endl;
		}
		else {
			v1.push_back(i);
			cout << i<< "-ая итерация, capasity = " << v1.capacity() << endl;
		}

	}

	cout << "________________" << endl;

	vector <int> v2(2, 0);
	v2.reserve(6);
	for (int i = 0; i < 7; i++) {
		if (i <v2.size()) {
			v2[i] = 0;
			cout << i<< "-ая итерация, capasity = " << v2.capacity() << endl;
		}
		else {
			v2.push_back(i);
			cout << i<< "-ая итерация, capasity = " << v2.capacity() << endl;
		}

	}

	return 0;
}

//результаты изменений capasity можно увидеть, непосредственно запустив программу