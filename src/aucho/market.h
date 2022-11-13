#ifndef AUCHO_MARKET_H
#define AUCHO_MARKET_H

#include <map>
#include <string>

#include <aucho/account.h>

namespace aucho
{

struct market_t
{
    struct item_t
    {
        uint32_t    _price {};
        account_t * _seller_account_ptr { nullptr };
    };

private:
    std::map<std::string, item_t> _items_on_sale {};
    uint32_t _fee {};

public:
    explicit market_t(uint32_t fee);

    market_t(const market_t &) = delete;
    market_t(market_t &&) noexcept = delete;

    market_t & operator=(const market_t &) = delete;
    market_t & operator=(market_t &&) noexcept = delete;

    ~market_t() = default;

    void put_item_on_sale(account_t * seller_ptr, const std::string & item, uint32_t price);
    void cancel_item_sale(account_t * seller_ptr, const std::string & item);
    void buy_item(account_t * buyer_ptr, const std::string & item);

    [[nodiscard]] const std::map<std::string, item_t> & get_items_on_sale() const;
};

} // namespace aucho

#endif // AUCHO_MARKET_H
