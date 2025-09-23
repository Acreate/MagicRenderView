#ifndef STRINGTOFLOAT_H_H_HEAD__FILE__
#define STRINGTOFLOAT_H_H_HEAD__FILE__
#pragma once
#include "../../I_Conver.h"

class StringToFloat : public  I_Conver{
public:
	bool fillTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) override;
};

#endif // STRINGTOFLOAT_H_H_HEAD__FILE__
