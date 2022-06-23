#pragma once
#ifndef _BQ_BIT_TOOL_H
#define _BQ_BIT_TOOL_H

namespace bq {
	class BqBitTool {
	public:
		/*����i��bitλ�Ƿ�Ϊ1, iΪ0-31*/
		static bool CheckBit(unsigned int data,unsigned char i);
		/*����Ϊ����,start��endΪ0-31��bitλ����*/
		static void ClearBit(unsigned int* data, unsigned char start,  int end);
		/*����λ��1,start��endΪ0-31��bitλ����*/
		static void SettingBit(unsigned int* data, unsigned char start, unsigned char end);
	};
}

#endif