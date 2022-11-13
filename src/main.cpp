#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/write.hpp>

#include <aucho/commands/account_command.h>
#include <aucho/commands/account_operations_command.h>
#include <aucho/commands/deposit_operation.h>
#include <aucho/commands/withdraw_operation.h>
#include <aucho/commands/sell_command.h>
#include <aucho/commands/buy_command.h>
#include <aucho/commands/list_command.h>
#include <aucho/commands/status_command.h>
#include <aucho/command_processor.h>
#include <aucho/server.h>
#include <aucho/market.h>
#include <aucho/timer.h>

constexpr uint32_t market_fee = 10U;

int main()
{
    boost::asio::io_context io_context {};
    boost::asio::signal_set signals(io_context, SIGINT, SIGTERM);

    signals.async_wait([&](auto, auto) {
        io_context.stop();
    });

    using namespace std::chrono_literals;

    aucho::account_manager_t account_manager {};
    aucho::market_t market { market_fee };
    aucho::timer_t selling_timer { &io_context, 5min };
    aucho::command_processor_t command_processor {};

    command_processor
        .register_command(std::make_unique<aucho::commands::account_command_t>(&account_manager))
        .register_command(std::make_unique<aucho::commands::account_operations_command_t<aucho::commands::deposit_operation_t>>(&account_manager))
        .register_command(std::make_unique<aucho::commands::account_operations_command_t<aucho::commands::withdraw_operation_t>>(&account_manager))
        .register_command(std::make_unique<aucho::commands::sell_command_t>(&account_manager, &market, &selling_timer))
        .register_command(std::make_unique<aucho::commands::buy_command_t>(&account_manager, &market))
        .register_command(std::make_unique<aucho::commands::list_command_t>(&market))
        .register_command(std::make_unique<aucho::commands::status_command_t>(&account_manager));

    aucho::server server { 55555, &command_processor };

    co_spawn(io_context, server.run(), boost::asio::detached);

    io_context.run();
    return 0;
}
