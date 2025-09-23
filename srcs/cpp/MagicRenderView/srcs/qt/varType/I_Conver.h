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
#define ChackNeedType( left_type_, left_var_name_, right_type_,  right_var_name_ ) \
	if( left_type_info->getTypeInfo( ) != typeid( left_type_ ) ) \
		return false;\
	if( right_type_info->getTypeInfo( ) != typeid( right_type_ ) )  \
		return false;\
	left_type_ *left_var_name_ = (left_type_*)left;\
	const right_type_ *right_var_name_ = (const right_type_*)right

#endif // I_CONVER_H_H_HEAD__FILE__
