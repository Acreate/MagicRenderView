#ifndef ISQSTRINGTYPE_H_H_HEAD__FILE__
#define ISQSTRINGTYPE_H_H_HEAD__FILE__
#pragma once
#include "../I_IsType.h"

class IsQStringType : public I_IsType{
	
	using t_current_type = QString;
public:
	IsQStringType( ) : I_IsType( typeid( t_current_type ) ) { }
};

#endif // ISQSTRINGTYPE_H_H_HEAD__FILE__
