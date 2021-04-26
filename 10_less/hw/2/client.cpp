#include <iostream>
#include <string>
#include <future>
#include <thread>
#include <mutex>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
std::mutex mtx;

char name[50];
std::mutex mute;
void read_data_until(boost::asio::ip::tcp::socket & socket) 
{	
	std::lock_guard<std::mutex> lck (mute);
	boost::asio::streambuf buffer;
	boost::asio::read_until(socket, buffer, '!');
	std::string message;
	std::istream input_stream(&buffer);
	std::getline(input_stream, message, '!');
	std::cout << message << std::endl;

}

void write_data(boost::asio::ip::tcp::socket& socket)
{
	std::string message;
	while(message != "Пока") {
	mute.lock();
	std::cout << "Текст: ";
	getline(std::cin, message);
	mute.unlock();
	std::string data = name;
	data += ": ";
	data += message;
	data += "!EOF";
	//std::cout << std::endl << data << std::endl;
	boost::asio::write(socket, boost::asio::buffer(data));
	}

}

int main()
{
	//system("chcp 1251");
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

		auto read = std::async([&socket](){read_data_until(socket);});
		//boost::thread read(read_data_until, &socket);
		auto write = std::async([&socket](){write_data(socket);});
		//boost::thread write(write_data, socket);

		while (true) {
			boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint.protocol());
			acceptor.bind(endpoint);
			acceptor.listen(size);
			read.get();
			//write_data(socket);
			//write.join();
			//std::cout << read_data_until(socket) << std::endl;
			write.get();
			//read.join();
		}
	}
	
	catch (boost::system::system_error& e)
	{
		std::cout << "Error code = " << e.code() << ". Message: " << e.what() << std::endl;
		system("pause");
		return e.code().value();
	}

	system("pause");
	return 0;
}
	
	