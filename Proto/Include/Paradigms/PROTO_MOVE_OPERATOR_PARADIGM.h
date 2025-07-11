#pragma once


#define PROTO_MOVE_OPERATOR_PARADIGM(class_name) \
class_name& class_name::operator=(class_name&& other) {\
	if (&other != this) {\
		this->_cleanup_();\
		this->_move_(other);\
	}\
	return *this;\
}