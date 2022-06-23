#pragma once
#include <string>
#ifndef _BQ_EXCEPTION_H
#define _BQ_EXCEPTION_H
namespace bq{
	class BqException {
	public :
		BqException(const int code, const char* message);

		virtual ~BqException();

	public:
		const char* GetMessage();
		const int GetCode();

	private :
		const int code;
		const char* message;
	};

}
#endif