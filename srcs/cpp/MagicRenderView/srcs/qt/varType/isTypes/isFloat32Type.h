#ifndef ISFLOAT32TYPE_H_H_HEAD__FILE__
#define ISFLOAT32TYPE_H_H_HEAD__FILE__
#pragma once
#include "../I_IsType.h"

class IsFloat32Type : public I_IsType {

	using t_current_type = float_t;
public:
	IsFloat32Type( );
};

#endif // ISFLOAT32TYPE_H_H_HEAD__FILE__
