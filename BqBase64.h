#pragma once
#ifndef _BQ_BASE64_H
#define _BQ_BASE64_H
namespace bq {
	class BqBase64 {
	public :
		BqBase64();
	private :
		char base64_table[64]; // 64���Ʋ�ѯ��
		char reverse_table[128]; // 64���Ʒ����ѯ���ο���C/C++ѧϰָ�ϡ�����ƪ����̬����ҷ���

	public:
		/*3�ֽ�->4�ַ�*/
		void Encode(const char* data, char* base64Str);
		/*4�ַ�->3�ֽ�*/
		void Decode(const char* base64Str, char* data);
		/*����*/
		int Encode(const char* data, int dataSize, char* base64Str);
		/*����*/
		int Decode(const char* base64Str, int strSize, char* data);
	};
}
#endif