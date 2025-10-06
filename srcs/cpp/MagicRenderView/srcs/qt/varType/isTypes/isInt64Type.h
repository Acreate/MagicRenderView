#ifndef ISINT64TYPE_H_H_HEAD__FILE__
#define ISINT64TYPE_H_H_HEAD__FILE__
#pragma once
#include "../I_IsType.h"

class IsInt64Type : public I_IsType{
	
	using t_current_type = int64_t;
public:
	IsInt64Type( ) : I_IsType( typeid( t_current_type ) ) { }
};

#endif // ISINT64TYPE_H_H_HEAD__FILE__
