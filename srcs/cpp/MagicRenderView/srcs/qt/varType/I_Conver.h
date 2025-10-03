#ifndef I_CONVER_H_H_HEAD__FILE__
#define I_CONVER_H_H_HEAD__FILE__
#pragma once
#include "I_Type.h"

class VarGenerate;
class BaseVarType;
class I_Type;
/// @brief 转换器接口，委托代理类
class I_Conver {
protected:
	VarGenerate *varGenerate;
public:
	I_Conver( );
	virtual ~I_Conver( ) = default;
	/// @brief 支持运算内容
	/// @param left_type_info 左值
	/// @param right_type_info 右值
	/// @return 不支持返回 false
	virtual bool supportType( const type_info &left_type_info, const type_info &right_type_info ) const {
		return false;
	}
	/// @brief 右值赋值于左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @return 成功赋值返回 true
	virtual bool fillTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
		return false;
	}
	/// @brief 右值赋予于右值加上左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @return 成功加上返回 true
	virtual bool addTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
		return false;
	}
	/// @brief 右值赋值于右值减去左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @return 成功赋值返回 true
	virtual bool subTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
		return false;
	}
	/// @brief 右值赋值于右值乘以左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @return 成功赋值返回 true
	virtual bool mulTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
		return false;
	}
	/// @brief 右值赋值于右值除以左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @return 成功赋值返回 true
	virtual bool divTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) {
		return false;
	}
	/// @brief 右值是否等于左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @param result_bool 返回结果
	/// @return 成功比较返回 true
	virtual bool equThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
		return false;
	}
	/// @brief 右值是否大于左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @param result_bool 返回结果
	/// @return 成功比较返回 true
	virtual bool greaterThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
		return false;
	}
	/// @brief 右值是否小于左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @param result_bool 返回结果
	/// @return 成功比较返回 true
	virtual bool lessThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
		return false;
	}
	/// @brief 右值是否大于等于左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @param result_bool 返回结果
	/// @return 成功比较返回 true
	virtual bool greaterOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
		return false;
	}
	/// @brief 右值是否小于于等于左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @param result_bool 返回结果
	/// @return 成功比较返回 true
	virtual bool lessOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) {
		return false;
	}
	/// @brief 识别类型，并且返回最终类型指针，失败返回 nullptr
	/// @tparam TResult 返回类型
	/// @param check_type 类型识别
	/// @param var_ptr 转换指针
	/// @return 成功返回的类型
	template< typename TResult >
	TResult * isType( const type_info &check_type, const void *var_ptr ) {
		if( check_type == typeid( TResult ) )
			return ( TResult * ) var_ptr;
		return nullptr;
	}

	template< typename TResult >
	bool typeCall( const type_info &check_type, const void *var_ptr, const std_function< bool( TResult * ) > &call ) {
		if( check_type == typeid( TResult ) )
			return call( ( TResult * ) var_ptr );
		return false;
	}
	template< typename ttype >
	bool stringFillToNumTypeVar( const QString *string, void *fill_target, const type_info &target_type_info, bool *conver_result ) {
		ttype *var = isType< ttype >( target_type_info, fill_target );
		if( var ) {
			qlonglong longLong = string->toLongLong( conver_result );
			if( *conver_result ) {
				*var = longLong;
				return true;
			}
			longLong = string->toLongLong( conver_result, 16 );
			if( *conver_result ) {
				*var = longLong;
				return true;
			}
			auto ulongLong = string->toULongLong( conver_result );
			if( *conver_result ) {
				*var = ulongLong;
				return true;
			}
			ulongLong = string->toULongLong( conver_result, 16 );
			if( *conver_result ) {
				*var = ulongLong;
				return true;
			}
			auto doublev = string->toDouble( conver_result );
			if( *conver_result ) {
				*var = doublev;
				return true;
			}
			return true;
		}
		return false;
	}

	bool fillInt( const QString *string, void *fill_target, const type_info &target_type_info );

	bool fillInt( const std::string *string, void *fill_target, const type_info &target_type_info ) {
		QString buff = QString::fromStdString( *string );
		return fillInt( &buff, fill_target, target_type_info );
	}

	bool fillInt( const std::wstring *string, void *fill_target, const type_info &target_type_info ) {
		QString buff = QString::fromStdWString( *string );
		return fillInt( &buff, fill_target, target_type_info );
	}

	bool fillFloat( const QString *string, void *fill_target, const type_info &target_type_info );

	bool fillFloat( const std::string *string, void *fill_target, const type_info &target_type_info ) {
		QString buff = QString::fromStdString( *string );
		return fillInt( &buff, fill_target, target_type_info );
	}

	bool fillFloat( const std::wstring *string, void *fill_target, const type_info &target_type_info ) {
		QString buff = QString::fromStdWString( *string );
		return fillInt( &buff, fill_target, target_type_info );
	}
};

#endif // I_CONVER_H_H_HEAD__FILE__
