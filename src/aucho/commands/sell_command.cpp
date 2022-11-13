#include <aucho/commands/sell_command.h>

#include <boost/lexical_cast.hpp>

#include <iostream>

namespace aucho::commands
{

sell_command_t::sell_command_t(account_manager_t * account_manager_ptr,
                               market_t * market_ptr,
                               timer_t * timer_ptr)
: _account_manager_ptr { account_manager_ptr }
, _market_ptr { market_ptr }
, _timer_ptr { timer_ptr } {}

std::string_view sell_command_t::name() const
{
    return "sell";
}

std::string_view sell_command_t::description() const
{
    return "sell an item deposited on account; usage: sell <item> <price>";
}

void sell_command_t::invoke(uint64_t lease_id, const std::vector<std::string> & arguments, std::ostream & output)
{
    auto seller_account_ptr = _account_manager_ptr->get_account_by_lease(lease_id);

    if (!seller_account_ptr)
    {
        output << "No account selected\n";
        return;
    }

    if (arguments.size() != 2)
    {
        output << "Missing argument for sell command. Usage: sell <item> <sell_price>\n";
        return;
    }

    try
    {
        _market_ptr->put_item_on_sale(seller_account_ptr, arguments[0], boost::lexical_cast<uint32_t>(arguments[1]));

        _timer_ptr->start_timer(
            [this, seller_account_ptr, item = arguments[0]]() {
                std::cout << "TIMEOUT" << std::endl;
                _market_ptr->cancel_item_sale(seller_account_ptr, item);
            });
    }
    catch (std::exception & error)
    {
        output << "Failed to process 'sell' command due to an error: " << error.what() << std::endl;
    }
}

} // namespace aucho::commands