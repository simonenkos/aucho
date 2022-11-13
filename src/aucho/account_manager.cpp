#include <aucho/account_manager.h>

namespace aucho
{

bool account_manager_t::open_account(uint64_t lease_id, const std::string & account_name)
{
    auto new_account = false;
    auto it = _accounts.find(account_name);

    if (_accounts.end() == it)
    {
        it = _accounts.emplace(account_name, account_name).first;
        new_account = true;
    }

    _account_sessions.emplace(lease_id, &(it->second));
    return new_account;
}

void account_manager_t::close_account_session(uint64_t lease_id)
{
    _account_sessions.erase(lease_id);
}

account_t * account_manager_t::get_account_by_lease(uint64_t lease_id) const
{
    auto it = _account_sessions.find(lease_id);
    return (_account_sessions.end() == it) ? nullptr : it->second;
}

} // namespace aucho
