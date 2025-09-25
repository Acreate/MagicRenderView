#ifndef VARGENERATE_H_H_HEAD__FILE__
#define VARGENERATE_H_H_HEAD__FILE__
#pragma once

#include <alias/type_alias.h>

#include "../varType/I_Type.h"
#include "../varType/baseVarType.h"

class IntType;
class StringType;
class FloatType;
class I_Type;
class I_Conver;
class VarGenerate {

protected:
	/// @brief 类型堆栈
	static std_vector< BaseVarType * > baseVarStack;

	/// @brief 类型创建列表
	static std_vector< std_pairt< std_shared_ptr< I_Type >, std_function< BaseVarType*( QObject * ) > > > varTypeGenerateVector;
	/// @brief 转换列表
	static std_vector< std_shared_ptr< I_Conver > > converVector;
	/// @brief 追加一个赋值类型对象
	/// @param new_conver 对象指针
	static void appendConverInstance( const std_shared_ptr< I_Conver > &new_conver );
	/// @brief 追加一个变量类型创建器
	/// @param info 变量类型
	/// @param generate_instance_function 创建器
	static void appendVarTypeGenerateInstance( const std_shared_ptr< I_Type > &info, const std_function< BaseVarType*( QObject * ) > &generate_instance_function );
public:
	/// @brief 类型转换赋值
	/// @param left_type_info left 类型信息
	/// @param left 被赋值
	/// @param right_type_info right 类型信息
	/// @param right 赋值
	/// @return left 值被 right 改变时，返回 true。否则返回 false
	static bool conver( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right );

	/// @brief 类型加法
	/// @param left_type_info left 类型信息
	/// @param left 被赋值
	/// @param right_type_info right 类型信息
	/// @param right 赋值
	/// @return left 值被 right 改变时，返回 true。否则返回 false
	static bool add( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right );

	/// @brief 类型减法
	/// @param left_type_info left 类型信息
	/// @param left 被赋值
	/// @param right_type_info right 类型信息
	/// @param right 赋值
	static bool sub( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right );

	/// @brief 类型乘法
	/// @param left_type_info left 类型信息
	/// @param left 被赋值
	/// @param right_type_info right 类型信息
	/// @param right 赋值
	static bool mul( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right );

	/// @brief 类型除法
	/// @param left_type_info left 类型信息
	/// @param left 被赋值
	/// @param right_type_info right 类型信息
	/// @param right 赋值
	static bool div( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right );

