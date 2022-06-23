#pragma once
#ifndef _BQ_BIRTHDAY_H
#define _BQ_BIRTHDAY_H
/*定义表示生日的简单工具类，可表示的日期范围为1900-2027年
定义规范：
	使用2个字节即16位来表示一个生日日期。
	使用第0-6bit表示年，000 0000 - 111 1111，即0-127，基数是基于1900年，所以要加上1900  
	使用第7-10bit表示月，0000 - 1111，即0-15
	使用第11-15表示日，0 0000 - 1 1111，即0-31
*/
namespace bq {
	class BqBirthday {
	public:
		/*year年，month月，day日*/
		BqBirthday(unsigned short year,unsigned char month,unsigned char day);
	public:
		unsigned short GetYear();
		unsigned char GetMonth();
		unsigned char GetDay();
		void ToString(char* buf);

	private:
		unsigned char birthday[2];
	};


}
#endif