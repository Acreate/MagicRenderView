#ifndef STRINGTYPEOBJECT_H_H_HEAD__FILE__
#define STRINGTYPEOBJECT_H_H_HEAD__FILE__
#pragma once
#include "qt/type/ITypeObject.h"

class StringTypeObject : public ITypeObject {
	Q_OBJECT;
protected:
	QString string;
public:
	StringTypeObject( IVarStack *gener_var_stack, const std_vector< QString > &alias_type_name = { }, QObject *parnet = nullptr ): ITypeObject( gener_var_stack, alias_type_name, parnet ) {
	}
	StringTypeObject( IVarStack *gener_var_stack, const QString &rhs, const std_vector< QString > &alias_type_name = { }, QObject *parnet = nullptr ): ITypeObject( gener_var_stack, alias_type_name, parnet ) {
		string = rhs;
	}

	Def_Clone_Move_override_function( StringTypeObject );

	virtual StringTypeObject & operator+=( const StringTypeObject &&rhs ) {
		if( this == nullptr || thisPtr == nullptr )
			return *this;
		auto typeObject = &rhs;
		if( typeObject != nullptr && rhs.thisPtr != nullptr ) {
			string += rhs.string;
			currentTypeName = rhs.currentTypeName;
		}
		return *this;
	}
	virtual StringTypeObject & operator=( const StringTypeObject &other ) {
		auto typeObject = &other;
		if( typeObject != nullptr ) {
			if( typeObject == this )
				return *this;
			ITypeObject::operator=( other );
			string = other.string;
			currentTypeName = other.currentTypeName;
		} else
			thisPtr = nullptr;
		return *this;
	}
	virtual StringTypeObject operator+( const StringTypeObject &&rhs ) const {
		StringTypeObject result( this->stack );
		result.string = string + rhs.string;
		return result;
	}
	int compare( const ITypeObject &rhs ) const override {
		decltype(this) result_ptr;
		int result = comp( this, &rhs, result_ptr );
		if( result == 0 && result_ptr != this )
			return this->string.compare( result_ptr->string );
		return result;
	}
	virtual const QString & getString( ) const { return string; }
	virtual void setString( const QString &string ) { this->string = string; }
	size_t typeMemorySize( ) const override {
		if( string.isNull( ) )
			return 0;
		return ( string.size( ) + 1 ) * sizeof QChar;
	}
	QString toString( ) const override {
		return string;
	}
	size_t serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) override;
	bool serializeToVectorData( std_vector< uint8_t > *result_data_vector ) const override;
};

#endif // STRINGTYPEOBJECT_H_H_HEAD__FILE__
