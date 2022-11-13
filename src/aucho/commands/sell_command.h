#ifndef AUCHO_SELL_COMMAND_H
#define AUCHO_SELL_COMMAND_H

#include <aucho/commands/command.h>
#include <aucho/account_manager.h>
#include <aucho/market.h>
#include <aucho/timer.h>

namespace aucho::commands
{

class sell_command_t : public command_i
{
    account_manager_t * _account_manager_ptr;
    market_t          * _market_ptr;
    timer_t           * _timer_ptr;

public:
    explicit sell_command_t(account_manager_t * account_manager_ptr,
                            market_t * market_ptr,
                            timer_t * timer_ptr);

    [[nodiscard]] std::string_view name() const override;
    [[nodiscard]] std::string_view description() const override;

    void invoke(uint64_t lease_id, const std::vector<std::string> & arguments, std::ostream & output) override;
};

} // namespace aucho::commands

#endif // AUCHO_SELL_COMMAND_H
