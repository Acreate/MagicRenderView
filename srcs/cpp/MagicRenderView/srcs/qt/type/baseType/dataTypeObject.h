#ifndef DATATYPEOBJECT_H_H_HEAD__FILE__
#define DATATYPEOBJECT_H_H_HEAD__FILE__
#pragma once
#include "alias/type_alias.h"

#include "qt/type/ITypeObject.h"

class DataTypeObject : public ITypeObject {
	Q_OBJECT;
protected:
	std_shared_ptr< std_vector< char > > val;
public:
	DataTypeObject( const std_vector< char > &val, QObject *const parent = nullptr )
		: ITypeObject( parent ),
		val( new std_vector< char > ) { }
	DataTypeObject( QObject *const parent = nullptr )
		: ITypeObject( parent ) { }
	void append( char data ) {
		val->emplace_back( data );
	}
	void append( uchar data ) {
		val->emplace_back( data );
	}
	void resetSize( const size_t &new_size ) {
		val->resize( new_size );
	}
	size_t count( ) const {
		return val->size( );
	}
	std_vector< char > getCharArray( ) const {
		return *val;
	}
	std_vector< uchar > getUCharArray( ) const {
		size_t count = val->size( );
		if( count == 0 )
			return { };
		std_vector< uchar > result( count );
		auto data = result.data( );
		auto source = val->data( );
		for( size_t index = 0; index < count; ++index )
			data[ index ] = source[ index ];
		return result;
	}
	char & operator[]( const size_t &index ) const {
		size_t count = val->size( );
		char result = 0;
		if( count == 0 )
			return result;

		auto source = val->data( );
		return source[ index ];
	}

	size_t typeMemorySize( ) const override {
		return val->size( ) * sizeof( char );
	}
	QString toString( ) const override {
		QStringList result;
		for( auto bin : *val )
			result.append( "0x" + QString::number( bin, 16 ) );
		return "{ " + result.join( ", " ) + " }";
	}
	bool isNullptr( ) const override {
		return false;
	}
};

#endif // DATATYPEOBJECT_H_H_HEAD__FILE__
