#ifndef INCLUDE_TFTP_PACKET_H
#define INCLUDE_TFTP_PACKET_H

#include <stdint.h>
#include <string>

#include <tftp/opcode.h>
#include <tftp/mode.h>
#include <tftp/serializer.h>

namespace tftp {
namespace packet {



class packet {

	protected:
		Opcode opcode;

		packet (Opcode op);

	public:
		virtual uint16_t pack   (char*) = 0;
		virtual void     unpack (char*) = 0;
};


}}
#endif