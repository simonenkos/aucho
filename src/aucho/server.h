#ifndef AUCHO_SERVER_H
#define AUCHO_SERVER_H

#include <boost/asio.hpp>

#include <aucho/message_handler.h>

namespace aucho {

class server {

    uint16_t _port;
    message_handler_i * _message_handler;

public:
    explicit server(uint16_t port,
                    message_handler_i * message_handler);

    server(const server & other) = delete;
    server(server && other) noexcept = delete;

    server & operator=(const server & other) = delete;
    server & operator=(server && other) = delete;

    ~server() = default;

    boost::asio::awaitable<void> run();

private:
    boost::asio::awaitable<void> new_session(boost::asio::ip::tcp::socket socket, uint64_t id);
};

} // namespace aucho

#endif // AUCHO_SERVER_H
