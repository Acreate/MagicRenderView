#ifndef NULLTOANY_H_H_HEAD__FILE__
#define NULLTOANY_H_H_HEAD__FILE__
#pragma once
#include "../../I_Conver.h"

class NullToAny : public I_Conver {
public:
	bool equThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) override;
};

#endif // NULLTOANY_H_H_HEAD__FILE__
