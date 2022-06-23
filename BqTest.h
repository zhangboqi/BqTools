#pragma once
#include "BqTools.h"
namespace bq {
	void TestBase64() {
		BqBase64 base64;
		const char* data = "wojintianchifanlema";
		char* base64Buffer = (char*)malloc(2048);
		int len = base64.Encode(data, strlen(data), base64Buffer);
		printf("Base64Str: %s\n", base64Buffer);


		char* dataBuf = (char*)malloc(2048);
		base64.Decode(base64Buffer, len, dataBuf);
		printf("DataStr: %s\n", dataBuf);

		free(base64Buffer);
		free(dataBuf);
	}

	void TestHex() {
		BqHex hex;
		const char* data = "wojintianchifanlema";
		char hexStr[1024];
		hex.Encode(data, strlen(data), hexStr);
		printf("HexStr: %s\n",hexStr);
	}
}