#ifndef ISUINT64TYPE_H_H_HEAD__FILE__
#define ISUINT64TYPE_H_H_HEAD__FILE__
#pragma once
#include "../I_IsType.h"

class IsUint64Type : public I_IsType {
	using t_current_type = uint64_t;
public:
	IsUint64Type( ) : I_IsType( typeid( t_current_type ) ) { }
};

#endif // ISUINT64TYPE_H_H_HEAD__FILE__
