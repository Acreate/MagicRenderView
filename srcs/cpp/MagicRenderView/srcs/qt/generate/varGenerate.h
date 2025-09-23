#ifndef VARGENERATE_H_H_HEAD__FILE__
#define VARGENERATE_H_H_HEAD__FILE__
#pragma once
#include "../../alias/type_alias.h"

class BaseVarType;
class I_Type;
class I_Conver;
class VarGenerate {

protected:
	/// @brief 转换列表
	static std_vector< std_shared_ptr< I_Conver > > converVector;
public:
	static void append( const std_shared_ptr< I_Conver > &new_conver );
	static bool conver( BaseVarType *left, const BaseVarType *right );
	static bool conver( BaseVarType *left, const I_Type *right_type_info, const void *right );
	static bool conver( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right );
};

#endif // VARGENERATE_H_H_HEAD__FILE__
