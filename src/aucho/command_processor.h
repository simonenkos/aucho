#ifndef AUCHO_COMMAND_PROCESSOR_H
#define AUCHO_COMMAND_PROCESSOR_H

#include <map>

#include <aucho/commands/command.h>
#include <aucho/message_handler.h>

namespace aucho {

class command_processor_t : public message_handler_i {

    std::map<std::string, std::unique_ptr<commands::command_i>> _command_registry;

public:
    command_processor_t() = default;

    command_processor_t(const command_processor_t & other) = delete;
    command_processor_t(command_processor_t && other) noexcept = delete;

    command_processor_t & operator=(const command_processor_t & other) = delete;
    command_processor_t & operator=(command_processor_t && other) noexcept = delete;

    ~command_processor_t() override = default;

    command_processor_t & register_command(std::unique_ptr<commands::command_i> command);

private:
    std::tuple<message_t, size_t> initialize(uint64_t connection_id) override;
    std::tuple<message_t, size_t> handle_message(uint64_t connection_id, message_t message, size_t message_size) override;

    void print_command_registry_info(std::ostream & output) const;
};

} // namespace aucho

#endif //AUCHO_COMMAND_PROCESSOR_H
