#ifndef AUCHO_WITHDRAW_OPERATION_H
#define AUCHO_WITHDRAW_OPERATION_H

#include <aucho/account_manager.h>

#include <boost/lexical_cast.hpp>

namespace aucho::commands
{

struct withdraw_operation_t
{
    static std::string_view name()
    {
        return "withdraw";
    }

    static std::string_view description()
    {
        return "withdraw fund or item from account; usage: withdraw fund <amount> | withdraw item <name>";
    }

    static void operation_on_fund(account_t * account_ptr, std::ostream & output, const std::string & value)
    {
        try
        {
            auto integer_value = boost::lexical_cast<uint32_t>(value);
            if (account_ptr->remove_from_fund(integer_value))
                output << "Remove '" << value << "' from account funds\n";
            else
                output << "Not enough funds to withdraw '" << value << "' amount\n";
        }
        catch (...)
        {
            output << "Failed to remove fund due to error\n";
        }
    }

    static void operation_on_item(account_t * account_ptr, std::ostream & output, const std::string & value)
    {
        if (account_ptr->remove_item(value))
            output << "Removed item '" << value << "' from account '" << account_ptr->name() << "'\n";
        else
            output << "Item '" << value << "' doesn't exist on this account '" << account_ptr->name() << "'\n";
    }
};

} // namespace aucho::commands

#endif // AUCHO_WITHDRAW_OPERATION_H
