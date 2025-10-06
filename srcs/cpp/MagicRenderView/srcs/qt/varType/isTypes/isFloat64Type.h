#ifndef ISFLOAT64TYPE_H_H_HEAD__FILE__
#define ISFLOAT64TYPE_H_H_HEAD__FILE__
#pragma once
#include "../I_IsType.h"

class IsFloat64Type : public I_IsType {
	
	using t_current_type = double_t;
public:
	IsFloat64Type( ) : I_IsType( typeid( t_current_type ) ) { }
};

#endif // ISFLOAT64TYPE_H_H_HEAD__FILE__
