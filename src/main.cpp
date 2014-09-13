#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

#include <tftp.h>
#include <udp/client.h>
#include <ui.h>

#include <unistd.h>
#include <netdb.h>

using tftp::Mode;


enum class State : uint8_t {
	NOCMD   = 0x00,
	INIT    = 0x01,
	QUIT    = 0x02,
	PROMPT  = 0x03,
	STDIN   = 0x04,
	PARSE   = 0x05,

	HELP    = 0x10,
	CONNECT = 0x11,
	GET     = 0x12,
	MODE    = 0x13
};

std::map <std::string, State> command = {
	{"connect", State::CONNECT},
	{"quit"   , State::QUIT   },
	{"?"      , State::HELP   },
	{"get"    , State::GET    }
};

std::map <std::string, Mode> modes = {
	{"octet"   , Mode::OCTET    },
	{"netascii", Mode::NET_ASCII}
};

std::map <State, State> next = {
	{State::INIT     , State::PROMPT},
	{State::PROMPT   , State::STDIN },
	{State::STDIN    , State::PARSE },
	{State::NOCMD    , State::PROMPT},

	{State::QUIT     , State::QUIT  },
	{State::CONNECT  , State::PROMPT},
	{State::MODE     , State::PROMPT},
	{State::GET      , State::PROMPT}
};


void get (udp::session& session, const char* filename, Mode mode);

void interactive_prompt (udp::client& client);

int main(int argc, char** argv)
{
	udp::client client;

	interactive_prompt (client);

	// > connect <hostname>
	// udp::session session = client.connect ("glados.cs.rit.edu", "69");

	// get (session, "dcx01", Mode::OCTET);
}

void interactive_prompt (udp::client& client)
{
	udp::session session;
	Mode   mode = Mode::OCTET;


	std::string line;
	std::vector <std::string> args;

	State state;
	while ((state = next[state]) != State::QUIT)
	switch (state)
	{
		case State::PROMPT: std::cout << "tftp> ";
		break;

		case State::STDIN: 		if (std::getline(std::cin, line)) {	
									args.clear ();
									std::istringstream iss(line);
									std::copy(std::istream_iterator<std::string> (iss),
											  std::istream_iterator<std::string> (),
											  std::back_inserter (args));
								}
		break;

		case State::PARSE: 		next[state] = command[ args[0] ];
								//std::transform(args[0].begin(), args[0].end(), args[0].begin(), ::tolower);
		break;

		case State::CONNECT:	std::cout << "connecting to " << args[1] << ":" << args[2] << "\n";
								session = client.connect (args[1].c_str (), "69");
		break;

		case State::MODE:		if (modes.find (args[1]) != modes.end ()) {
									mode = modes[ args[1] ];
									std::cout << "Switching to '" << args[1] << "' mode\n";
								} else {
									std::cout << "Mode '" << args[1] << "' does not exist\n";
								}
		break;

		case State::GET:		if (session.ok ())
									get (session, args[1].c_str (), mode);
								else
									std::cout << "no connection defined\n";
		break;


		case State::NOCMD:		std::cout << "Command '" << args[0] << "' does not exist\n";
		break;

		default: state = State::QUIT;
				 std::cout << "An error has occurred...quitting\n";
	}
}

void get (udp::session& session, const char* filename, Mode mode)
{

	using tftp::protocol;

	assert (session.ok ());
	std::ofstream file (filename);

	char buffer [512];

	int  bytes = 0;
	auto rrq   = protocol::get  (filename, mode);
	int  len   = protocol::pack (buffer, &rrq);

	if    ((bytes = session.send (buffer, len)) == len)
	while ((bytes = session.recv (buffer, sizeof (buffer))) > 0)
	{
		tftp::packet::data dta (buffer);
		tftp::packet::ack  ack = protocol::ack (dta.index);

		session.send (buffer, protocol::pack (buffer, &ack));

		file << dta.text;
		if (dta.last ())
			break;
	}
	file.close ();
}