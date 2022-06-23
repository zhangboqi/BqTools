#pragma once
#ifndef _BQ_HEX_H
#define _BQ_HEX_H

namespace bq {
	class BqHex {
	public:
		BqHex();
	public:
		int Encode(const char* data,int dataLength, char* hexStr);

		int Decode(const char* hexStr, int hexStrLength, char* dataBuffer);

	private :
		char hex_table[16];
	};
}

#endif