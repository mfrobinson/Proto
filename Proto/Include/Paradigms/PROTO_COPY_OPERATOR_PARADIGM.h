#pragma once


#define PROTO_COPY_OPERATOR_PARADIGM(class_name) \
class_name& class_name::operator=(const class_name& other) {\
	if (&other != this) {\
		this->_cleanup_();\
		this->_copy_(other);\
	}\
	return *this;\
}