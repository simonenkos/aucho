#ifndef AUCHO_DEPOSIT_OPERATION_H
#define AUCHO_DEPOSIT_OPERATION_H

#include <aucho/account_manager.h>

#include <boost/lexical_cast.hpp>

namespace aucho::commands
{

struct deposit_operation_t
{
    static std::string_view name()
    {
        return "deposit";
    }

    static std::string_view description()
    {
        return "deposit fund or item to account; usage: deposit fund <amount> | deposit item <name>";
    }

    static void operation_on_fund(account_t * account_ptr, std::ostream & output, const std::string & value)
    {
        try
        {
            auto integer_value = boost::lexical_cast<uint32_t>(value);
            account_ptr->add_to_fund(integer_value);
            output << "Added '" << value << "' to account funds\n\r";
        }
        catch (...)
        {
            output << "Failed to add fund due to error\n\r";
        }
    }

    static void operation_on_item(account_t * account_ptr, std::ostream & output, const std::string & value)
    {
        if (account_ptr->add_item(value))
            output << "Added item '" << value << "' to account '" << account_ptr->name() << "'\n\r";
        else
            output << "Item '" << value << "' already exists\n\r";
    }
};

} // namespace aucho::commands

#endif // AUCHO_DEPOSIT_OPERATION_H
