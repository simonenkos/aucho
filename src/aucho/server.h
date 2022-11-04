#ifndef AUCHO_SERVER_H
#define AUCHO_SERVER_H

#include <boost/asio.hpp>

namespace aucho {

class server {

    server();

    boost::asio::awaitable<void> run();

};

} // namespace aucho

#endif // AUCHO_SERVER_H
