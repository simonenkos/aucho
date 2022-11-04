#ifndef AUCHO_ACCOUNT_MANAGER_H
#define AUCHO_ACCOUNT_MANAGER_H

#include <set>

#include <aucho/account.h>

namespace aucho {

class account_manager {

    std::set<account> _accounts;

public:
    account_manager() = default;

    void create_account();
    void remove_account();



};

} // namespace aucho

#endif // AUCHO_ACCOUNT_MANAGER_H
