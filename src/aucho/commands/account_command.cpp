#include "account_command.h"

namespace aucho::commands
{

account_command_t::account_command_t(account_manager_t * account_manager_ptr)
: _account_manager_ptr { account_manager_ptr }
{ }

std::string_view account_command_t::name() const
{
    return "account";
}

std::string_view account_command_t::description() const
{
    return "open account or create a new one; usage: account <name>";
}

void account_command_t::invoke(uint64_t lease_id,
                               const std::vector<std::string> & arguments,
                               std::ostream & output)
{
    if (arguments.empty())
    {
        output << "Missing account name\n";
    }
    else if (arguments.size() > 1)
    {
        output << "Wrong amount of arguments for 'account' command\n";
    }
    else
    {
        const auto & account_name = arguments.front();

        if (auto account_ptr = _account_manager_ptr->get_account_by_lease(lease_id))
        {
            if (account_name == account_ptr->name())
                return;

            output << "Closing account '" << account_ptr->name() << "'\n";
            _account_manager_ptr->close_account_session(lease_id);
        }

        if (_account_manager_ptr->open_account(lease_id, account_name))
        {
            output << "New account '" << account_name << "' created\n";
        }
        else
        {
            output << "Account '" << account_name << "' opened\n";
        }
    }
}

} // namespace aucho::commands
