#ifndef AUCHO_STATUS_COMMAND_H
#define AUCHO_STATUS_COMMAND_H

#include <aucho/commands/command.h>
#include <aucho/account_manager.h>

namespace aucho::commands
{

class status_command_t : public command_i
{
    account_manager_t * _account_manager_ptr;

public:
    explicit status_command_t(account_manager_t * account_manager_ptr);

    [[nodiscard]] std::string_view name() const override;
    [[nodiscard]] std::string_view description() const override;

    void invoke(uint64_t lease_id, const std::vector<std::string> & arguments, std::ostream & output) override;
};

} // namespace aucho::commands

#endif // AUCHO_STATUS_COMMAND_H
