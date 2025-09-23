#ifndef I_CONVER_H_H_HEAD__FILE__
#define I_CONVER_H_H_HEAD__FILE__
#pragma once

#include "I_Type.h"

#include "../../alias/type_alias.h"

class I_Var;
/// @brief 转换器接口
class I_Conver {
public:
	virtual ~I_Conver( ) = default;
	virtual bool fillTarget( I_Var *left, const I_Var *right ) = 0;
	virtual bool converTarget( const I_Var *target_data ) = 0;
};

#endif // I_CONVER_H_H_HEAD__FILE__
