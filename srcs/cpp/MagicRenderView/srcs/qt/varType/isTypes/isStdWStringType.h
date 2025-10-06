#ifndef ISSTDWSTRINGTYPE_H_H_HEAD__FILE__
#define ISSTDWSTRINGTYPE_H_H_HEAD__FILE__
#pragma once
#include "../I_IsType.h"

class IsStdWStringType : public I_IsType{
	
	using t_current_type = std::wstring;
public:
	IsStdWStringType( ) : I_IsType( typeid( t_current_type ) ) { }
};

#endif // ISSTDWSTRINGTYPE_H_H_HEAD__FILE__
