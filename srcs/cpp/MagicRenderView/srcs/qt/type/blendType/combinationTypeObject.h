#ifndef COMBINATIONTYPEOBJECT_H_H_HEAD__FILE__
#define COMBINATIONTYPEOBJECT_H_H_HEAD__FILE__
#pragma once

#include "alias/type_alias.h"

#include "qt/type/ITypeObject.h"

class CombinationTypeObject : public ITypeObject {
	Q_OBJECT;
protected:
	/// @brief 数据结构
	std_shared_ptr< std_vector< std_shared_ptr< std_pairt< std_shared_ptr< ITypeObject >, QString > > > > dataStruct;
public:
	CombinationTypeObject( const std_function< std_shared_ptr<IVarStack> ( ) > &gener_var_stack, const std_vector< QString > &alias_type_name = { }, QObject *parent = nullptr ) : ITypeObject( gener_var_stack, alias_type_name, parent ), dataStruct( new std_vector< std_shared_ptr< std_pairt< std_shared_ptr< ITypeObject >, QString > > >( ) ) {
	}
	Def_Clone_Move_override_function( CombinationTypeObject );
	CombinationTypeObject & operator=( const CombinationTypeObject &other ) {
		if( this == nullptr || thisPtr == nullptr )
			return *this;
		auto typeObject = &other;
		if( typeObject != nullptr && other.thisPtr != nullptr ) {
			if( this == typeObject )
				return *this;
			ITypeObject::operator =( other );
			dataStruct.reset( new std_vector< std_shared_ptr< std_pairt< std_shared_ptr< ITypeObject >, QString > > >( ) );
			*dataStruct = *other.dataStruct;
		} else
			thisPtr = nullptr;
		return *this;
	}
	virtual std_shared_ptr< ITypeObject > removeBeginElemnt( );

	virtual std_shared_ptr< ITypeObject > removeEndElemnt( );

	virtual std_shared_ptr< ITypeObject > removeItem( const QString &&var_name );

	virtual std_shared_ptr< ITypeObject > setVarObject( const std_shared_ptr< ITypeObject > &new_type, const QString &var_name );
	/// @brief 获取成员变量
	/// @param var_name 成员名称
	/// @return 变量
	virtual std_shared_ptr< ITypeObject > getVarObject( const QString &var_name ) const;
	/// @brief 获取匹配的结构体成员
	/// @param var_name 成员名称
	/// @return 成员
	virtual std_shared_ptr< ITypeObject > operator[]( const QString &var_name ) const {
		return getVarObject( var_name );
	}
	/// @brief 获取当前成员列表
	/// @return 成员列表
	virtual const std_vector< std_shared_ptr< std_pairt< std_shared_ptr< ITypeObject >, QString > > > & getStructInfo( ) const {
		return *dataStruct;
	}
	
	void clear() const;
	int compare( const ITypeObject &rhs ) const override;

	size_t typeMemorySize( ) const override;
	QString toString( ) const override;
	bool serializeToVectorData( std_vector< uint8_t > *result_data_vector ) const override;
	size_t serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) override;
};

#endif // COMBINATIONTYPEOBJECT_H_H_HEAD__FILE__
