#pragma once
#ifndef _VEC_STD_CRC32_H_
#define _VEC_STD_CRC32_H_

#include <string>
#include <sstream>

namespace vec
{
	namespace hashlib
	{
		namespace crc32
		{
			uint32_t update(unsigned char ch, uint32_t crc);
			bool file(char* name, uint32_t* crc, long* charcnt);
			uint32_t buf(char* buf, size_t len);
			void toHex(uint32_t crc, char* buf, size_t len);
		}
	}
}

#endif // !_VEC_STD_CRC32_H_