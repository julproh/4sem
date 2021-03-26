#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <chrono>
#include <vector>
#include <fstream>

using namespace std;
using namespace chrono;

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

class Threads_Guard{
    public:

	    explicit Threads_Guard(std::vector < std::thread > & threads) : m_threads(threads) {}
	    Threads_Guard(Threads_Guard const&) = delete;
	    Threads_Guard& operator=(Threads_Guard const&) = delete;
	    ~Threads_Guard() noexcept
	    {
		    try
		    {
			    for (std::size_t i = 0; i < m_threads.size(); ++i)
			    {
				    if (m_threads[i].joinable()){
					    m_threads[i].join();
				    }
			    }
		    }
		    catch (...){}
	}

    private:
	    std::vector < std::thread > & m_threads;
};

template < typename Iterator, typename T > struct accumulate_block
{
	T operator()(Iterator first, Iterator last)
	{
		return std::accumulate(first, last, T());
	}
};

template < typename Iterator, typename T >
T parallel_accumulate(Iterator first, Iterator last, T init, int n)
{
	const std::size_t length = std::distance(first, last);

	if (!length) {
        return init;
    }

    const std::size_t num_threads = (n != 0 ? n:1); 
	const std::size_t block_size = length / num_threads;

	std::vector < std::future < T > > futures(num_threads - 1);
	std::vector < std::thread >		  threads(num_threads - 1);

	Threads_Guard guard(threads);

	Iterator block_start = first;

	for (std::size_t i = 0; i < (num_threads - 1); ++i)
	{
		Iterator block_end = block_start;
		std::advance(block_end, block_size);

		std::packaged_task < T(Iterator, Iterator) > task{
			accumulate_block < Iterator, T >() };

		futures[i] = task.get_future();
		threads[i] = std::thread(std::move(task), block_start, block_end);

		block_start = block_end;
	}

	T last_result = accumulate_block < Iterator, T > ()(block_start, last);

	T result = init;

	for (std::size_t i = 0; i < (num_threads - 1); ++i)
	{
		result += futures[i].get();
	}

	result += last_result;

	return result;
}

int main(int argc, char ** argv)
{   
    std::cout << "Введите количество потоков: " << std::endl;
    int n;
    std::cin >> n;

	std::vector < int > v(100);
	std::iota(v.begin(), v.end(), 1);

	Timer timer("Timer");
	int sum = parallel_accumulate(v.begin(), v.end(), 0, n);
	int time = timer.time_period();
	
	cout << "Сумма элементов: " << sum << endl << "Время: " << time << " мкс" << endl;
	
	ofstream out("2.dat");

	if (!out.is_open()) {
		std::cerr << "Не могу открыть \"2.dat\" " << std::endl;
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < 10; i++) {

		Timer timer("Timer");
		int sum = parallel_accumulate(v.begin(), v.end(), 0, i+1);
		time = timer.time_period();
		out << i+1 <<  "\t" << time << "\n";
	}


	return 0;
}

