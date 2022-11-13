#include <aucho/commands/buy_command.h>

namespace aucho::commands
{

buy_command_t::buy_command_t(account_manager_t * account_manager_ptr, market_t * market_ptr)
: _account_manager_ptr { account_manager_ptr }
, _market_ptr { market_ptr }
{ }

std::string_view buy_command_t::name() const
{
    return "buy";
}

std::string_view buy_command_t::description() const
{
    return "buy an item that was put on sale; usage: buy <item>";
}

void buy_command_t::invoke(uint64_t lease_id, const std::vector<std::string> & arguments, std::ostream & output)
{
    auto buyer_account_ptr = _account_manager_ptr->get_account_by_lease(lease_id);

    if (!buyer_account_ptr)
    {
        output << "No account selected\n\r";
        return;
    }

    if (arguments.size() != 1)
    {
        output << "Missing argument for buy command. Usage: buy <item>\n\r";
        return;
    }

    try
    {
        _market_ptr->buy_item(buyer_account_ptr, arguments[0]);
    }
    catch (std::exception & error)
    {
        output << "Failed to process 'buy' command due to an error: " << error.what() << "\n\r";
    }
}

} // namespace aucho::commands