﻿#ifndef INTTYPEOBJECT_H_H_HEAD__FILE__
#define INTTYPEOBJECT_H_H_HEAD__FILE__
#pragma once

#include "qt/types/ITypeObject.h"

class IntTypeObject : public ITypeObject {
	Q_OBJECT;
protected:
	int64_t val;
public:
	operator_virtual_equ( IntTypeObject, val );
public:
	explicit IntTypeObject( IVarStack *generate_this_var_stack_ptr_ptr, const std_function< std_shared_ptr< IVarStack > ( ) > &gener_var_stack, const std_vector< QString > &alias_type_name = { }, QObject *parent = nullptr ) : ITypeObject( generate_this_var_stack_ptr_ptr, gener_var_stack, alias_type_name, parent ), val( 0 ) {
	}
	explicit IntTypeObject( IVarStack *generate_this_var_stack_ptr_ptr, const std_function< std_shared_ptr< IVarStack > ( ) > &gener_var_stack, const int64_t val, const std_vector< QString > &alias_type_name = { }, QObject *parent = nullptr )
		: ITypeObject( generate_this_var_stack_ptr_ptr, gener_var_stack, alias_type_name, parent ), val( val ) {
		currentTypeName.emplace_back( IntTypeObject::staticMetaObject.className( ) );
	}
	Def_Clone_Move_override_function( IntTypeObject );
	IntTypeObject & operator=( const IntTypeObject &other ) {
		if( this == nullptr || thisPtr == nullptr )
			return *this;
		if( &other != nullptr && other.thisPtr != nullptr ) {
			if( this == &other )
				return *this;
			ITypeObject::operator =( other );
			val = other.val;
		} else
			thisPtr = nullptr;
		return *this;
	}

	int compare( const ITypeObject &rhs ) const override {
		decltype(this) result_ptr;
		int result = comp( this, &rhs, result_ptr );
		if( result == 0 && result_ptr != this )
			return this->val - result_ptr->val;
		return result;
	}
	virtual int64_t getVal( ) const { return val; }
	virtual void setVal( const int64_t val ) { this->val = val; }
	size_t typeMemorySize( ) const override {
		return sizeof val;
	}
	QString toString( ) const override {
		return QString::number( val );
	}

	size_t serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) override;
	bool serializeToVectorData( std_vector< uint8_t > *result_data_vector ) const override;

};

#endif // INTTYPEOBJECT_H_H_HEAD__FILE__
