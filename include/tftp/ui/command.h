#ifndef INCLUDE_TFTP_UI_COMMAND_H
#define INCLUDE_TFTP_UI_COMMAND_H

#include <map>
#include <cstdint>

#include <tftp/mode.h>
#include "state.h"

namespace tftp {
namespace ui   {

static std::map <std::string, State> command = {
	{"connect", State::CONNECT},
	{"quit"   , State::QUIT   },
	{"?"      , State::HELP   },
	{"get"    , State::GET    },
//	{"put"    , State::PUT    },
	{"mode"   , State::MODE   }
};

static std::map <std::string, Mode> modes = {
	{"octet"   , Mode::OCTET    },
	{"netascii", Mode::NET_ASCII}
};


}
}

#endif