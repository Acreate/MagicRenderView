#ifndef I_ISTYPE_H_H_HEAD__FILE__
#define I_ISTYPE_H_H_HEAD__FILE__
#pragma once
#include <QString>

/// @brief 类型识别器
class I_IsType {
public:
	/// @brief 目标为整数
	/// @param check_type_info 类型识别
	/// @param check_type_data_ptr 识别对象指针
	/// @return true 表示整形
	virtual bool isInt( const type_info &check_type_info, void *check_type_data_ptr ) const = 0;
	/// @brief 目标为无符号整数
	/// @param check_type_info 类型识别
	/// @param check_type_data_ptr 识别对象指针
	/// @return true 表示整数
	virtual bool isUInt( const type_info &check_type_info, void *check_type_data_ptr ) const = 0;
	/// @brief 目标为浮点数
	/// @param check_type_info 类型识别
	/// @param check_type_data_ptr 识别对象指针
	/// @return true 表示浮点
	virtual bool isFloat( const type_info &check_type_info, void *check_type_data_ptr ) const = 0;
	/// @brief 目标为字符串
	/// @param check_type_info 类型识别
	/// @param check_type_data_ptr 识别对象指针
	/// @return true 表示浮点
	virtual bool isString( const type_info &check_type_info, void *check_type_data_ptr ) const = 0;
	/// @brief 获取类型的字符串形式
	/// @param check_type_info 检查的类型
	/// @param check_type_data_ptr 识别对象指针
	/// @param result_type_string_name 返回的字符串名称 
	/// @return true 表示正确识别
	virtual bool getTypeName( const type_info &check_type_info, void *check_type_data_ptr, QString &result_type_string_name ) const =0;
	virtual ~I_IsType( ) = default;
};
#define isType( type , check) \
	if( typeid( type ) == check )\
		return true
#define isTypeResultName( type , check, fill ) \
	if( typeid( type ) == check )\
		{fill = typeid(type).name(  );  return true;}
#endif // I_ISTYPE_H_H_HEAD__FILE__
