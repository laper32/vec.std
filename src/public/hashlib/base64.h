#pragma once
#ifndef _VEC_STD_BASE64_H_
#define _VEC_STD_BASE64_H_

#include <string>

#if __cplusplus >= 201703L
#include <string_view>
#endif  // __cplusplus >= 201703L

namespace vec
{
	namespace hashlib
	{
		namespace base64
		{
			std::string encode(std::string const& s, bool url = false);
			std::string encode_pem(std::string const& s);
			std::string encode_mime(std::string const& s);

			std::string decode(std::string const& s, bool remove_linebreaks = false);
			std::string encode(unsigned char const*, size_t len, bool url = false);

#if __cplusplus >= 201703L
			//
			// Interface with std::string_view rather than const std::string&
			// Requires C++17
			// Provided by Yannic Bonenberger (https://github.com/Yannic)
			//
			std::string encode(std::string_view s, bool url = false);
			std::string encode_pem(std::string_view s);
			std::string encode_mime(std::string_view s);

			std::string decode(std::string_view s, bool remove_linebreaks = false);
#endif  // __cplusplus >= 201703L
		}
	}
}
#endif // !_VEC_STD_BASE64_H_