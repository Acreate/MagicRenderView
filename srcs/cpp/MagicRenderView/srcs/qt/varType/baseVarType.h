#ifndef BASEVARTYPE_H_H_HEAD__FILE__
#define BASEVARTYPE_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include <alias/type_alias.h>

#include "I_Type.h"

class I_Conver;
class I_Del;
class I_New;
class BaseVarType : public QObject {
	Q_OBJECT;
private:
	friend class VarGenerate;
	std_function< bool ( ) > baseVarTypeInitTypeInfo;
protected:
	/// @brief 生成代码
	size_t generateCode;
	/// @brief 记录当前类型
	std_shared_ptr< I_Type > varTypeInfo;
	/// @brief 记录对象自身类型
	std_shared_ptr< I_Type > objTypeInfo;
	/// @brief 初始化函数
	std_function< bool ( ) > initTypeInfo;
	/// @brief 对象释放调用函数
	std_function< void ( ) > deleteCall;
protected:
	BaseVarType( );
	BaseVarType( QObject *parent );
	/// @brief 给当前对象赋予 target_data_ptr 值
	/// @param target_data_type_info target_data_ptr 对象值的类型
	/// @param target_data_ptr 右值
	/// @return 成功改变 this 对象值，返回 true
	virtual bool setVar( const I_Type *target_data_type_info, const void *target_data_ptr );
	/// @brief 对象值赋予到 target_data_ptr
	/// @param target_data_type_info target_data_ptr 对象值的类型
	/// @param target_data_ptr 左值
	/// @return 成功改变 target_data_ptr 值，返回 true
	virtual bool getVar( const I_Type *target_data_type_info, void *target_data_ptr );
public:
	virtual const std_function< bool( ) > & getBaseVarTypeInitTypeInfo( ) const { return baseVarTypeInitTypeInfo; }
	virtual void * getVarPtr( ) const = 0;
	virtual void * getVarPtr( const I_Type &type_info ) const;
	/// @brief 重置为默认
	virtual void resetVar( ) = 0;
	~BaseVarType( ) override;
	virtual I_Type * getVarTypeInfoPtr( ) const;
	virtual I_Type * getThisTypeInfoPtr( ) const;
	virtual bool setVar( const BaseVarType *target_data_ptr ) {
		return this->setVar( target_data_ptr->getVarTypeInfoPtr( ), target_data_ptr->getVarPtr( ) );
	}
	virtual bool getVar( BaseVarType *target_data_ptr ) {
		return this->getVar( target_data_ptr->getVarTypeInfoPtr( ), target_data_ptr->getVarPtr( ) );
	}
	template< typename type >
	type * getVarPtr( ) const {
		return ( type * ) getVarPtr( typeid( type ) );
	}
	template< typename type >
	bool setVar( const type *target_data_ptr ) {
		I_Type iType( typeid( type ) );
		return this->getVar( &iType, target_data_ptr );
	}
	template< typename type >
	bool getVar( type *target_data_ptr ) {
		I_Type iType( typeid( type ) );
		return this->getVar( &iType, target_data_ptr );
	}
public: // 删除列表
	/// @brief 同时与 BaseVarType & operator =( const BaseVarType *right_type_var_ref )  激活时，赋予指针赋值，但类型会降级，再也无法升级到子类。@code *varptr = varptr @cond 
	/// @param other 
	BaseVarType( const BaseVarType &other ) = delete;
	/// @brief 同时与 BaseVarType( const BaseVarType &other ) 激活时，赋予指针赋值，但类型会降级，再也无法升级到子类。@code *varptr = varptr @cond 
	const BaseVarType & operator =( const BaseVarType *right_type_var_ref ) = delete;
Q_SIGNALS:
	void releaseObj( BaseVarType *release );

};

#endif // BASEVARTYPE_H_H_HEAD__FILE__
