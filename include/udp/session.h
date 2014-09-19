#ifndef INCLUDE_UDP_SESSION_H
#define INCLUDE_UDP_SESSION_H

#include <errno.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <memory>
#include <string>

namespace udp {

class session {

	public:
		typedef std::shared_ptr<session> pointer;

		session (int fd = -1, addrinfo* addr = nullptr);
		~session ();

		session& operator= (const session& rhs);

		int send (char* buffer, uint16_t len);
		int recv  (char* buffer, uint16_t len);

		bool ok ();

	private:
		int       fd_  = -1;
		addrinfo* res_ = nullptr;
};

}

#endif