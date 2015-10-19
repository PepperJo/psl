#ifndef NET_H
#define NET_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <system_error>
#include <istream>

namespace psl {
namespace net {

using ::in_addr;
using ::in_port_t;
using ::sockaddr_in;
}
}

/* ADL only works in org namespace of type -> global */
template <typename CharT, typename Traits>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& in, psl::net::in_addr& ip) {
    std::string str;
    in >> str;
    int ret = inet_aton(str.c_str(), &ip);
    if (!ret) {
        in.setstate(std::ios_base::failbit);
    }
    return in;
}

template <typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& out,
           const psl::net::in_addr& ip) {
    const uint8_t* ip_raw = reinterpret_cast<const uint8_t*>(&ip.s_addr);
    out << static_cast<uint32_t>(ip_raw[0]) << '.'
        << static_cast<uint32_t>(ip_raw[1]) << '.'
        << static_cast<uint32_t>(ip_raw[2]) << '.'
        << static_cast<uint32_t>(ip_raw[3]);
    return out;
}
#endif /* NET_H */
