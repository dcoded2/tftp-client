#include <tftp/packet/request.h>

namespace tftp {
namespace packet {

request::request (Opcode op) : packet (op) {}
request::request (char* buf) : packet (Opcode::OP_NUL) {
	unpack (buf);
}

uint16_t request::pack (char* buf) {

	char* it = buf;

	serializer <uint16_t>    (it, this->opcode);
	serializer <std::string> (it, file);
	serializer <std::string> (it, mode);

	return (it - buf);
}

void request::unpack (char* it) {

	deserializer <uint16_t>    (it, (uint16_t*)&this->opcode);
	deserializer <std::string> (it, &file);
	deserializer <std::string> (it, &mode);
}

}}