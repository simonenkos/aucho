#ifndef AUCHO_ACCOUNT_MANAGER_H
#define AUCHO_ACCOUNT_MANAGER_H

#include <map>

#include <aucho/account.h>

namespace aucho {

class account_manager_t {

    std::map<std::string, account_t> _accounts;
    std::map<uint64_t, account_t *>  _account_sessions;

public:
    account_manager_t() = default;

    account_manager_t(const account_manager_t & other) = delete;
    account_manager_t(account_manager_t && other) noexcept = delete;

    account_manager_t & operator=(const account_manager_t & other) = delete;
    account_manager_t & operator=(account_manager_t && other) noexcept = delete;

    ~account_manager_t() = default;

    bool open_account(uint64_t lease_id, const std::string & account_name);
    void close_account_session(uint64_t lease_id);

    [[nodiscard]] account_t * get_account_by_lease(uint64_t lease_id) const;
};

} // namespace aucho

#endif // AUCHO_ACCOUNT_MANAGER_H