	/// @brief 右值是否等于左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @param result_bool 返回结果
	/// @return 成功比较返回 true
	static bool equThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool );
	/// @brief 右值是否大于左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @param result_bool 返回结果
	/// @return 成功比较返回 true
	static bool greaterThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool );
	/// @brief 右值是否小于左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @param result_bool 返回结果
	/// @return 成功比较返回 true
	static bool lessThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool );
	/// @brief 右值是否大于等于左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @param result_bool 返回结果
	/// @return 成功比较返回 true
	static bool greaterOrEquThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool );
	/// @brief 右值是否小于于等于左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @param result_bool 返回结果
	/// @return 成功比较返回 true
	static bool lessOrEquThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool );
	/// @brief 类型转换赋值
	/// @param left 被赋值
	/// @param right 赋值
	/// @return left 值被 right 改变时，返回 true。否则返回 false
	static bool conver( BaseVarType &left, const BaseVarType &right ) {
		return conver( left.varTypeInfo.get( ), left.getVarPtr( ), right.varTypeInfo.get( ), right.getVarPtr( ) );
	}
	/// @brief 类型转换赋值
	/// @param left 被赋值
	/// @param right 赋值
	/// @return left 值被 right 改变时，返回 true。否则返回 false
	static bool conver( BaseVarType *left, const BaseVarType *right ) {
		return conver( left->varTypeInfo.get( ), left->getVarPtr( ), right->varTypeInfo.get( ), right->getVarPtr( ) );
	}
	/// @brief 类型转换赋值
	/// @param left 被赋值
	/// @param right_type_info right 类型信息
	/// @param right 赋值
	/// @return left 值被 right 改变时，返回 true。否则返回 false
	static bool conver( BaseVarType *left, const I_Type *right_type_info, const void *right ) {
		return conver( left->varTypeInfo.get( ), left->getVarPtr( ), right_type_info, right );
	}
	/// @brief 类型转换赋值
	/// @param left 被赋值
	/// @param right 赋值
	/// @return left 值被 right 改变时，返回 true。否则返回 false
	static bool add( BaseVarType &left, const BaseVarType &right ) {
		return add( left.varTypeInfo.get( ), left.getVarPtr( ), right.varTypeInfo.get( ), right.getVarPtr( ) );
	}
	/// @brief 类型转换赋值
	/// @param left 被赋值
	/// @param right 赋值
	/// @return left 值被 right 改变时，返回 true。否则返回 false
	static bool add( BaseVarType *left, const BaseVarType *right ) {
		return add( left->varTypeInfo.get( ), left->getVarPtr( ), right->varTypeInfo.get( ), right->getVarPtr( ) );
	}
	/// @brief 类型转换赋值
	/// @param left 被赋值
	/// @param right_type_info right 类型信息
	/// @param right 赋值
	/// @return left 值被 right 改变时，返回 true。否则返回 false
	static bool add( BaseVarType *left, const I_Type *right_type_info, const void *right ) {
		return add( left->varTypeInfo.get( ), left->getVarPtr( ), right_type_info, right );
	}

	/// @brief 类型转换赋值
	/// @param left 被赋值
	/// @param right 赋值
	/// @return left 值被 right 改变时，返回 true。否则返回 false
	static bool sub( BaseVarType &left, const BaseVarType &right ) {
		return sub( left.varTypeInfo.get( ), left.getVarPtr( ), right.varTypeInfo.get( ), right.getVarPtr( ) );
	}
	/// @brief 类型转换赋值
	/// @param left 被赋值
	/// @param right 赋值
	/// @return left 值被 right 改变时，返回 true。否则返回 false
	static bool sub( BaseVarType *left, const BaseVarType *right ) {
		return sub( left->varTypeInfo.get( ), left->getVarPtr( ), right->varTypeInfo.get( ), right->getVarPtr( ) );
	}
	/// @brief 类型转换赋值
	/// @param left 被赋值
	/// @param right_type_info right 类型信息
	/// @param right 赋值
	/// @return left 值被 right 改变时，返回 true。否则返回 false
	static bool sub( BaseVarType *left, const I_Type *right_type_info, const void *right ) {
		return sub( left->varTypeInfo.get( ), left->getVarPtr( ), right_type_info, right );
	}
	/// @brief 类型转换赋值
	/// @param left 被赋值
	/// @param right 赋值
	/// @return left 值被 right 改变时，返回 true。否则返回 false
	static bool mul( BaseVarType &left, const BaseVarType &right ) {
		return mul( left.varTypeInfo.get( ), left.getVarPtr( ), right.varTypeInfo.get( ), right.getVarPtr( ) );
	}
	/// @brief 类型转换赋值
	/// @param left 被赋值
	/// @param right 赋值
	/// @return left 值被 right 改变时，返回 true。否则返回 false
	static bool mul( BaseVarType *left, const BaseVarType *right ) {
		return mul( left->varTypeInfo.get( ), left->getVarPtr( ), right->varTypeInfo.get( ), right->getVarPtr( ) );
	}
	/// @brief 类型转换赋值
	/// @param left 被赋值
	/// @param right_type_info right 类型信息
	/// @param right 赋值
	/// @return left 值被 right 改变时，返回 true。否则返回 false
	static bool mul( BaseVarType *left, const I_Type *right_type_info, const void *right ) {
		return mul( left->varTypeInfo.get( ), left->getVarPtr( ), right_type_info, right );
	}
	/// @brief 类型转换赋值
	/// @param left 被赋值
	/// @param right 赋值
	/// @return left 值被 right 改变时，返回 true。否则返回 false
	static bool div( BaseVarType &left, const BaseVarType &right ) {
		return div( left.varTypeInfo.get( ), left.getVarPtr( ), right.varTypeInfo.get( ), right.getVarPtr( ) );
	}
	/// @brief 类型转换赋值
	/// @param left 被赋值
	/// @param right 赋值
	/// @return left 值被 right 改变时，返回 true。否则返回 false
	static bool div( BaseVarType *left, const BaseVarType *right ) {
		return div( left->varTypeInfo.get( ), left->getVarPtr( ), right->varTypeInfo.get( ), right->getVarPtr( ) );
	}
	/// @brief 类型转换赋值
	/// @param left 被赋值
	/// @param right_type_info right 类型信息
	/// @param right 赋值
	/// @return left 值被 right 改变时，返回 true。否则返回 false
	static bool div( BaseVarType *left, const I_Type *right_type_info, const void *right ) {
		return div( left->varTypeInfo.get( ), left->getVarPtr( ), right_type_info, right );
	}

	/// @brief 增加一个类型赋值对象
	/// @tparam ttype 赋值对象类型
	template< typename ttype >
		requires requires ( ttype *ptr, I_Conver *base_ptr ) {
			base_ptr = ptr;
		}
	static void appendConverInstance( ) {
		appendConverInstance( std_shared_ptr< I_Conver >( new ttype ) );
	}
	/// @brief 追加一个类型创建器实例
	/// @tparam ttype 类型
	template< typename ttype >
		requires requires ( ttype *ptr, BaseVarType *base_ptr, QObject *parent ) {
			base_ptr = ptr;
			base_ptr = new ttype( parent );
		}
	static void appendVarTypeGenerateInstance( ) {
		std_shared_ptr< I_Type > sharedPtr( new I_Type( typeid( ttype ) ) );

		auto createLambda = [] ( QObject *parent )->BaseVarType * {
			ttype *resultPtr = new ttype( parent );
			baseVarStack.emplace_back( resultPtr );
			QObject::connect( resultPtr, &BaseVarType::releaseObj, [resultPtr] ( BaseVarType *delete_ptr ) {
				size_t count = baseVarStack.size( );
				if( count == 0 )
					return;
				auto data = baseVarStack.data( );
				for( size_t index = 0; index < count; ++index )
					if( data[ index ] == resultPtr ) {
						auto iterator = baseVarStack.begin( ) + index;
						baseVarStack.erase( iterator );
						break;
					}
			} );
			return resultPtr;
			return nullptr;
		};
		appendVarTypeGenerateInstance( sharedPtr, createLambda );
	}
	/// @brief 生成指定类型的共享对象
	/// @param create_type 生成类型
	/// @param parent 父节点
	/// @return 失败返回 nullptr
	static BaseVarType * createVarType( const I_Type &create_type, QObject *parent );

	/// @brief 生成指定类型的共享对象
	/// @param create_type 生成类型
	/// @return 失败返回 nullptr
	static BaseVarType * createVarType( const I_Type &create_type ) {
		return createVarType( create_type, nullptr );
	}

	/// @brief 生成指定类型的共享对象
	/// @param create_type 生成类型
	/// @param parent 父节点
	/// @return 失败返回 nullptr
	static BaseVarType * createVarType( const type_info &create_type, QObject *parent ) {
		return createVarType( I_Type( create_type ), parent );
	}

	/// @brief 生成指定类型的共享对象
	/// @param create_type 生成类型
	/// @return 失败返回 nullptr
	static BaseVarType * createVarType( const type_info &create_type ) {
		return createVarType( create_type, nullptr );
	}

	/// @brief 生成指定类型的共享对象
	/// @return 失败返回 nullptr
	template< typename ttype >
	static BaseVarType * createVarType( ) {
		return createVarType( typeid( ttype ) );
	}

	/// @brief 生成指定类型的共享对象
	/// @return 失败返回 nullptr
	template< typename ttype >
	static BaseVarType * createVarType( QObject *parent ) {
		return createVarType( typeid( ttype ), parent );
	}
	/// @brief 获取支持类型
	/// @return 类型列表
	static std_vector< std_shared_ptr< I_Type > > getSupporType( );
};

#endif // VARGENERATE_H_H_HEAD__FILE__
