#include <boost/iostreams/stream.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>

#include <aucho/command_processor.h>

#include <ranges>

namespace aucho
{

command_processor_t & command_processor_t::register_command(std::unique_ptr<commands::command_i> command)
{
    auto [_, result] = _command_registry.emplace(command->name(), std::move(command));
    assert(result);
    return *this;
}

std::tuple<message_t, size_t> command_processor_t::initialize(uint64_t connection_id)
{
    message_t output_message {};

    boost::iostreams::stream<boost::iostreams::basic_array_sink<char>> output { reinterpret_cast<char *>(output_message.data()),
                                                                                output_message.size() };

    output << "Welcome to Auction House!" << std::endl;
    print_command_registry_info(output);

    return { output_message, boost::iostreams::seek(output, 0, std::ios_base::end) };
}

std::tuple<message_t, size_t> command_processor_t::handle_message(uint64_t connection_id, message_t message, size_t message_size)
{
    std::string_view input { reinterpret_cast<char *>(message.data()), message_size };

    message_t output_message {};

    boost::iostreams::stream<boost::iostreams::basic_array_sink<char>> output { reinterpret_cast<char *>(output_message.data()),
                                                                                output_message.size() };

    try
    {
        std::vector<std::string> tokens {};
        boost::split(tokens, input, boost::is_any_of(" \t\n\r"));

        auto cmd = *(tokens.begin());

        if (cmd == "info")
        {
            print_command_registry_info(output);
        }
        else
        {
            auto it = _command_registry.find(cmd);

            if (_command_registry.end() != it)
            {
                auto arguments_range = tokens
                    | std::views::drop(1)
                    | std::views::filter([](const std::string & str) { return !str.empty(); })
                    | std::views::common;

                it->second->invoke(connection_id, { arguments_range.begin(), arguments_range.end() }, output);

                output << "OK\n\n";
            }
            else if (!cmd.empty())
            {
                output << "Unknown command: '" << cmd << "'\n";
                print_command_registry_info(output);
            }
        }
    }
    catch (const std::exception & error)
    {
        output << "Failed to process command: " << error.what() << std::endl;
        print_command_registry_info(output);
    }

    return { output_message, boost::iostreams::seek(output, 0, std::ios_base::end) };
}

void command_processor_t::print_command_registry_info(std::ostream & output) const
{
    output << "Commands description:\n\r";
    output << boost::format("%-10s : %s") % "info" % "show commands description to use on Auction House\n\r";

    for (const auto & [command_name, command_ptr] : _command_registry)
    {
        output << boost::format("%-10s : %s") % command_name % command_ptr->description() << std::endl;;
    }
}

} // namespace aucho