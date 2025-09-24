#ifndef I_CONVER_H_H_HEAD__FILE__
#define I_CONVER_H_H_HEAD__FILE__
#pragma once

class BaseVarType;
class I_Type;
/// @brief 转换器接口
class I_Conver {
public:
	virtual ~I_Conver( ) = default;
	/// @brief 右值赋值于左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @return 成功赋值返回 true
	virtual bool fillTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) = 0;
	/// @brief 右值赋予于右值加上左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @return 成功加上返回 true
	virtual bool addTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) = 0;
	/// @brief 右值赋值于右值减去左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @return 成功赋值返回 true
	virtual bool subTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) = 0;
	/// @brief 右值赋值于右值乘以左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @return 成功赋值返回 true
	virtual bool mulTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) = 0;
	/// @brief 右值赋值于右值除以左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @return 成功赋值返回 true
	virtual bool devTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) = 0;
	/// @brief 右值是否等于左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @param result_bool 返回结果
	/// @return 成功比较返回 true
	virtual bool equThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) = 0;
	/// @brief 右值是否大于左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @param result_bool 返回结果
	/// @return 成功比较返回 true
	virtual bool greaterThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) = 0;
	/// @brief 右值是否小于左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @param result_bool 返回结果
	/// @return 成功比较返回 true
	virtual bool lessThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) = 0;
	/// @brief 右值是否大于等于左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @param result_bool 返回结果
	/// @return 成功比较返回 true
	virtual bool greaterOrEquThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) = 0;
	/// @brief 右值是否小于于等于左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @param result_bool 返回结果
	/// @return 成功比较返回 true
	virtual bool lessOrEquThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) = 0;

};
#define ChackNeedType( left_type_, left_var_name_, right_type_,  right_var_name_ ) \
	if( left_type_info->getTypeInfo( ) != typeid( left_type_ ) ) \
		return false;\
	if( right_type_info->getTypeInfo( ) != typeid( right_type_ ) )  \
		return false;\
	left_type_ *left_var_name_ = (left_type_*)left;\
	const right_type_ *right_var_name_ = (const right_type_*)right

#endif // I_CONVER_H_H_HEAD__FILE__
