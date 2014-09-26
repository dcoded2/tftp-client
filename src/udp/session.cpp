#include <udp/session.h>

namespace udp {

session::session (int fd, addrinfo* addr, uint16_t seconds)
: fd_   (fd)
, res_  (addr)
, time_ (seconds) {
	timeout (seconds);
}


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

uint16_t session::timeout () const {
	return time_;
}

bool session::timeout (uint16_t seconds) {
	struct timeval tv;
	tv.tv_sec  = seconds;
	tv.tv_usec = 0;

	return (setsockopt (fd_, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof (tv)) >= 0);
}

}