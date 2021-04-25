#include <iostream>
#include <string>
#include <boost/asio.hpp>
using namespace std;

char name[10];

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
	data = ": "+ message + "!EOF";
	boost::asio::write(socket, boost::asio::buffer(data));
}

int main(int argc, char ** argv)
{
	system("chcp 1251");

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
			std::cout << read_data_until(socket) << std::endl;
			write_data(socket);
		}
	}
	catch (boost::system::system_error & err)
	{
		std::cout << "Chat is ended. " << err.what() << std::endl;

		system("pause");

		return err.code().value();
	}

	return EXIT_SUCCESS;
}