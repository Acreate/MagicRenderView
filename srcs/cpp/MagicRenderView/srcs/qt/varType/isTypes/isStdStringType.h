#ifndef ISSTDSTRINGTYPE_H_H_HEAD__FILE__
#define ISSTDSTRINGTYPE_H_H_HEAD__FILE__
#pragma once
#include "../I_IsType.h"

class IsStdStringType : public I_IsType{
	
	using t_current_type = std::string;
public:
	IsStdStringType( );
};

#endif // ISSTDSTRINGTYPE_H_H_HEAD__FILE__
