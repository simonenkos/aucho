#ifndef AUCHO_ACCOUNT_OPERATIONS_COMMAND_H
#define AUCHO_ACCOUNT_OPERATIONS_COMMAND_H

#include <aucho/commands/command.h>
#include <aucho/account_manager.h>

#include <boost/lexical_cast.hpp>

#include <concepts>
#include <type_traits>

namespace aucho::commands
{

namespace concepts
{
    template<typename command_t>
    concept account_operation = requires(account_t * account_ptr,
                                         std::ostream & output,
                                         const std::string & value)
    {
        { command_t::name() }        -> std::same_as<std::string_view>;
        { command_t::description() } -> std::same_as<std::string_view>;

        command_t::operation_on_fund(account_ptr, output, value);
        command_t::operation_on_item(account_ptr, output, value);
    };

} // namespace concepts

template <concepts::account_operation operation_impl_t>
class account_operations_command_t : public command_i
{
    account_manager_t * _account_manager_ptr { nullptr };

public:
    explicit account_operations_command_t(account_manager_t * account_manager_ptr)
    : _account_manager_ptr { account_manager_ptr } {}

private:
    [[nodiscard]] std::string_view name() const override
    {
        return operation_impl_t::name();
    }

    [[nodiscard]] std::string_view description() const override
    {
        return operation_impl_t::description();
    }

    void invoke(uint64_t lease_id, const std::vector<std::string> & arguments, std::ostream & output) override
    {
        auto account_ptr = _account_manager_ptr->get_account_by_lease(lease_id);

        if (!account_ptr)
        {
            output << "No account selected for deposit\n";
            return;
        }

        if (arguments.empty())
        {
            output << "Missing deposit type: 'fund' or 'item'\n";
            return;
        }

        const auto & type = arguments.front();

        if (type == "fund")
        {
            if (arguments.size() == 2)
                operation_impl_t::operation_on_fund(account_ptr, output, arguments[1]);
            else
                output << "Invalid arguments\n";
        }
        else if (type == "item")
        {
            if (arguments.size() == 2)
                operation_impl_t::operation_on_item(account_ptr, output, arguments[1]);
            else
                output << "Invalid arguments\n";
        }
        else
        {
            output << "Unknown deposit type: " << type << std::endl;
        }
    }
};

} // namespace aucho::commands

#endif // AUCHO_ACCOUNT_OPERATIONS_COMMAND_H
