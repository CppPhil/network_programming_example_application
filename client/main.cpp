#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <limits>
#include <string>
#include <string_view>

#include <fmt/format.h>

#include <Poco/Net/NetException.h>
#include <Poco/Net/StreamSocket.h>

#include "lib/ip_address.hpp"
#include "lib/port.hpp"
#include "lib/request.hpp"
#include "lib/response_header.hpp"
#include "lib/socket_read.hpp"

std::istream& readUserOption(std::string& buffer)
{
  fmt::print("Enter your name or \"EXIT\": ");
  return std::getline(std::cin, buffer);
}

std::uint16_t readNumber(std::string_view prompt)
{
  fmt::print("{}", prompt);
  std::uint16_t buffer{};

  while (!(std::cin >> buffer)) {
    fmt::print(stderr, "Invalid input, please try again: ");
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return buffer;
}

int main()
{
  try {
    const Poco::Net::IPAddress     ipAddress{lib::ipAddress};
    const Poco::Net::SocketAddress socketAddress{ipAddress, lib::port};
    Poco::Net::StreamSocket socket{Poco::Net::SocketAddress::Family::IPv4};
    socket.setReuseAddress(true);
    socket.setReusePort(true);
    socket.connect(socketAddress);

    std::string       userInput{};
    const std::string exitOption{"EXIT"};

    while (readUserOption(userInput) && (userInput != exitOption)) {
      const std::uint16_t number1{readNumber("Please enter the 1st number: ")};
      const std::uint16_t number2{readNumber("Please enter the 2nd number: ")};
      const lib::Request  request{number1, number2, userInput};
      socket.sendBytes(request.header(), request.headerSize());
      socket.sendBytes(request.name(), request.nameSize());

      lib::ResponseHeader header{};
      lib::ReadStatus     readStatus{
        lib::socketRead(socket, &header, sizeof(header))};

      if (readStatus != lib::ReadStatus::Success) {
        return EXIT_FAILURE;
      }

      header = header.asHostByteOrder();
      std::string message(header.messageLength, ' ');

      readStatus = lib::socketRead(socket, message.data(), message.size());

      if (readStatus != lib::ReadStatus::Success) {
        return EXIT_FAILURE;
      }

      fmt::print("result: {}\n", header.result);
      fmt::print("message: {}\n", message);
    }
  }
  catch (const Poco::Net::NetException& exception) {
    fmt::print(stderr, "Client caught NetException: {}\n", exception.what());
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
