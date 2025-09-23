#ifndef STRINGTOINT_H_H_HEAD__FILE__
#define STRINGTOINT_H_H_HEAD__FILE__
#pragma once
#include "../../I_Conver.h"

class StringToInt : public I_Conver {
public:
	bool fillTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) override;
};

#endif // STRINGTOINT_H_H_HEAD__FILE__
