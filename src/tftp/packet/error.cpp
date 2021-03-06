#include <tftp/packet/error.h>

namespace tftp {
namespace packet {

error::error ()          : packet (Opcode::OP_ERR) {}
error::error (char* buf) : packet (Opcode::OP_ERR) {
	unpack (buf);
}

uint16_t error::pack (char* buf) const {

	char* it = buf;

	serializer <uint16_t>    (it, this->opcode);
	serializer <uint16_t>    (it, err);
	serializer <std::string> (it, message);

	return (it - buf);
}

bool error::unpack (char* it) {

	deserializer <uint16_t> (it, (uint16_t*)&this->opcode);

	if (opcode != Opcode::OP_ERR)
		return false;

	deserializer <uint16_t>    (it, &err);
	deserializer <std::string> (it, &message);

	return true;
}

}}