#ifndef STRINGTYPEOBJECT_H_H_HEAD__FILE__
#define STRINGTYPEOBJECT_H_H_HEAD__FILE__
#pragma once
#include "qt/type/ITypeObject.h"

class StringTypeObject : public ITypeObject {
	Q_OBJECT;
protected:
	QString string;
public:
	StringTypeObject( const std_vector< QString > &alias_type_name = { }, QObject *parnet = nullptr ): ITypeObject( alias_type_name, parnet ) {
	}
	StringTypeObject( const QString &rhs, const std_vector< QString > &alias_type_name = { }, QObject *parnet = nullptr ): ITypeObject( alias_type_name, parnet ) {
		string = rhs;
	}

	Def_Clone_Move_override_function( StringTypeObject );

	StringTypeObject & operator+=( const StringTypeObject &&rhs ) {
		if( this == nullptr || thisPtr == nullptr )
			return *this;
		auto typeObject = &rhs;
		if( typeObject != nullptr && rhs.thisPtr != nullptr ) {
			string += rhs.string;
			currentTypeName = rhs.currentTypeName;
		}
		return *this;
	}
	StringTypeObject & operator=( const StringTypeObject &other ) {
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
	StringTypeObject operator+( const StringTypeObject &&rhs ) const {
		StringTypeObject result;
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

	size_t typeMemorySize( ) const override {
		if( string.isNull( ) )
			return 0;
		return ( string.size( ) + 1 ) * sizeof QChar;
	}
	QString toString( ) const override {
		return string;
	}
};

#endif // STRINGTYPEOBJECT_H_H_HEAD__FILE__
