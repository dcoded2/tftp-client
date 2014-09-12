#ifndef INCLUDE_TFTP_OPCODE_H
#define INCLUDE_TFTP_OPCODE_H

#include <stdint.h>

namespace tftp {

enum Opcode : uint16_t {
	OP_RRQ = 0x01,
	OP_WRQ = 0x02,
	OP_DTA = 0x03,
	OP_ACK = 0x04,
	OP_ERR = 0x05,
	OP_NUL = 0xFF
};

}

#endif