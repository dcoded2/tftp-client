#ifndef INCLUDE_TFTP_H
#define INCLUDE_TFTP_H

#include <sys/socket.h>
#include <assert.h>
#include <string>
#include <iostream>
#include <memory.h>

#include <tftp/opcode.h>
#include <tftp/mode.h>
#include <tftp/packet.h>

namespace tftp {

class protocol {

	public:
		static packet::request get   (const char* path, Mode mode = Mode::OCTET);
		static packet::request put   (const char* path, Mode mode = Mode::OCTET);
		static packet::ack     ack   (uint16_t id);
		static packet::error   error (uint16_t error, std::string message);


		template <class T>
		static uint16_t pack (char* buf, T packet) {
			return packet.pack (buf);
		}

		static packet::packet* unpack (char* data) {

			packet::packet* pk = nullptr;

			switch (ntohs ((uint16_t)*data))
			{
				case OP_RRQ: pk = new packet::request (OP_RRQ); break;
				case OP_WRQ: pk = new packet::request (OP_WRQ); break;
				case OP_DTA: pk = new packet::data    ();       break;
				case OP_ACK: pk = new packet::ack     ();       break;
				case OP_ERR: pk = new packet::error   ();       break;
			}

			pk->unpack (data);

			return pk;
		}
};



};
#endif