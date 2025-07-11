#pragma once


#define PROTO_MOVE_CONSTRUCTOR_PARADIGM(class_name) \
class_name::class_name(class_name&& other) {\
	this->_move_(other);\
	return;\
}