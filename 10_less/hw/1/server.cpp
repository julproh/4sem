#include <iostream>
#include <string>
#include <future>
#include <thread>
#include <mutex>

#include <boost/asio.hpp>
using namespace std;

char name[10];
std::mutex mute;
// std::string read_data(boost::asio::ip::tcp::socket & socket)
// {
// 	const std::size_t length = 100;
// 	char buffer[length];
// 	boost::asio::read(socket, boost::asio::buffer(buffer, length));
// 	return std::string(buffer, length);
// }

void read_data_until(boost::asio::ip::tcp::socket & socket)
{	
	//std::lock_guard<std::mutex> lck (mute);
	
	boost::asio::streambuf buffer;
	boost::asio::read_until(socket, buffer, '!');
	std::string message;
	std::istream input_stream(&buffer);
	std::getline(input_stream, message, '!') ;
	std::cout << message << std::endl;


}

void write_data(boost::asio::ip::tcp::socket& socket)
{

	std::string message;
	mute.lock();
	std::cout << "Сообщение: ";
	getline(std::cin, message);
	mute.unlock();
	std::string data = name;
	data += ": ";
	data += message;
	data += "!EOF";
	boost::asio::write(socket, boost::asio::buffer(data));

}

int main(int argc, char ** argv)
{
	//system("chcp 1251");
	const std::size_t size = 100;
	auto port = 4444;
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address_v4::any(), port);
	boost::asio::io_service io_service;

	try
	{
		boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint.protocol());
		acceptor.bind(endpoint);
		acceptor.listen(size);
		boost::asio::ip::tcp::socket socket(io_service);
		acceptor.accept(socket);

		std::cout << "connection succeed" << std::endl;
		std::cout << "Write your name: ";
		std::cin.getline(name, 10);

		// auto read = std::async(std::launch::async, [&socket](){read_data_until(socket);});
		 //auto write = std::async(std::launch::async, [&socket](){write_data(socket);});
		 //std::thread read(read_data_until);
		  //std::thread write(write_data);
		
		while (true) {
		 //write.get();
		 //read.get();
		//write.join();
		//read.join();
		 	write_data(socket);
		 	read_data_until(socket);
		 }
		
	}
	catch (boost::system::system_error & e)
	{
		std::cout << "Конец." << e.what() << std::endl;
		return e.code().value();
	}

	return 0;
}