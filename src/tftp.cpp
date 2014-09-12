#include <tftp.h>

namespace tftp {

packet::request protocol::get (const char* path, Mode transfer_mode) {

	packet::request packet (Opcode::OP_RRQ);
	packet.mode = mode [static_cast<int> (transfer_mode)];
	packet.file = path;

	return packet;
}

packet::request protocol::put (const char* path, Mode transfer_mode) {

	packet::request packet (Opcode::OP_WRQ);
	packet.mode = mode [static_cast<int> (transfer_mode)];
	packet.file = path;

	return packet;
}

packet::ack protocol::ack (uint16_t id) {

	packet::ack packet;
	packet.index = id;

	return packet;
}


packet::error protocol::error (uint16_t error, std::string message) {
	packet::error packet;
	packet.err     = error;
	packet.message = message;

	return packet;
}

};