#include <udp/session.h>

namespace udp {

session::session (int fd, addrinfo* addr)
: fd_ (fd)
, res_ (addr) {}


session::~session () {
	close (fd_);
	freeaddrinfo (res_);
}

uint16_t session::send (char* buffer, uint16_t len) {

    return sendto (fd_, buffer, len, 0, res_->ai_addr, res_->ai_addrlen);
}

uint16_t session::recv (char* buffer, uint16_t len) {

	return recvfrom (fd_, buffer, len, 0, res_->ai_addr, (socklen_t*) &res_->ai_addrlen);
}

bool session::ok () {
	return (fd_ >= 0);
}

}