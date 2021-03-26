#include <algorithm>
#include <thread>
#include <vector>

void f(int i) {}

int main(int argc, char ** argv)
{
	std::vector < std::thread > threads;

	for (std::size_t i = 0; i < std::thread::hardware_concurrency(); ++i)
	{
		threads.push_back(std::thread(f, i));
	}

	std::for_each(threads.begin(), threads.end(),
		std::mem_fn(&std::thread::join));

	system("pause");

	return EXIT_SUCCESS;
}