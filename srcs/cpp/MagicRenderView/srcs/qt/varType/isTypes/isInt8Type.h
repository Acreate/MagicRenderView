#ifndef ISINT8TYPE_H_H_HEAD__FILE__
#define ISINT8TYPE_H_H_HEAD__FILE__
#pragma once
#include "../I_IsType.h"

class IsInt8Type : public I_IsType{
	
	using t_current_type = int8_t;
public:
	IsInt8Type( ) : I_IsType( typeid( t_current_type ) ) { }
};

#endif // ISINT8TYPE_H_H_HEAD__FILE__
