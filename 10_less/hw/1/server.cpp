#include <iostream>
#include <string>

#include <boost/asio.hpp>
using namespace std;

std::string read_data(boost::asio::ip::tcp::socket & socket)
{
	const std::size_t length = 100;
	char buffer[length];
	boost::asio::read(socket, boost::asio::buffer(buffer, length));
	return std::string(buffer, length);
}

std::string read_data_until(boost::asio::ip::tcp::socket & socket)
{
	boost::asio::streambuf buffer;
	boost::asio::read_until(socket, buffer, '!');
	std::string message;
	std::istream input_stream(&buffer);
	std::getline(input_stream, message, '!');

	return message;
}

void write_data(boost::asio::ip::tcp::socket& socket)
{
	char message[100];
	std::cout << "Сообщение: ";
	std::cin.getline(message, 100);
	std::string data = name;
	data = ": " + message + "!EOF";
	boost::asio::write(socket, boost::asio::buffer(data));
}

int main(int argc, char ** argv)
{
	system("chcp 1251");
	const std::size_t size = 100;
	auto port = 3333;
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
		while (true) {
			std::cout << read_data_until(socket) << std::endl;
			write_data(socket);
		}
		
	}
	catch (boost::system::system_error & e)
	{
		std::cout << "Конец." << e.what() << std::endl;
		return e.code().value();
	}

	return 0;
}