#ifndef FLOATTOINT_H_H_HEAD__FILE__
#define FLOATTOINT_H_H_HEAD__FILE__
#pragma once
#include "../../I_Conver.h"

class FloatToInt : public I_Conver {
public:
	bool fillTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) override;
	bool addTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) override;
	bool subTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) override;
	bool mulTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) override;
	bool devTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) override;
};

#endif // FLOATTOINT_H_H_HEAD__FILE__
