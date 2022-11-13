#ifndef AUCHO_ACCOUNT_COMMAND_H
#define AUCHO_ACCOUNT_COMMAND_H

#include "aucho/account_manager.h"
#include "aucho/commands/command.h"

namespace aucho::commands
{

class account_command_t : public command_i
{
    account_manager_t * _account_manager_ptr { nullptr };

public:
    explicit account_command_t(account_manager_t * account_manager_ptr);

    [[nodiscard]] std::string_view name() const override;
    [[nodiscard]] std::string_view description() const override;

    void invoke(uint64_t lease_id, const std::vector<std::string> & arguments, std::ostream & output) override;
};

} // namespace aucho::commands

#endif // AUCHO_ACCOUNT_COMMAND_H
