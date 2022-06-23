#include <stdio.h>
#include "BqBirthday.h"
namespace bq {

	BqBirthday::BqBirthday(unsigned short year,unsigned char month, unsigned char day) {
		unsigned char y = year - 1900;
		this->birthday[0] = (y << 1) + (month >> 3);
		this->birthday[1] = (month << 5) + (day & 0x1F);
	}
	unsigned short BqBirthday::GetYear() {
		return (this->birthday[0] >> 1) + 1900;
	}
	unsigned char BqBirthday::GetMonth() {
		return ((this->birthday[0] & 0x01) << 3) + (this->birthday[1] >> 5);
	}
	unsigned char BqBirthday::GetDay() {
		return this->birthday[1] & 0x1F;
	}

	void BqBirthday::ToString(char* buf) {
		sprintf(buf, "%d-%d-%d", GetYear(), GetMonth(), GetDay());
	}
}