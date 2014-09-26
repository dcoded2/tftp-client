#ifndef INCLUDE_UDP_CLIENT_H
#define INCLUDE_UDP_CLIENT_H

#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>



#include <string.h>

#include "session.h"

namespace udp {

class client {

	private:
		std::string host_;
		std::string port_;

	public:
		void connect (const char* host, const char* port);
		session::pointer session ();

		std::string address () const;
};

};


#endif