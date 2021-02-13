#include <iostream>
#include <vector>
#include <ratio>
#include <chrono>
#include <iomanip>
#include <algorithm>

using namespace std;
using namespace chrono;


template <typename T>
class Timer
{
	nanoseconds elapsed;
	typename T::time_point last;
public:
	Timer(): elapsed(0), last(T::now())
    {};
	void reset()
    {
	    elapsed = nanoseconds::zero();
	    last = T::now();
    };
	void start() 
    {
	    last = T::now();
    };
	void count()
    {
	    typename T::time_point now = T::now();
	    elapsed += now - last;
	    last = now;
    };
	double read() const {
	return static_cast<int>(elapsed.count())*nano::num / nano::den;};
};

void sort_(vector<int> &v){
	for (size_t i = 0; i < v.size() - 1; ++i)
	{
		for (size_t j = i + 1; j < v.size(); ++j)
		{
			if (v[i] > v[j])
			{
				swap(v[i], v[j]);
			}
		}
	}
};

int main()
{
	Timer<steady_clock> timer;

	const auto size = 10000U;

	vector<int> v(size, 0);

	for (size_t i = 0; i < v.size(); ++i)
	{
		v[i] = v.size() - i;
	}

	timer.start();
	timer.count();
	
	auto v_1 = v;
	auto v_2 = v;

	timer.reset();
	sort_(v_1);
	timer.count();

	double _time;
	_time = timer.read();
	cout << "Время 1-ой сортировки " << _time << endl;
	

	timer.start();
	sort(v_2.begin(), v_2.end());
	timer.count();

	cout << "Время 2-ой сортировки " << timer.read() - _time << endl;


	return 0;
}

