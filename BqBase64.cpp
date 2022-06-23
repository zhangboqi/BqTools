#include "BqBase64.h"

namespace bq {
	BqBase64::BqBase64() {
		// ��ʼ��Base64���ұ�
		for (int i = 0; i < 26; i++) base64_table[i] = 'A' + i;
		for (int i = 0; i < 26; i++) base64_table[i + 26] = 'a' + i;
		for (int i = 0; i < 10; i++) base64_table[i + 52] = '0' + i;
		base64_table[62] = '+';
		base64_table[63] = '/';

		// ��ʼ��Base64������ұ�
		for (int i = 'A'; i < 'Z'; i++) reverse_table[i] = i - 'A';
		for (int i = 'a'; i < 'z'; i++) reverse_table[i] = i - 'a' + 26;
		for (int i = '0'; i < '9'; i++) reverse_table[i] = i - '0' + 52;
		reverse_table['+'] = 62;
		reverse_table['/'] = 63;
		reverse_table['='] = 0;

	}

	void BqBase64::Encode(const char* data, char* base64Str) {
		// data[0]�ĸ�6λ
		base64Str[0] = base64_table[ data[0] >> 2 ];
		// data[0]�ĵ�2λ��data[1]�ĸ�4λ
		base64Str[1] = base64_table[ ((data[0] & 0x03) << 4) + (data[1] >> 4) ];
		// data[1]�ĵ�4λ��data[2]�ĸ�2λ
		base64Str[2] = base64_table[ (data[1] & 0x0F << 2) + (data[2] >> 6) ];
		// data[2]�ĵ�6λ
		base64Str[3] = base64_table[ data[2] & 0x3F ];
	}

	void BqBase64::Decode(const char* base64Str, char* data) {
		unsigned char p0, p1, p2, p3;
		p0 = reverse_table[ base64Str[0] ];
		p1 = reverse_table[ base64Str[1] ];
		p2 = reverse_table[ base64Str[2] ];
		p3 = reverse_table[ base64Str[3] ];
		// p0(bit0-5)  p1(bit4-5)
		data[0] = (p0 << 2) + (p1 >> 4);
		// p1(bit0-3)  p2(bit2-5)
		data[1] = (p1 << 4) + (p2 >> 2);
		// p2(bit0-1)  p3(bit0-5)
		data[2] = (p2 << 6) + p3;
	}

	void BqBase64::Encode(const char* data, int dataSize, char* base64Str) {
		// ��3���ַ�����
		int groups = dataSize / 3;
		int remain = dataSize % 3;  // ����֮��ʣ����ַ�������Ҫ�չ�3���ַ�

		const char* dataPtr = data;
		char* strPtr = base64Str; 
		
		for (int i = 0; i < groups; i++) {
			// 3�ֽ�->4�ֽ�
			Encode(dataPtr, strPtr);
			dataPtr += 3;
			strPtr += 4;
		}

		// ʣ��2���ַ�����1���ַ�
		if (remain == 2) {
			const char t[3] = {dataPtr[0], dataPtr[1], 0};
			Encode(t, strPtr);
			groups += 1;
			strPtr[3] = '='; // ��һ���Ⱥ�
		}

		// ʣ��1���ַ�����2���ַ�
		if (remain == 1) {

		}
		
	}

	void BqBase64::Decode(const char* base64Str, int strSize, char* data) {

	}

}