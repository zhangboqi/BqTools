#pragma once
#ifndef _BQ_BIT_TOOL_H
#define _BQ_BIT_TOOL_H

namespace bq {
	class BqBitTool {
	public:
		/*检查第i个bit位是否为1, i为0-31*/
		static bool CheckBit(unsigned int data,unsigned char i);
		/*数据为清零,start和end为0-31的bit位索引*/
		static void ClearBit(unsigned int* data, unsigned char start,  int end);
		/*数据位置1,start和end为0-31的bit位索引*/
		static void SettingBit(unsigned int* data, unsigned char start, unsigned char end);
	};
}

#endif