#include <aucho/timer.h>

namespace aucho
{

timer_t::timer_t(boost::asio::io_context * io_context_ptr,
                 std::chrono::seconds timeout_duration)
: _io_context_ptr { io_context_ptr }
, _timeout_duration { timeout_duration }
{ }

void timer_t::start_timer(const std::function<void()> & on_timeout)
{
    co_spawn(*_io_context_ptr, timer(on_timeout), boost::asio::detached);
}

boost::asio::awaitable<void> timer_t::timer(std::function<void()> on_timeout)
{
    boost::asio::system_timer timer { co_await boost::asio::this_coro::executor };
    timer.expires_after(_timeout_duration);
    try
    {
        co_await timer.async_wait(boost::asio::use_awaitable);
        on_timeout();
    }
    catch (const boost::system::system_error & error)
    {
        // do nothing
    }
}


} // namespace aucho