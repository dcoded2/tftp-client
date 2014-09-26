#ifndef INCLUDE_TFTP_PACKET_ERROR_H
#define INCLUDE_TFTP_PACKET_ERROR_H

#include "packet.h"

namespace tftp {
namespace packet {


/* Figure 5-4: ERROR packet
------------------------------------------
2 bytes		2 bytes		string		1 byte
Opcode		ErrorCode	ErrMsg		0 */
class error : public packet {

	public:
		uint16_t    err;
		std::string message;

		error ();
		error (char* buf);

		uint16_t pack (char* buf) const;
		bool     unpack (char* it);
};


}}
#endif