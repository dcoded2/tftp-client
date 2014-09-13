#ifndef INCLUDE_TFTP_PACKET_H
#define INCLUDE_TFTP_PACKET_H

#include <iostream>
#include <stdint.h>
#include <string>
#include <assert.h>

#include <tftp/opcode.h>
#include <tftp/mode.h>
#include <tftp/serializer.h>

namespace tftp {
namespace packet {



class packet {

	public:
		Opcode opcode;

		packet (Opcode op);

	public:
		virtual uint16_t pack   (char*) const = 0;
		virtual void     unpack (char*)       = 0;
};


}}
#endif