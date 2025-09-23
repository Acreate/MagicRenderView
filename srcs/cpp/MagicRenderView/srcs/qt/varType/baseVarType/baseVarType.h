#ifndef BASEVARTYPE_H_H_HEAD__FILE__
#define BASEVARTYPE_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include "../../../alias/type_alias.h"

class I_Type;
class I_Var;
class I_Conver;
class I_Del;
class I_New;
class BaseVarType : public QObject {
	Q_OBJECT;
protected:
	/// @brief 记录当前类型
	std_shared_ptr<I_Type> typeInfo;
	/// @brief 类型转换列表
	std_vector< std_shared_ptr< I_Conver > > converVector;
	/// @brief 变量
	I_Var *var;
	/// @brief 变量的创建
	std_shared_ptr< I_New > newFcuntion;
	/// @brief 变量的释放
	std_shared_ptr< I_Del > delFcuntion;
protected:
	BaseVarType( QObject *parent, const std_vector< std_shared_ptr< I_Conver > > &conver_vector, const std_shared_ptr< I_New > &new_fcuntion, const std_shared_ptr< I_Del > &del_fcuntion );
	BaseVarType( const std_vector< std_shared_ptr< I_Conver > > &conver_vector, const std_shared_ptr< I_New > &new_fcuntion, const std_shared_ptr< I_Del > &del_fcuntion );
	BaseVarType( const BaseVarType &other );
public:
	~BaseVarType( ) override;
	virtual BaseVarType & operator=( const BaseVarType &other );
	virtual bool setVar( const I_Var *target_data );
	virtual bool setVar( const BaseVarType *target_data );
	virtual I_Var * getVarPtr( ) const {
		return var;
	}
	virtual const I_Type& getTypeInfo() const;
};

#endif // BASEVARTYPE_H_H_HEAD__FILE__
