
#include "BqBitTool.h"
#include "BqException.h"
namespace bq {

	bool BqBitTool::CheckBit(unsigned int data, unsigned char i) {
		if (i > 31) { throw BqException(10001, "Index Out of Bounds"); }
		return (data & 0x01 << i) > 0;
	}

	void BqBitTool::ClearBit(unsigned int* data, unsigned char start,  int end)
	{	
		// 注意，32位数不支持左移32位，会有问题 
		unsigned int mask = (end >=31 ? 0 : (0xFFFFFFFF << end + 1)) + (start <= 0 ? 0 : 0xFFFFFFFF >> 32 - start);
		*data &= mask;
	}

	void BqBitTool::SettingBit(unsigned int* data, unsigned char start, unsigned char end)
	{
		unsigned char len = end - start + 1;
		int mask = 0x00;
		for (int i = 0; i < len; i++) {
			mask <<= 1;
			mask |= 0x01;
		}
		mask <<= start;
		*data |= mask;
	}

}