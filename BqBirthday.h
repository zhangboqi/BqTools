#pragma once
#ifndef _BQ_BIRTHDAY_H
#define _BQ_BIRTHDAY_H
/*�����ʾ���յļ򵥹����࣬�ɱ�ʾ�����ڷ�ΧΪ1900-2027��
����淶��
	ʹ��2���ֽڼ�16λ����ʾһ���������ڡ�
	ʹ�õ�0-6bit��ʾ�꣬000 0000 - 111 1111����0-127�������ǻ���1900�꣬����Ҫ����1900  
	ʹ�õ�7-10bit��ʾ�£�0000 - 1111����0-15
	ʹ�õ�11-15��ʾ�գ�0 0000 - 1 1111����0-31
*/
namespace bq {
	class BqBirthday {
	public:
		/*year�꣬month�£�day��*/
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