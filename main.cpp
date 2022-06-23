#include <stdio.h>
#include "BqTools.h"

using namespace bq;

int main() {

	unsigned int a = 0x00;
	BqBitTool::SettingBit(&a, 1, 30);
	
	unsigned int b = 0xFFFFFFFF;
	BqBitTool::ClearBit(&b, 1, 30);
	return 0;
}