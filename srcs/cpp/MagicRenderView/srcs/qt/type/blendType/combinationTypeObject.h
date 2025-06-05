#ifndef COMBINATIONTYPEOBJECT_H_H_HEAD__FILE__
#define COMBINATIONTYPEOBJECT_H_H_HEAD__FILE__
#pragma once

#include "alias/type_alias.h"

#include "qt/type/ITypeObject.h"
#include "qt/type/baseType/nullTypeObject.h"
#include "qt/type/sequenceType/pairtTypeObject.h"

class CombinationTypeObject : public ITypeObject {
	Q_OBJECT;
protected:
	/// @brief 数据结构
	std_vector< std_shared_ptr< std_pairt< std_shared_ptr< ITypeObject >, QString > > > dataStruct;
public:
	CombinationTypeObject( QObject *parent = nullptr ) : ITypeObject( parent ) { }

	virtual ITypeObject * setVarObject( const std_shared_ptr< ITypeObject > &new_type, const QString &&var_name ) {
		for( auto &pair : dataStruct )
			if( pair->second == var_name ) {
				ITypeObject *element = pair->first.get( ); // 用于覆盖返回
				pair->first = new_type;
				return element;
			}

		auto ptr = std_shared_ptr< std_pairt< std_shared_ptr< ITypeObject >, QString > >( );
		ptr->first = new_type;
		ptr->second = var_name;
		dataStruct.emplace_back( ptr );
		return nullptr;
	}

	virtual ITypeObject * getVarObject( const QString &&var_name ) const {
		for( auto pair : dataStruct )
			if( pair->second == var_name )
				return pair->first.get( );
		return nullptr;
	}

	virtual const std_shared_ptr< ITypeObject > & operator[]( const QString &&var_name ) const {
		for( auto pair : dataStruct )
			if( pair->second == var_name )
				return pair->first;
		std_shared_ptr< ITypeObject > shared( new NullTypeObject( ) ); // 返回一个空指针
		return shared;
	}

	virtual std_shared_ptr< ITypeObject > & operator[]( const QString &&var_name ) {
		for( auto pair : dataStruct )
			if( pair->second == var_name )
				return pair->first;
		std_shared_ptr< ITypeObject > shared( new NullTypeObject( ) ); // 返回一个空指针
		return shared;
	}

	int compare( const ITypeObject &rhs ) const override {
		auto typeObject = &rhs;
		if( this == typeObject )
			return 0;
		auto combinationTypeObject = qobject_cast< CombinationTypeObject * >( typeObject );
		if( combinationTypeObject == nullptr )
			return -2;
		size_t thisCount = dataStruct.size( );
		size_t rCount = combinationTypeObject->dataStruct.size( );
		if( thisCount > rCount )
			return 1;
		if( thisCount < rCount )
			return -1;
		for( size_t index = 0; index < thisCount; ++index ) {
			int compare = dataStruct[ index ]->first->compare( *combinationTypeObject->dataStruct[ index ]->first );
			if( compare != 0 )
				return compare;
			compare = dataStruct[ index ]->second.compare( combinationTypeObject->dataStruct[ index ]->second );
			if( compare != 0 )
				return compare;
		}
		return 0;
	}

	size_t typeMemorySize( ) const override {
		size_t result = 0;
		for( auto pair : dataStruct )
			result += pair->first->typeMemorySize( ) + ( pair->second.size( ) + 1 ) * sizeof( QChar );
		return result;
	}
	QString toString( ) const override {
		QStringList result;
		for( auto pair : dataStruct )
			result.append( pair->first->toString( ) + " " + pair->second );
		return "{" + result.join( "," ) + "}";
	}
	QString typeName( ) const override {
		return "CombinationTypeObject";
	}
	bool isNullptr( ) const override {
		return false;
	}
};

#endif // COMBINATIONTYPEOBJECT_H_H_HEAD__FILE__
