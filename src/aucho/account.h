#ifndef AUCHO_ACCOUNT_H
#define AUCHO_ACCOUNT_H

#include <string>
#include <set>

namespace aucho {

class account_t {

    std::string _name;

    uint32_t _funds { 0 };
    std::set<std::string> _items {};

public:
    explicit account_t(const std::string & name);

    account_t(const account_t & other) = default;
    account_t(account_t && other) noexcept = default;

    account_t & operator=(const account_t & other) = default;
    account_t & operator=(account_t && other) noexcept = default;

    ~account_t() = default;

    [[nodiscard]] const std::string & name() const;

    void add_to_fund(uint32_t value);
    [[nodiscard]] uint32_t get_funds_amount() const;
    bool remove_from_fund(uint32_t value);

    bool add_item(const std::string & item);
    bool has_item(const std::string & item) const;
    void log_all_items(std::ostream & output) const;
    bool remove_item(const std::string & item);
};

} // namespace aucho

#endif // AUCHO_ACCOUNT_H
