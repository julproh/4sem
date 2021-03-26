#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <chrono>
#include <execution>

using namespace std;
using namespace chrono;

class Timer;
void _for_each(vector<int>& v1, vector<int>& v2);
void _transform (vector<int>& v1, vector<int>& v2);
void _sort (vector <int> &v1, vector <int> &v2);

int main()
{
    vector <int> v1 = {3, 5, 2,7, 12, 4, 7};
    vector <int> v2 = v1;

    _for_each (v1, v2);
    _transform(v1, v2);
    _sort(v1, v2);

    return 0;
}


class Timer
{	
	private:
		
		string name;
		steady_clock::time_point begin;
		steady_clock::duration time;
		bool running;
	
	public:
		Timer(const string& name_) :
			name(name_), begin(steady_clock::now()), time(steady_clock::duration::zero()), running(true) {}

		~Timer() = default;
	void pause()
	{
		if (running)
		{
			time = time + steady_clock::now() - begin;
			running = false;
		}
	}

	void proceed()
	{
		if (!running)
		{
			begin = steady_clock::now();
			running = true;
		}
	}


	int time_period(){
		pause();
		auto time_ = duration_cast <microseconds>(time).count();
		if (running){
			proceed();
		}
		return time_;
	}
};

void _for_each(vector<int>& v1, vector<int>& v2) {
    Timer timer("timer1");
    for_each(v1.begin(), v1.end(), [](int& i) {i++;});
	int time = timer.time_period();
	cout << "for_each: " << time << " mcs"<< endl;

    Timer timer2("timer2");
    for_each(execution::par, v2.begin(), v2.end(), [](int& i) {i++;});
	time = timer.time_period();
	cout << "parallel_for_each: " << time << " mcs" << endl;
}

void _transform (vector<int>& v1, vector<int>& v2) {
    Timer timer("timer1");
    transform(v1.begin(), v1.end(), v1.begin(), [](int& i) {return i++;});
	int time = timer.time_period();
	cout << "transform: " << time << " mcs" << endl;

    Timer timer2("timer2");
    transform(execution::par, v2.begin(), v2.end(), v2.begin(),[](int& i) {return i++;});
	time = timer.time_period();
	cout << "parallel_transform: " << time << " mcs" << endl;
}

void _sort (vector <int> &v1, vector <int> &v2) {
    Timer timer("timer1");
    sort(v1.begin(), v1.end());
	int time = timer.time_period();
	cout << "sort: " << time << " mcs" << endl;

    Timer timer2("timer2");
    sort(execution::par, v2.begin(), v2.end());
	time = timer.time_period();
	cout << "parallel_sort: " << time << " mcs" << endl;
}


//g++-10 -std=c++20  4.cpp -o 4 -pthread