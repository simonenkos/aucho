#ifndef AUCHO_TIMER_H
#define AUCHO_TIMER_H

#include <boost/asio.hpp>

#include <chrono>

namespace aucho
{

class timer_t
{
    boost::asio::io_context * _io_context_ptr { nullptr };
    const std::chrono::seconds _timeout_duration;

public:
    explicit timer_t(boost::asio::io_context * io_context_ptr,
                     std::chrono::seconds duration);

    timer_t(const timer_t &) = delete;
    timer_t(timer_t &&) noexcept = delete;

    timer_t & operator=(const timer_t &) = delete;
    timer_t & operator=(timer_t &&) noexcept = delete;

    ~timer_t() = default;

    void start_timer(const std::function<void()> & on_timeout);

private:
    boost::asio::awaitable<void> timer(std::function<void()> on_timeout);

};

} // namespace aucho

#endif // AUCHO_TIMER_H
