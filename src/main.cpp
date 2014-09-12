#include <iostream>

#include <tftp.h>
#include <udp/client.h>
#include <ui.h>

#include <unistd.h>
#include <netdb.h>

int main(int argc, char** argv)
{

	using tftp::Mode;
	using tftp::protocol;

	char buffer [512];
	udp::client  client;

	udp::session session = client.connect ("glados.cs.rit.edu", "69");

	std::cout << "connecting...\n";
	if (session.ok ()) {

		int len   = 0;
		int bytes = 0;

		len = protocol::pack (buffer, protocol::get ("dcx01", Mode::OCTET));
		std::cout << "sent " << len << " bytes\n";

		if ((bytes = session.send (buffer, len)) == len) {
			std::cout << "send () successful\n";
		}

		if ((bytes = session.recv (buffer, 512)) > 0) {

			//protocol::unpack (buffer);
			tftp::packet::data dta (buffer);

			session.send (buffer,
				protocol::pack (buffer, protocol::ack (dta.index)));
		}
	}

	std::cout << std::endl;
}