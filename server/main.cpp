#include <csignal>
#include <cstdio>
#include <cstdlib>

#include <chrono>
#include <string>
#include <thread>

#include <fmt/format.h>

#include <Poco/Net/NetException.h>
#include <Poco/Net/TCPServer.h>

#include "lib/ip_address.hpp"
#include "lib/port.hpp"
#include "lib/request.hpp"
#include "lib/response.hpp"
#include "lib/socket_read.hpp"

class ClientHandler : public Poco::Net::TCPServerConnection {
public:
  using TCPServerConnection::TCPServerConnection;

  void run() override
  {
    for (;;) {
      lib::RequestHeader header{};

      lib::ReadStatus readStatus{
        lib::socketRead(socket(), &header, sizeof(header))};

      if (readStatus != lib::ReadStatus::Success) {
        return;
      }

      header = header.asHostByteOrder();

      std::string name(header.nameLength, ' ');

      readStatus = lib::socketRead(socket(), name.data(), name.size());

      if (readStatus != lib::ReadStatus::Success) {
        return;
      }

      const std::string ipAddress{socket().peerAddress().host().toString()};
      const std::string message{
        fmt::format("Hello {}! Your IP address is {}", name, ipAddress)};
      const lib::Response response{
        static_cast<std::uint32_t>(header.number1 + header.number2), message};
      socket().sendBytes(response.header(), response.headerSize());
      socket().sendBytes(response.message(), response.messageSize());
    }
  }
};

volatile std::sig_atomic_t gSignalState{0};

void signalHandler(int signal)
{
  gSignalState = signal;
}

int main()
{
  try {
    const Poco::Net::IPAddress     ipAddress{lib::ipAddress};
    const Poco::Net::SocketAddress socketAddress{ipAddress, lib::port};
    const Poco::Net::ServerSocket  serverSocket{socketAddress};
    Poco::Net::TCPServer           tcpServer{
      Poco::Net::TCPServerConnectionFactory::Ptr{
        new Poco::Net::TCPServerConnectionFactoryImpl<ClientHandler>{}},
      serverSocket};
    tcpServer.start();

    std::signal(SIGINT, &signalHandler);
    fmt::print("Hit CTRL+C to exit.\n");

    while (gSignalState != SIGINT) {
      using namespace std::chrono_literals;
      std::this_thread::sleep_for(100ms);
    }

    tcpServer.stop();
  }
  catch (const Poco::Net::NetException& exception) {
    fmt::print(stderr, "Server caught NetException: {}\n", exception.what());
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
