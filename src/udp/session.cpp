#include <udp/session.h>

namespace udp {

session::session (int fd, addrinfo* addr)
: fd_ (fd)
, res_ (addr) {}


session::~session () {
	if (fd_ >= 0)
		close (fd_);

	if (res_ != nullptr)
		freeaddrinfo (res_);
}

session & session::operator= (const session& rhs)
{
    if (this != &rhs)
    {
    	fd_  = rhs.fd_;
    	res_ = rhs.res_;
    }

    return *this;
}

int session::send (char* buffer, uint16_t len) {

	assert (fd_ >= 0 && res_ != nullptr);
    return sendto (fd_, buffer, len, 0, res_->ai_addr, res_->ai_addrlen);
}

int session::recv (char* buffer, uint16_t len) {

	assert (fd_ >= 0 && res_ != nullptr);
	memset (buffer, 0, len);
	return recvfrom (fd_, buffer, len, 0, res_->ai_addr, (socklen_t*) &res_->ai_addrlen);
}

bool session::ok () {
	return (fd_ >= 0);
}

}