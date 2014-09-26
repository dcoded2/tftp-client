#ifndef INCLUDE_TFTP_UI_STATE_H
#define INCLUDE_TFTP_UI_STATE_H

#include <cstdint>

namespace tftp {
namespace ui   {

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
	PUT     = 0x13,
	MODE    = 0x14
};

}
}

#endif