#include <tftp/ui/shell.h>

namespace tftp {
namespace ui   {

void shell::start ()
{
	std::string mode;

	std::string line;
	std::vector <std::string> args;
	const char* filename = nullptr;

	State state = State::INIT;

	while  (state != State::QUIT)
	switch (state)
	{
		case State::INIT:
			state = next[state];
		break;
		/*********************************************************************/
		case State::PROMPT:

			state = next[state];

			if (client.address () != "")
				std::cout << "tftp " << client.address () << "> ";
			else
				std::cout << "tftp> ";
		break;
		/*********************************************************************/
		case State::STDIN: 	

			state = next[state];
			if (std::getline(std::cin, line)) {	
				args.clear ();
				std::istringstream iss(line);
				std::copy(std::istream_iterator<std::string> (iss),
						  std::istream_iterator<std::string> (),
						  std::back_inserter (args));
			}
		break;
		/*********************************************************************/
		case State::PARSE: 	

			state = (command.find (args[0]) != command.end ())
					? command[args[0]]
					: State::NOCMD;
		break;
		/*********************************************************************/
		case State::CONNECT:

			state = next[state];
			client.connect (args[1].c_str (), "69");
		break;
		/*********************************************************************/
		case State::MODE:

			state = next[state];

			if (modes.find (args[1]) != modes.end ()) {
				mode = args[1];
				std::cout << "Switching to '" << args[1] << "' mode" << std::endl; 
			} else {
				std::cout << "Mode '" << args[1] << "' is invalid" << std::endl; 
			}
						
		break;
		/*********************************************************************/
		case State::GET:	

			state = next[state];

			filename = args[1].c_str ();
			session  = client.session ();

			if (!session->ok ())
				std::cout << "no connection defined" << std::endl;

			else
			{
				int bytes = get (filename, modes[mode]);

				if (bytes < 0) {
					std::cout << "Transfer timed out after "
				              << session->timeout ()
				              << " seconds" << std::endl;
				}
				else
					std::cout << "Received " << bytes << " bytes" << std::endl;
			}
		break;
		/*********************************************************************/
		case State::HELP:

		/*
Commands may be abbreviated.  Commands are:

connect         connect to remote tftp
put             send file
get             receive file
quit            exit tftp
?               print help information
*/

			state = next[state];
			std::cout << "Commands are:"                          << std::endl
					  << "connect         connect to remote tftp" << std::endl
					  << "put             send file **disabled**" << std::endl
					  << "get             receive file"           << std::endl
					  << "quit            exit tftp"              << std::endl
					  << "?               print help information" << std::endl
					  ;
		break;
		/*********************************************************************/
		case State::NOCMD:	

			state = next[state];
			std::cout << "Command '" << args[0] << "' does not exist\n";
		break;
		/*********************************************************************/
		default:	

			state = State::QUIT;
			std::cout << "An error has occurred...quitting\n";
	}
}



int shell::get (const char* filename, Mode mode)
{
	using tftp::protocol;

	char buffer [512 + 64] = {0};

	int  bytes = 0;
	int  size  = 0;

	auto rrq   = protocol::get  (filename, mode);
	int  len   = protocol::pack (buffer  , &rrq);

	tftp::packet::data  data;
	tftp::packet::error error;

	// check via strerror (errno);
	if ((bytes = session->send (buffer, len)) == len) {

		std::ofstream file;

		while ((bytes = session->recv (buffer, sizeof (buffer))) > 0)
		{	
			if (data.unpack (buffer)) {

				if (!file.is_open ())
					 file.open (filename);

				tftp::packet::ack  ack = protocol::ack (data);
				session->send (buffer, protocol::pack (buffer, &ack));

				size += bytes;
				file << data.text;

				if (data.last ())
					break;
			}
			else if (error.unpack (buffer)) {
				std::cout << "Error code " << error.err << ": " << error.message << std::endl;
				break;
			}
		}

		if (!file.is_open ())
			 file.close ();
	}

	if (bytes == -1)
		size = -1;

	return size;
}

}
}