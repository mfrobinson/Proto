#pragma once


#define PROTO_COPY_CONSTRUCTOR_PARADIGM(class_name) \
class_name::class_name(const class_name& other) {\
	this->_copy_(other);\
	return;\
}