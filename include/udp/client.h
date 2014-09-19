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
	public:
		session::pointer connect (const char* host, const char* port);
};

};


#endif