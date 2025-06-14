#ifndef NULLTYPEOBJECT_H_H_HEAD__FILE__
#define NULLTYPEOBJECT_H_H_HEAD__FILE__
#pragma once
#include "qt/type/ITypeObject.h"

class NullTypeObject : public ITypeObject {
	Q_OBJECT;
public:
	static bool isNullptr( const ITypeObject *object ) {
		if( object == nullptr || qobject_cast< const NullTypeObject * >( object ) )
			return true;
		return object->isNullptr( );
	}
public:
	NullTypeObject( const std_function< IVarStack*( ) > &gener_var_stack, const std_vector< QString > &alias_type_name = { }, QObject *parent = nullptr ) : ITypeObject( gener_var_stack, alias_type_name, parent ) {
		thisPtr = nullptr;
	}
	Def_Clone_Move_override_function( NullTypeObject );

	NullTypeObject & operator=( const NullTypeObject &other ) {
		if( this == nullptr || thisPtr == nullptr )
			return *this;
		auto typeObject = &other;
		if( typeObject != nullptr && other.thisPtr != nullptr ) {
			if( this == &other )
				return *this;
			ITypeObject::operator =( other );
		} else
			thisPtr = nullptr;
		return *this;
	}
	size_t typeMemorySize( ) const override {
		return 0;
	}

	int compare( const ITypeObject &rhs ) const override {
		auto typeObject = &rhs;
		if( this == typeObject )
			return true;
		if( typeObject == nullptr || qobject_cast< const NullTypeObject * >( typeObject ) )
			return true;
		return typeObject->isNullptr( );
	}

	QString toString( ) const override {
		return "nullptr";
	}
	bool serializeToVectorData( std_vector< uint8_t > *result_data_vector ) const override;
	size_t serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) override;
};

#endif // NULLTYPEOBJECT_H_H_HEAD__FILE__
