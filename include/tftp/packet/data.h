#ifndef INCLUDE_TFTP_PACKET_DATA_H
#define INCLUDE_TFTP_PACKET_DATA_H

#include "packet.h"

namespace tftp {
namespace packet {


/* Figure 5-2: DATA packet
-------------------------------
2 bytes		2 bytes		n bytes
Opcode		Block #		Data */
class data : public packet {
	private:
		bool last_;
	public:
		uint16_t    index;
		std::string text;

		data ();
		data (char* buf);
		//data (char* buf, uint16_t size);

		uint16_t pack   (char* buf) const;
		bool     unpack (char* it);
		bool     last () const;
};   


}}
#endif