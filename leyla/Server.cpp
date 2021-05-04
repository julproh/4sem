#include <iostream>
#include <string>
#include <thread>
#include <atomic>

#include <boost/asio.hpp>

std::string user_name;

std::atomic <bool> flag(true);

void write_data(boost::asio::ip::tcp::socket& socket) {
	std::string data;
	while (flag) {
		std::getline(std::cin, data);
		if (data == "EXIT") {
			flag = false;
		}
		data.insert(0, user_name);
		data.push_back('\n');
		boost::asio::write(socket, boost::asio::buffer(data));
	}
}

void read_data(boost::asio::ip::tcp::socket& socket) {
	std::string data;
	boost::asio::streambuf buffer;
	std::istream input_stream(&buffer);
	while (flag && data.find_first_of("EXIT") == std::string::npos) {
		boost::asio::read_until(socket, buffer, '!');
		std::getline(input_stream, data, '!');
		std::cout << data << std::endl;
	}
}

int main() {
	system("chcp 1251");
	std::cout << "Enter your nickname: ";
	std::getline(std::cin, user_name);
	if (!user_name.empty())
		user_name.push_back(':');
	system("pause");

	const std::string ip_address = "127.0.0.1";
	const auto port = 3333;

	try {
		boost::asio::ip::tcp::endpoint endpoint(
			boost::asio::ip::address_v4::any(), port
		);

		boost::asio::io_service ios;
		boost::asio::ip::tcp::acceptor acceptor(ios, endpoint.protocol());

		acceptor.bind(endpoint);
		acceptor.listen(25);

		boost::asio::ip::tcp::socket socket(ios);
		acceptor.accept(socket);

		std::thread t(write_data, std::ref(socket));
		std::thread t1(read_data, std::ref(socket));
		t.join();
		t1.join();
	}
	catch (boost::system::system_error& e) {
		std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;
		system("pause");
		return e.code().value();
	}
	system("pause");

	return 0;
}
