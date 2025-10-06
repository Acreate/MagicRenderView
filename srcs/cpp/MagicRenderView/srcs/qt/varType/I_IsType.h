#ifndef I_ISTYPE_H_H_HEAD__FILE__
#define I_ISTYPE_H_H_HEAD__FILE__
#pragma once
#include <QString>
#include <alias/type_alias.h>
class VarGenerate;
class I_Var;
class I_Type;
/// @brief 类型识别器
class I_IsType {
protected:
	std_vector< QString > aliasTypeName;
	const type_info &currentTypeInfo;
	VarGenerate* varGenerate;
	I_IsType( const type_info &current_type_info );
public:
	/// @brief 目标为整数
	/// @param check_type_info 类型识别
	/// @param check_type_data_ptr 识别对象指针
	/// @param check_type_data_count 检查对象指向内存的数量
	/// @param result_alias_name_list 返回别名列表
	/// @return true 表示整形
	virtual bool getCheckTypeNames( const type_info &check_type_info, const uint8_t *check_type_data_ptr, const size_t &check_type_data_count, std_vector< QString > &result_alias_name_list ) const {
		return false;
	}
	/// @brief 创建匹配的类型
	/// @param check_type_info 创建的类型
	/// @param create_name 创建的类型名称
	/// @param create_is_right_call_back_function 创建成功时，会调用该函数，需要用户保存，并且返回 true，若返回 false，则自动释放
	/// @return 若成功创建并且调用create_is_right_call_back_function则返回 true（create_is_right_call_back_function 返回 false 时，仍然返回 true）
	virtual bool createCheckTypeName( const type_info &check_type_info, const QString &create_name, const std_function< bool( I_Var *create_var_ptr ) > &create_is_right_call_back_function ) const {
		return false;
	}
	virtual ~I_IsType( ) = default;
};
#endif // I_ISTYPE_H_H_HEAD__FILE__
