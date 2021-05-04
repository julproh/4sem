#include <iostream>
#include <iostream>
#include <string>
#include <future>
#include <thread>
#include <mutex>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

using namespace std;

char name[10];
std::mutex mute;

void read_data_until(boost::asio::ip::tcp::socket & socket)
{
	while(true){
		boost::asio::streambuf buffer;
		//mute.lock();
		boost::asio::read_until(socket, buffer, '!');
		//mute.unlock();
		std::string message;
		std::istream input_stream(&buffer);
		std::getline(input_stream, message, '!') ;
		std::cout << message << std::endl;

	}
}


void write_data(boost::asio::ip::tcp::socket& socket)
{
	std::string message;
	while(message != "Пока") {
	getline(std::cin, message);
	std::string data = name;
	data += ": ";
	data += message;
	data += "!EOF";
	//mute.lock();
	boost::asio::write(socket, boost::asio::buffer(data));
	//mute.unlock();
	}
}


int main(int argc, char ** argv)
{
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

			//auto read = std::async(std::launch::async, [&socket](){read_data_until(socket);});
			//auto write = std::async(std::launch::async, [&socket](){write_data(socket);});
			thread read{[&socket](){read_data_until(socket);}};
			thread write{[&socket](){write_data(socket);}};
			//read.get();
			//write.get();
			read.join();
			write.join();
		 	//write_data(socket);
		 	//read_data_until(socket);

	}
	catch (boost::system::system_error & e)
	{
		std::cout << e.what() << std::endl;
		return e.code().value();
	}

	return 0;
}
