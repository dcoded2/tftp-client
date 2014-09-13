#include <tftp/packet/data.h>

namespace tftp {
namespace packet {

data::data ()          : packet (Opcode::OP_DTA) {}
data::data (char* buf) : packet (Opcode::OP_DTA) {
	unpack (buf);
}

uint16_t data::pack (char* buf) const {

	char* it = buf;

	serializer <uint16_t>    (it, this->opcode);
	serializer <uint16_t>    (it, index);
	serializer <std::string> (it, text);

	return (it - buf);
}

void data::unpack (char* it) {

	deserializer <uint16_t> (it, (uint16_t*)&this->opcode);

	assert (opcode == Opcode::OP_DTA);

	deserializer <uint16_t>    (it, &index);
	deserializer <std::string> (it, &text);

	last_ = (text.size () < 512);
}

bool data::last () const {
	return last_;
}

}}