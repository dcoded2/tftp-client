#ifndef INCLUDE_TFTP_PACKET_H
#define INCLUDE_TFTP_PACKET_H

#include <stdint.h>
#include <string>

#include "opcode.h"
#include "mode.h"
#include "serializer.h"

namespace tftp {
namespace packet {



class packet {

	protected:
		Opcode opcode;

		packet (Opcode op)  : opcode (op) {}

	public:
		virtual uint16_t pack   (char*) = 0;
		virtual void     unpack (char*) = 0;
};

/* Figure 5-1: RRQ/WRQ packet
----------------------------------------------
2 bytes		string		1 byte	string	1 byte
Opcode		Filename	0		Mode	0 */
class request : public packet {

	public:
		std::string file;
		std::string mode;

		request (Opcode op) : packet (op) {}
		request (char* buf) : packet (Opcode::OP_NUL) {
			unpack (buf);
		}

		uint16_t pack (char* buf) {

			char* it = buf;

			serializer <uint16_t>    (it, this->opcode);
			serializer <std::string> (it, file);
			serializer <std::string> (it, mode);

			return (it - buf);
		}

		void unpack (char* it) {

			deserializer <uint16_t>    (it, (uint16_t*)&this->opcode);
			deserializer <std::string> (it, &file);
			deserializer <std::string> (it, &mode);
		}
};

/* Figure 5-2: DATA packet
-------------------------------
2 bytes		2 bytes		n bytes
Opcode		Block #		Data */
class data : public packet {

	public:
		uint16_t    index;
		std::string text;

		data ()          : packet (Opcode::OP_DTA) {}
		data (char* buf) : packet (Opcode::OP_DTA) {
			unpack (buf);
		}

		uint16_t pack (char* buf) {

			char* it = buf;

			serializer <uint16_t>    (it, this->opcode);
			serializer <uint16_t>    (it, index);
			serializer <std::string> (it, text);

			return (it- buf);
		}

		void unpack (char* it) {

			deserializer <uint16_t>    (it, (uint16_t*)&this->opcode);
			deserializer <uint16_t>    (it, &index);
			deserializer <std::string> (it, &text);
		}
};   

/* Figure 5-3: ACK packet
----------------------
2 bytes		2 bytes
Opcode		Block # */
class ack : public packet {

	public:
		uint16_t index;

		ack ()          : packet (Opcode::OP_ACK) {}
		ack (char* buf) : packet (Opcode::OP_ACK) {
			unpack (buf);
		}

		uint16_t pack (char* buf) {

			char* it = buf;

			serializer <uint16_t> (it, this->opcode);
			serializer <uint16_t> (it, index);

			return (it - buf);
		}

		void unpack (char* it) {

			deserializer <uint16_t> (it, (uint16_t*)&this->opcode);
			deserializer <uint16_t> (it, &index);
		}
};  

/* Figure 5-4: ERROR packet
------------------------------------------
2 bytes		2 bytes		string		1 byte
Opcode		ErrorCode	ErrMsg		0 */
class error : public packet {

	public:
		uint16_t    err;
		std::string message;

		error ()          : packet (Opcode::OP_ERR) {}
		error (char* buf) : packet (Opcode::OP_ERR) {
			unpack (buf);
		}

		uint16_t pack (char* buf) {

			char* it = buf;

			serializer <uint16_t>    (it, this->opcode);
			serializer <uint16_t>    (it, err);
			serializer <std::string> (it, message);

			return (it - buf);
		}

		void unpack (char* it) {

			deserializer <uint16_t>    (it, (uint16_t*)&this->opcode);
			deserializer <uint16_t>    (it, &err);
			deserializer <std::string> (it, &message);
		}
};


};
};
#endif