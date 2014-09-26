#ifndef INCLUDE_TFTP_MODE_H
#define INCLUDE_TFTP_MODE_H

#include <stdint.h>

namespace tftp {

enum class Mode : uint8_t {
	NET_ASCII = 0x00,
	OCTET     = 0x01,
	MAIL      = 0x02
};

static const char* mode[] = {
	"netascii",
	"octet",
	"mail"
};

}

#endif