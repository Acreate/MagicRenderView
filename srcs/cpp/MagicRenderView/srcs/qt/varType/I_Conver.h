#ifndef I_CONVER_H_H_HEAD__FILE__
#define I_CONVER_H_H_HEAD__FILE__
#pragma once

class BaseVarType;
class I_Type;
/// @brief 转换器接口
class I_Conver {
public:
	virtual ~I_Conver( ) = default;
	virtual bool fillTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) = 0;
};

#endif // I_CONVER_H_H_HEAD__FILE__
