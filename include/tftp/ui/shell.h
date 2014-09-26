#ifndef INCLUDE_TFTP_UI_SHELL_H
#define INCLUDE_TFTP_UI_SHELL_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <string.h>
#include <iterator>

#include <tftp.h>
#include <udp/client.h>

#include "state.h"
#include "command.h"
#include "transistion_table.h"

namespace tftp {
namespace ui   {



class shell {

	private:
		udp::client client;

		udp::session::pointer session;

	public:
		void start ();
		int get (const char* filename, Mode mode);
		//int put (const char* filename, Mode mode);
};





}
}

#endif