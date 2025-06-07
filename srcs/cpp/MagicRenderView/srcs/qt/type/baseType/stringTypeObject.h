#ifndef STRINGTYPEOBJECT_H_H_HEAD__FILE__
#define STRINGTYPEOBJECT_H_H_HEAD__FILE__
#pragma once
#include "qt/type/ITypeObject.h"

class StringTypeObject : public ITypeObject {
	Q_OBJECT;
protected:
	QString string;
public:
	StringTypeObject( QObject *parnet = nullptr ): ITypeObject( parnet ) { }
	StringTypeObject( const QString &rhs, QObject *parnet = nullptr ): ITypeObject( parnet ) {
		string = rhs;
	}

	StringTypeObject( const StringTypeObject &rhs ): ITypeObject( rhs.parent( ) ) {
		string = rhs.string;
	}

	StringTypeObject & operator+=( const StringTypeObject &&rhs ) {
		string += rhs.string;
		return *this;
	}
	StringTypeObject & operator=( const StringTypeObject &&rhs ) {
		string = rhs.string;
		return *this;
	}
	StringTypeObject operator+( const StringTypeObject &&rhs ) const {
		StringTypeObject result;
		result.string = string + rhs.string;
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
	bool isNullptr( ) const override {
		return false;
	}
};

#endif // STRINGTYPEOBJECT_H_H_HEAD__FILE__
