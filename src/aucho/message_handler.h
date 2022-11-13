#ifndef AUCHO_MESSAGE_HANDLER_H
#define AUCHO_MESSAGE_HANDLER_H

#include <boost/asio/awaitable.hpp>

#include <array>

namespace aucho
{

using message_t = std::array<uint8_t, 1024>;

struct message_handler_i
{
    virtual ~message_handler_i() = default;

    virtual std::tuple<message_t, size_t> initialize(uint64_t connection_id) = 0;
    virtual std::tuple<message_t, size_t> handle_message(uint64_t connection_id, message_t message, size_t message_size) = 0;
};

} // namespace aucho

#endif // AUCHO_MESSAGE_HANDLER_H
