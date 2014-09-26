#ifndef INCLUDE_TFTP_SERIALIZER_H
#define INCLUDE_TFTP_SERIALIZER_H

#include <stdint.h>
#include <arpa/inet.h>
#include <memory.h>
#include <string>

namespace tftp {
namespace packet {

template <typename T> struct serializer {

	serializer (char*& buf, T data, int size = sizeof (T)) {
		memcpy (buf, &data, size);
		buf += size;
	}
};

template <> struct serializer <uint16_t> {
	
	serializer (char*& buf, uint16_t data) {
		int size = 0;

		size = sizeof (uint16_t);
		data = htons (data);

		memcpy (buf, &data, size);
		buf += size;
	}
};

template <> struct serializer <std::string> {

	serializer (char*& buf, std::string data) {
		int size = data.size () + 1;

		memcpy (buf, data.c_str (), size);
		buf += size; 
	}
};


template <typename T> struct deserializer {

	deserializer (char*& src, T* dst, int size = sizeof (T)) {
		memcpy (dst, &src, size);
		src += size;
	}
};

template <> struct deserializer <uint16_t> {
	
	deserializer (char*& src, uint16_t* dst) {
		*dst = ntohs (*(uint16_t*)src);
		src += sizeof (uint16_t);
	}
};

template <> struct deserializer <std::string> {

	deserializer (char*& src, std::string* dst) {
		dst->clear ();
		dst->append (src);
		src += dst->size () + 1; 
	}
};


}
}

#endif 