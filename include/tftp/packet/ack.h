#ifndef INCLUDE_TFTP_PACKET_ACK_H
#define INCLUDE_TFTP_PACKET_ACK_H

#include "packet.h"

namespace tftp {
namespace packet {


/* Figure 5-3: ACK packet
----------------------
2 bytes		2 bytes
Opcode		Block # */
class ack : public packet {

	public:
		uint16_t index;

		ack ();
		ack (char* buf);

		uint16_t pack (char* buf) const;
		void     unpack (char* it);
};  


}}
#endif