#ifndef STACK_H_H_HEAD__FILE__
#define STACK_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include <alias/type_alias.h>

class Stack : public QObject {
	Q_OBJECT;
public:
	using TypeItemKey = const void *;
	using TypeItemVal = QString;
	using TypeItem = std_pairt< TypeItemKey, TypeItemVal >;
	using TypeItemArray = std_vector< TypeItem >;
protected:
	TypeItemArray typeNameMap;
	virtual bool isType( const TypeItemKey &check_obj_ptr, const TypeItemVal &type_name ) const {
		size_t count = typeNameMap.size( );
		auto data = typeNameMap.data( );
		for( size_t index = 0; index < count; ++index )
			if( data[ index ].first == check_obj_ptr ) {
				if( data[ index ].second == type_name )
					return true;
				break;
			}
		return false;
	}
	virtual void appendType( TypeItemKey check_obj_ptr, const TypeItemVal &type_name ) {
		size_t count = typeNameMap.size( );
		auto data = typeNameMap.data( );
		for( size_t index = 0; index < count; ++index )
			if( data[ index ].first == check_obj_ptr ) {
				data[ index ] = TypeItem( check_obj_ptr, type_name );
				return;
			}
		typeNameMap.emplace_back( check_obj_ptr, type_name );
	}
public:
	template< typename TTypeNmae >
	bool isType( const TTypeNmae *check_obj_ptr ) const {
		return isType( check_obj_ptr, typeid( TTypeNmae ).name( ) );
	}
	template< typename TTypeNmae >
	void appendType( const TTypeNmae *check_obj_ptr ) {
		appendType( check_obj_ptr, typeid( TTypeNmae ).name( ) );
	}
	template< typename TTypeNmae >
	std_vector< TTypeNmae * > getType( ) {
		auto typeName = typeid( TTypeNmae ).name( );
		std_vector< TTypeNmae > result;
		size_t count = typeNameMap.size( );
		auto data = typeNameMap.data( );
		for( size_t index = 0; index < count; ++index )
			if( data[ index ].second == typeName )
				result.emplace_back( data[ index ].first );
		return result;
	}
	virtual TypeItemVal typeName( const TypeItemKey *check_obj_ptr ) {
		size_t count = typeNameMap.size( );
		auto data = typeNameMap.data( );
		for( size_t index = 0; index < count; ++index )
			if( data[ index ].first == check_obj_ptr )
				return data[ index ].second;
		return TypeItemVal( typeid( nullptr_t ).name( ) );
	}
};

#endif // STACK_H_H_HEAD__FILE__
