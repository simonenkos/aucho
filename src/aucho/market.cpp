#include <aucho/market.h>

#include <stdexcept>

namespace aucho
{

market_t::market_t(uint32_t fee) : _fee { fee }
{ }

void market_t::put_item_on_sale(account_t * seller_ptr, const std::string & item, uint32_t price)
{
    if (!seller_ptr->has_item(item))
        throw std::runtime_error("Seller has no such item");

    if (!seller_ptr->remove_from_fund(_fee))
        throw std::runtime_error("Seller has no funds for sell fee");

    if (!_items_on_sale.emplace(item, item_t {price, seller_ptr}).second)
    {
        seller_ptr->add_to_fund(_fee);
        throw std::runtime_error("Item is already on sale");
    }

    seller_ptr->remove_item(item);
}

void market_t::cancel_item_sale(account_t * seller_ptr, const std::string & item)
{
    auto it = _items_on_sale.find(item);

    if ((_items_on_sale.end() != it) && (it->second._seller_account_ptr == seller_ptr))
        seller_ptr->add_item(item);
}

void market_t::buy_item(account_t * buyer_ptr, const std::string & item)
{
    auto it = _items_on_sale.find(item);

    if (_items_on_sale.end() == it)
        throw std::runtime_error("No such item is no sale");

    if (!buyer_ptr->remove_from_fund(it->second._price))
        throw std::runtime_error("Not enough funds to buy item");

    buyer_ptr->add_item(item);
    it->second._seller_account_ptr->add_to_fund(it->second._price);
    _items_on_sale.erase(it);
}

const std::map<std::string, market_t::item_t> & market_t::get_items_on_sale() const
{
    return _items_on_sale;
}

} // namespace aucho
