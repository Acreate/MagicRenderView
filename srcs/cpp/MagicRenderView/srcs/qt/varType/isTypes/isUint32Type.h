#ifndef ISUINT32TYPE_H_H_HEAD__FILE__
#define ISUINT32TYPE_H_H_HEAD__FILE__
#pragma once
#include "../I_IsType.h"

class IsUint32Type : public I_IsType{
	
	using t_current_type = uint32_t;
public:
	IsUint32Type( ) : I_IsType( typeid( t_current_type ) ) { }
};

#endif // ISUINT32TYPE_H_H_HEAD__FILE__
