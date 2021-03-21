#include <iostream>
#include <set>
#include <chrono>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;
using namespace std::chrono;

class Timer;
int nlogn_vector (int);
int nlogn_set (int);
void print_1 ();
void print_2 (int &);

int main()
{
	print_1();

	for (auto n = 10; n < 1000000; n *= 10)
	{
		print_2(n);
	}

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


	int time_period()
	{
		pause();
		auto time_ = duration_cast <microseconds>(time).count();
		if (running)
		{
			proceed();
		}
		return time_;
	}

};

int nlogn_vector (int n) {

	Timer timer_vector("Timer for vector");
	vector<int> vector(n, 0);
	for (int i = 0; i < n; ++i)
	{
		vector[i] = n - i;
	}
	sort(vector.begin(), vector.end());
	int result_vector = timer_vector.time_period();

	return result_vector;	

};

int nlogn_set (int n) {

	Timer timer_set("timer for set");

	set <int> set;
	for (int i = 0; i < n; ++i)
	{
		set.insert(n - i);
	}
	int result_set = timer_set.time_period();

	return result_set;	

};

void print_1 () {

	cout << 'N' << setw(12) << setfill(' ')
	<< "set" << setw(13) << setfill(' ') 
	<< "vector"  << endl;
}

void print_2 (int &n) {
	cout << left << setw(10) << setfill(' ') << n
		<< setw(10) << setfill(' ') << nlogn_set(n)
		<< setw(10) << setfill(' ') << nlogn_vector(n)
		<< endl;
}