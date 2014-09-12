#include <tftp/packet/ack.h>

namespace tftp {
namespace packet {

ack::ack ()          : packet (Opcode::OP_ACK) {}
ack::ack (char* buf) : packet (Opcode::OP_ACK) {
	unpack (buf);
}

uint16_t ack::pack (char* buf) {

	char* it = buf;

	serializer <uint16_t> (it, this->opcode);
	serializer <uint16_t> (it, index);

	return (it - buf);
}

void ack::unpack (char* it) {

	deserializer <uint16_t> (it, (uint16_t*)&this->opcode);
	deserializer <uint16_t> (it, &index);
}

}}