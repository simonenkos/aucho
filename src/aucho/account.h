#ifndef AUCHO_ACCOUNT_H
#define AUCHO_ACCOUNT_H

#include <string>

namespace aucho {

class account {

    std::string _name;

public:
    explicit account(const std::string & name);

    account(const account & other) = default;
    account(account && other) noexcept = default;

    account & operator=(const account & other) = default;
    account & operator=(account && other) noexcept = default;

    ~account() = default;
};

} // namespace aucho

#endif // AUCHO_ACCOUNT_H
