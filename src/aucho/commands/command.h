#ifndef AUCHO_COMMAND_H
#define AUCHO_COMMAND_H

#include <ostream>
#include <vector>
#include <string>

namespace aucho::commands
{

struct command_i
{
    virtual ~command_i() = default;

    [[nodiscard]] virtual std::string_view name() const = 0;
    [[nodiscard]] virtual std::string_view description() const = 0;

    virtual void invoke(uint64_t lease_id, const std::vector<std::string> & arguments, std::ostream & output) = 0;
};

} // namespace aucho::commands

#endif // AUCHO_COMMAND_H
