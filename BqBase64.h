#pragma once
#ifndef _BQ_BASE64_H
#define _BQ_BASE64_H
namespace bq {
	class BqBase64 {
	public :
		BqBase64();
	private :
		char base64_table[64]; // 64进制查询表
		char reverse_table[128]; // 64进制反向查询表，参考《C/C++学习指南》补充篇“静态表查找法”

	public:
		/*3字节->4字符*/
		void Encode(const char* data, char* base64Str);
		/*4字符->3字节*/
		void Decode(const char* base64Str, char* data);
		/*编码*/
		int Encode(const char* data, int dataSize, char* base64Str);
		/*解码*/
		int Decode(const char* base64Str, int strSize, char* data);
	};
}
#endif