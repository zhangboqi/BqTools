#include "BqHex.h"
namespace bq {
	BqHex::BqHex() {
		for (char i = 0; i <= 9; i++) hex_table[i] = '0' + i;
		for (char i = 0; i < 6; i++) hex_table[i + 10] = 'A' + i;
	}
	int BqHex::Encode(const char* data, int dataLength, char* hexStr) {
		char* hexStrPtr = hexStr;
		for (int i = 0; i < dataLength; i++) {
			hexStrPtr[0] = hex_table[data[i] >> 4];
			hexStrPtr[1] = hex_table[data[i] & 0x0F];
			hexStrPtr += 2;
		}
		int len = dataLength * 2;
		hexStr[len] = 0;
		return len;
	}

	int BqHex::Decode(const char* hexStr, int hexStrLength, char* dataBuffer) {
		return 0;
	}

}