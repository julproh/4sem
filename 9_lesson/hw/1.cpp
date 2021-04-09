#define BOOST_DATE_TIME_NO_LIB

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <mutex>
#include <string>
#include <fstream>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <thread>

int main(int argc, char ** argv)
{
	system("pause");

	const std::string shared_memory_name = "text_messeges";

	//boost::interprocess::shared_memory_object::remove(shared_memory_name.c_str()); // !

	boost::interprocess::shared_memory_object shared_memory(
		boost::interprocess::create_only, shared_memory_name.c_str(), boost::interprocess::read_write); 

	shared_memory.truncate(1024);

	//boost::interprocess::mapped_region region(shared_memory, boost::interprocess::read_write);

	//std::memset(region.get_address(), 1, region.get_size()); // !
	std::ifstream in("text.txt");

	const std::string mutex_name = "mutex";

	auto mutex = 
		shared_memory.find_or_construct < boost::interprocess::interprocess_mutex > (
			mutex_name.c_str())();
			
	boost::interprocess::shared_memory_object::remove(shared_memory_name.c_str()); // !

	system("pause");

	return EXIT_SUCCESS;
}