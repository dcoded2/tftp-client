#ifndef INCLUDE_UDP_SESSION_H
#define INCLUDE_UDP_SESSION_H

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <string>

namespace udp {

class session {

	public:
		session (int fd, addrinfo* addr);
		~session ();

		uint16_t send (char* buffer, uint16_t len);
		uint16_t recv (char* buffer, uint16_t len);

		bool ok ();

	private:
		int  fd_;
		addrinfo* res_;
};

}

#endif