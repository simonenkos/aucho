#include <aucho/commands/status_command.h>

namespace aucho::commands
{

status_command_t::status_command_t(account_manager_t * account_manager_ptr)
: _account_manager_ptr { account_manager_ptr } {}

std::string_view status_command_t::name() const
{
    return "status";
}

std::string_view status_command_t::description() const
{
    return "report status of the account including deposited funds and items; usage: status";
}

void status_command_t::invoke(uint64_t lease_id, const std::vector<std::string> & arguments, std::ostream & output)
{
    auto account_ptr = _account_manager_ptr->get_account_by_lease(lease_id);

    if (!account_ptr)
    {
        output << "No account selected" << std::endl;
        return;
    }

    output << "Account status:\n";
    output << "Funds: '" << account_ptr->get_funds_amount() << "'; Items: ";
    account_ptr->log_all_items(output);
    output << "\n";
}

} // namespace aucho::commands
