#include <udp/client.h>

namespace udp {

session client::connect (const char* host, const char* port) {

	int fd = -1;

	addrinfo  hints;
	addrinfo* res;  // will point to the results

	memset (&hints, 0, sizeof hints); // make sure the struct is empty

    hints.ai_family   = AF_INET;     // don't care IPv4 or IPv6
	hints.ai_socktype = SOCK_DGRAM; // TCP stream sockets
	hints.ai_protocol = IPPROTO_UDP;

	// get ready to connect
	if (getaddrinfo (host, port, &hints, &res) == 0) {
		fd = socket (res->ai_family, res->ai_socktype, res->ai_protocol);
	}

	return session (fd, res);
}


}