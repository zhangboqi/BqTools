#include "BqException.h"

namespace bq {
	BqException::BqException(const int code, const char* message) :code(code), message(message) {
	}
	BqException::~BqException() {}

	const int BqException::GetCode() {
		return this->code;
	}
	const char* BqException::GetMessage() {
		return this->message;
	}

}