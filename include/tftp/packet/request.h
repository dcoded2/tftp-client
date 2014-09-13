#ifndef INCLUDE_TFTP_PACKET_REQUEST_H
#define INCLUDE_TFTP_PACKET_REQUEST_H

#include "packet.h"

namespace tftp {
namespace packet {


/* Figure 5-1: RRQ/WRQ packet
----------------------------------------------
2 bytes		string		1 byte	string	1 byte
Opcode		Filename	0		Mode	0 */
class request : public packet {

	public:
		std::string file;
		std::string mode;

		request (Opcode op);
		request (char* buf);

		uint16_t pack (char* buf) const;
		void     unpack (char* it);
};


}}
#endif