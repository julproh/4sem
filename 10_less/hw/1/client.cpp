#include <iostream>
#include <string>
#include <future>
#include <thread>
#include <mutex>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

char name[50];
std::mutex mute;

void read_data_until(boost::asio::ip::tcp::socket & socket) 
{	
	mute.lock();
	//std::cout << "start read" << std:: endl;
	boost::asio::streambuf buffer;
	boost::asio::read_until(socket, buffer, '!');
	std::string message;
	std::istream input_stream(&buffer);
	std::getline(input_stream, message, '!');
	std::cout << message << std::endl;
	//std::cout << "end read" << std:: endl;
	mute.unlock();

}

void write_data(boost::asio::ip::tcp::socket& socket)
{
	mute.lock();
	//std::cout << "start write" << std:: endl;
	std::cout << "Текст: ";
	std::string message;
	while(message != "Пока") {
	getline(std::cin, message);
	std::string data = name;
	data += ": ";
	data += message;
	data += "!EOF";
	boost::asio::write(socket, boost::asio::buffer(data));
	//std::cout << "end write" << std:: endl;
	mute.unlock();
	}
	

}

int main()
{
	std::string raw_ip_address = "127.0.0.1";
	auto port = 4444;
	const std::size_t size = 30;

	try
	{
		boost::asio::ip::tcp::endpoint endpoint(
		boost::asio::ip::address::from_string(raw_ip_address), port);
		boost::asio::io_service io_service;

		boost::asio::ip::tcp::socket socket(io_service, endpoint.protocol());
		
		socket.connect(endpoint);

		std::cout << "Имя: ";
		std::cin.getline(name, 50);


		while (true) {
			//auto read = std::async([ &socket](){read_data_until(socket);});
			boost::thread write{[&socket](){write_data(socket);}};
			//auto write = std::async([&socket](){write_data(socket);});
			boost::thread read{[&socket](){read_data_until(socket);}};
			boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint.protocol());
			acceptor.bind(endpoint);
			acceptor.listen(size);
			//auto read = std::async([&socket](){read_data_until(socket);});
			//read.get();
			//write.get();
			write.join();
			read.join();
		}
	}
	
	catch (boost::system::system_error& e)
	{
		std::cout << "Error code = " << e.code() << ". Message: " << e.what() << std::endl;
		return e.code().value();
	}

	return 0;
}
	