#ifndef AUCHO_BUY_COMMAND_H
#define AUCHO_BUY_COMMAND_H

#include <aucho/commands/command.h>
#include <aucho/account_manager.h>
#include <aucho/market.h>

namespace aucho::commands
{

class buy_command_t : public command_i
{
    account_manager_t * _account_manager_ptr;
    market_t * _market_ptr;

public:
    explicit buy_command_t(account_manager_t * account_manager_ptr, market_t * market_ptr);

    [[nodiscard]] std::string_view name() const override;
    [[nodiscard]] std::string_view description() const override;

    void invoke(uint64_t lease_id, const std::vector<std::string> & arguments, std::ostream & output) override;
};

} // namespace aucho::commands

#endif //AUCHO_BUY_COMMAND_H
