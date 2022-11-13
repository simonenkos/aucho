#include <aucho/account.h>

#include <boost/algorithm/string/join.hpp>

namespace aucho
{

account_t::account_t(const std::string & name) : _name { name }
{ }

const std::string & account_t::name() const
{
    return _name;
}

void account_t::add_to_fund(uint32_t value)
{
    _funds += value;
}

uint32_t account_t::get_funds_amount() const
{
    return _funds;
}

bool  account_t::remove_from_fund(uint32_t value)
{
    if (value > _funds)
        return false;

    _funds -= value;
    return true;
}

bool account_t::add_item(const std::string & item)
{
    return _items.emplace(item).second;
}

bool account_t::has_item(const std::string & item) const
{
    return _items.contains(item);
}

void account_t::log_all_items(std::ostream & output) const
{
    output << boost::join(_items, " ");
}

bool account_t::remove_item(const std::string & item)
{
    return (0 != _items.erase(item));
}

} // namespace aucho
