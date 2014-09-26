#include <udp/client.h>

namespace udp {

void client::connect (const char* host, const char* port) {

	host_ = host;
	port_ = port;
}

std::string client::address () const {
	return host_;
}

session::pointer client::session () {

	int fd = -1;

	addrinfo  hints;
	addrinfo* res;  // will point to the results

	memset (&hints, 0, sizeof hints); // make sure the struct is empty

    hints.ai_family   = AF_INET;     // don't care IPv4 or IPv6
	hints.ai_socktype = SOCK_DGRAM; // TCP stream sockets
	hints.ai_protocol = IPPROTO_UDP;

	// get ready to connect
	if (getaddrinfo (host_.c_str (), port_.c_str (), &hints, &res) == 0) {
		fd = socket (res->ai_family, res->ai_socktype, res->ai_protocol);
	}

	return udp::session::pointer (new udp::session (fd, res));
}

}