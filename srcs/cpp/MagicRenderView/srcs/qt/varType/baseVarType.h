#ifndef BASEVARTYPE_H_H_HEAD__FILE__
#define BASEVARTYPE_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include <alias/type_alias.h>

class I_Type;
class I_Conver;
class I_Del;
class I_New;
class BaseVarType : public QObject {
	Q_OBJECT;
private:
	friend class VarGenerate;
	friend class StringType;
	friend class FloatType;
	friend class IntType;
	friend class NullptrType;
protected:
	/// @brief 记录当前类型
	std_shared_ptr< I_Type > typeInfo;
protected:
	BaseVarType( );
	BaseVarType( QObject *parent );
	BaseVarType( QObject *parent, const std_shared_ptr< I_Type > &type_info );
	BaseVarType( const BaseVarType &other );
	virtual void * getVarPtr( ) const = 0;
	virtual void * getVarPtr( const I_Type &type_info ) const;
public:
	~BaseVarType( ) override;
	virtual BaseVarType & operator=( const BaseVarType &other );
	virtual bool setVar( const BaseVarType *target_data );
	virtual const I_Type & getTypeInfo( ) const;
	template< typename type >
	type * getVarPtr( ) const {
		return ( type * ) getVarPtr( typeid( type ) );
	}
	
};

#endif // BASEVARTYPE_H_H_HEAD__FILE__
