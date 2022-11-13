#include <aucho/server.h>

namespace aucho {

server::server(uint16_t port,
               message_handler_i * message_handler)
: _port { port }
, _message_handler { message_handler } { }

boost::asio::awaitable<void> server::run()
{
    uint64_t connection_id = 0;
    auto executor = co_await boost::asio::this_coro::executor;
    boost::asio::ip::tcp::acceptor acceptor { executor, { boost::asio::ip::tcp::v4(), _port } };
    for (;;)
    {
        auto socket = co_await acceptor.async_accept(boost::asio::use_awaitable);
        co_spawn(executor, new_session(std::move(socket), ++connection_id), boost::asio::detached);
    }
}

boost::asio::awaitable<void> server::new_session(boost::asio::ip::tcp::socket socket, uint64_t id)
{
    auto connection_alive = true;
    auto [greeting_message, greeting_message_size] = _message_handler->initialize(id);

    if (greeting_message_size > 0)
    {
        co_await async_write(socket,
                             boost::asio::buffer(greeting_message, greeting_message_size),
                             boost::asio::use_awaitable);
    }

    message_t input_message {};

    do
    {
        try
        {
            auto input_message_size = co_await socket.async_read_some(boost::asio::buffer(input_message), boost::asio::use_awaitable);
            auto [output_message, output_message_size] = _message_handler->handle_message(id, input_message, input_message_size);

            if (output_message_size > 0)
            {
                co_await async_write(socket,
                                     boost::asio::buffer(output_message, output_message_size),
                                     boost::asio::use_awaitable);
            }
        }
        catch (const std::exception & error)
        {
            connection_alive = false;
        }
    }
    while (connection_alive);
}

} // namespace aucho
