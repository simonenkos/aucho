#ifndef AUCHO_LIST_COMMAND_H
#define AUCHO_LIST_COMMAND_H

#include <aucho/commands/command.h>
#include <aucho/market.h>

namespace aucho::commands
{

class list_command_t : public command_i
{
    market_t * _market_ptr;

public:
    explicit list_command_t(market_t * market_ptr);

    [[nodiscard]] std::string_view name() const override;
    [[nodiscard]] std::string_view description() const override;

    void invoke(uint64_t lease_id, const std::vector<std::string> & arguments, std::ostream & output) override;
};

} // namespace aucho::commands

#endif // AUCHO_LIST_COMMAND_H
