#define BOOST_DATE_TIME_NO_LIB
#include <iostream>
#include <string>
#include <future>
#include <chrono>
#include <map>
#include <mutex>
#include <atomic>
#include <thread>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/unordered_map.hpp>

using namespace boost::interprocess;
using char_allocator = allocator<char, managed_shared_memory::segment_manager>;
using shared_string = boost::interprocess::basic_string<char, std::char_traits<char>, char_allocator>;
using pair_str_allocator = allocator < std::pair< std::string, shared_string>, managed_shared_memory::segment_manager >;
using pair_allocator = allocator < std::pair<int, std::pair< std::string, shared_string>>, managed_shared_memory::segment_manager >;
using shared_map = boost::unordered_map< int, std::pair< std::string, shared_string>, boost::hash<int>, std::equal_to<int>, pair_allocator>;

struct Data {
    int* count;
    const std::string shared_memory_name = "managed_shared_memory";
    managed_shared_memory shared_memory = managed_shared_memory(open_or_create, shared_memory_name.c_str(), 4096);
    interprocess_mutex* mutex_ = shared_memory.find_or_construct<interprocess_mutex>("mutex")();
    interprocess_condition* condition = shared_memory.find_or_construct<interprocess_condition>("condition")();
    shared_map* map = shared_memory.find_or_construct<shared_map>("user")(shared_memory.get_segment_manager());
    int* id = shared_memory.find_or_construct<int>("id")(0);
    shared_string* line = shared_memory.find_or_construct<shared_string>("line")(shared_memory.get_segment_manager());
    std::atomic<bool> flag = ATOMIC_VAR_INIT(false);
    std::atomic<bool> end = ATOMIC_VAR_INIT(false);
    std::string personal_name;
    shared_string* current_name;

};

    void message(Data &d)
{
    do {
        getline(std::cin, *d.line);
        std::lock_guard < boost::interprocess::interprocess_mutex > lock(*d.mutex_);
        d.map->emplace(*d.id, std::make_pair(d.personal_name,*d.line));
        (*d.id)++;
        d.flag = true;
        d.condition->notify_all();
    } while (*d.line != "Пока");
    d.end = true;
}
    

    void print(Data& d)
    {
    while (!d.end.load()) {
        std::unique_lock<interprocess_mutex> lock(*d.mutex_);
        d.condition->wait(lock);
        if (!d.flag.load()) {
            std::cout  << d.map->find(((*d.id) - 1))->second.first<<": " << (d.map->find((*d.id) - 1))->second.second << std::endl;
        }
        d.flag = false;
    }
    }

int main() {

    Data dialog;

    std::cout << "Имя участника: ";
    getline(std::cin, dialog.personal_name);
    (*dialog.count)++;


    for (auto i : *dialog.map) {
            std::cout  << i.second.first << ": " << i.second.second << std::endl;
    }
        auto f1 = std::async(message, dialog);
        auto f2 = std::async(print, dialog);
        using namespace std::chrono_literals;
        while (!dialog.end.load()) {
            std::this_thread::sleep_for(2ms);
        }
        f1.get();
        f2.get();
        system("pause");


    shared_memory_object::remove("managed_shared_memory");
    return 0;
    
}