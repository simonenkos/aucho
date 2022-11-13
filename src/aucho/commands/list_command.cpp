#include <aucho/commands/list_command.h>

namespace aucho::commands
{

list_command_t::list_command_t(market_t * market_ptr) : _market_ptr { market_ptr }
{ }

std::string_view list_command_t::name() const
{
    return "list";
}

std::string_view list_command_t::description() const
{
    return "list items on sale; usage: list";
}

void list_command_t::invoke(uint64_t lease_id, const std::vector<std::string> & arguments, std::ostream & output)
{
    const auto & items_on_sale = _market_ptr->get_items_on_sale();

    if (items_on_sale.empty())
        output << "No active sales\n\r";
    else
    {
        output << "Active sales:\n\r";
        for (const auto & sale_entry: _market_ptr->get_items_on_sale())
            output << "Item: '" << sale_entry.first << "'; Price: '" << sale_entry.second._price << "';\n\r";
    }
}

} // namespace aucho::commands
