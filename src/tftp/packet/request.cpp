#include <tftp/packet/request.h>

namespace tftp {
namespace packet {

request::request (Opcode op) : packet (op) {}
request::request (char* buf) : packet (Opcode::OP_NUL) {
	unpack (buf);
}

uint16_t request::pack (char* buf) const {

	char* it = buf;

	serializer <uint16_t>    (it, this->opcode);
	serializer <std::string> (it, file);
	serializer <std::string> (it, mode);

	return (it - buf);
}

bool request::unpack (char* it) {

	deserializer <uint16_t> (it, (uint16_t*)&this->opcode);

	if (opcode != Opcode::OP_WRQ && opcode != Opcode::OP_RRQ)
		return false;

	deserializer <std::string> (it, &file);
	deserializer <std::string> (it, &mode);

	return true;
}

}}