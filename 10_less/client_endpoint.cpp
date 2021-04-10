#include <iostream>

#include <boost/asio.hpp>

int main(int argc, char ** argv)
{
	std::string raw_ip_address = "127.0.0.1"; //local_host

	auto port = 3333; // берем больше 1000

	boost::system::error_code error_code;

	boost::asio::ip::address ip_address =
		boost::asio::ip::address::from_string(raw_ip_address, error_code);

	if (error_code.value() != 0) 
	{
		std::cout << "Failed to parse the IP address. Error code = " << 
			error_code.value() << ". Message: " << error_code.message();

		return error_code.value();
	}

	boost::asio::ip::tcp::endpoint endpoint(ip_address, port);

	std::cout << "Endpoint ready" << std::endl;

	system("pause");

	return EXIT_SUCCESS;
}