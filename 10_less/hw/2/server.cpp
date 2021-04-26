#include <iostream>
#include <string>
#include <mutex>
#include <boost/asio.hpp>
using namespace std;

char name[10];
std::mutex mute;

void read_data_until(boost::asio::ip::tcp::socket & socket)
{
	boost::asio::streambuf buffer;

	boost::asio::read_until(socket, buffer, '!');

	std::string message;
	std::istream input_stream(&buffer);
	std::getline(input_stream, message, '!');
	std::cout<<message << std::endl;
}

void write_data(boost::asio::ip::tcp::socket& socket)
{
	std::string message;
	mute.lock();
	std::cout << "Сообщение: ";
	std::cin.getline(message, 100);
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
	auto port = 8000;
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address_v4::any(), port);
	boost::asio::io_service io_service;

	try
	{
		boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint.protocol());
		acceptor.bind(endpoint);
		acceptor.listen(size);
		boost::asio::ip::tcp::socket socket(io_service);
		acceptor.accept(socket);

		std::cout << "есть соединение" << std::endl;
		std::cout << "Имя: ";
		std::cin.getline(name, 10);

		while (true) {
			read_data_until(socket);
			write_data(socket);
		}
	}
	catch (boost::system::system_error & err)
	{
		std::cout << "Chat is ended. " << err.what() << std::endl;
		return err.code().value();
	}

	return 0;
}