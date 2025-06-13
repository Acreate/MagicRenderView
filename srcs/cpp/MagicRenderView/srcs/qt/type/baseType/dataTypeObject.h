#ifndef DATATYPEOBJECT_H_H_HEAD__FILE__
#define DATATYPEOBJECT_H_H_HEAD__FILE__
#pragma once
#include "alias/type_alias.h"

#include "qt/type/ITypeObject.h"

class DataTypeObject : public ITypeObject {
	Q_OBJECT;
protected:
	std_shared_ptr< std_vector< uint8_t > > val;
public:
	DataTypeObject( const std_vector< uint8_t > &val, const std_vector< QString > &alias_type_name = { }, QObject *const parent = nullptr )
		: ITypeObject( alias_type_name, parent ),
		val( new std_vector< uint8_t >( val ) ) {
	}
	DataTypeObject( const std_vector< int8_t > &val, const std_vector< QString > &alias_type_name = { }, QObject *const parent = nullptr )
		: ITypeObject( alias_type_name, parent ) {
		currentTypeName.emplace_back( DataTypeObject::staticMetaObject.className( ) );
		size_t count = val.size( );
		this->val.reset( new std_vector< uint8_t >( count ) );
		if( count == 0 )
			return;
		auto data = val.data( );
		auto targetData = this->val->data( );
		for( --count; 0 < count; --count )
			targetData[ count ] = data[ count ];
		targetData[ 0 ] = data[ 0 ];
	}
	DataTypeObject( const std_vector< QString > &alias_type_name = { }, QObject *const parent = nullptr )
		: ITypeObject( alias_type_name, parent ),
		val( new std_vector< uint8_t >( ) ) {
		currentTypeName.emplace_back( DataTypeObject::staticMetaObject.className( ) );
	}

	Def_Clone_Move_override_function( DataTypeObject );

	DataTypeObject & operator=( const DataTypeObject &other ) {
		if( this == nullptr || thisPtr == nullptr )
			return *this;
		auto typeObject = &other;
		if( typeObject != nullptr && other.thisPtr != nullptr ) {
			if( this == typeObject )
				return *this;
			ITypeObject::operator =( other );
			val.reset( new std_vector< uint8_t >( ) );
			*val = *other.val;
		} else
			thisPtr = nullptr;
		return *this;
	}

	void append( int8_t data ) {
		val->emplace_back( data );
	}
	void append( int16_t data ) {
		auto stdVector = toData( data );
		size_t count = stdVector.size( );
		auto sourceData = stdVector.data( );
		for( size_t index = 0; index < count; ++index )
			val->emplace_back( sourceData[ index ] );
	}
	void append( int32_t data ) {
		auto stdVector = toData( data );
		size_t count = stdVector.size( );
		auto sourceData = stdVector.data( );
		for( size_t index = 0; index < count; ++index )
			val->emplace_back( sourceData[ index ] );
	}
	void append( int64_t data ) {
		auto stdVector = toData( data );
		size_t count = stdVector.size( );
		auto sourceData = stdVector.data( );
		for( size_t index = 0; index < count; ++index )
			val->emplace_back( sourceData[ index ] );
	}

	void append( uint8_t data ) {
		val->emplace_back( data );
	}
	void append( uint16_t data ) {
		auto stdVector = toData( data );
		size_t count = stdVector.size( );
		auto sourceData = stdVector.data( );
		for( size_t index = 0; index < count; ++index )
			val->emplace_back( sourceData[ index ] );
	}
	void append( uint32_t data ) {
		auto stdVector = toData( data );
		size_t count = stdVector.size( );
		auto sourceData = stdVector.data( );
		for( size_t index = 0; index < count; ++index )
			val->emplace_back( sourceData[ index ] );
	}
	void append( uint64_t data ) {
		auto stdVector = toData( data );
		size_t count = stdVector.size( );
		auto sourceData = stdVector.data( );
		for( size_t index = 0; index < count; ++index )
			val->emplace_back( sourceData[ index ] );
	}
	void clear( ) {
		val->clear( );
	}
	void resetSize( const size_t &new_size ) {
		val->resize( new_size );
	}
	size_t count( ) const {
		return val->size( );
	}
	std_vector< uint8_t > getCharArray( ) const {
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
	uint8_t & operator[]( const size_t &index ) const {
		size_t count = val->size( );
		uint8_t result = 0;
		if( count == 0 )
			return result;
		auto source = val->data( );
		return source[ index ];
	}

	int compare( const ITypeObject &rhs ) const override {
		decltype(this) result_ptr;
		int result = comp( this, &rhs, result_ptr );
		if( result == 0 && result_ptr != this ) {
			size_t count = val->size( );
			size_t countR = result_ptr->val->size( );
			if( count != countR )
				return count - countR;
			auto data = val->data( );
			auto compData = result_ptr->val->data( );
			for( countR = 0; count < countR; ++count )
				if( data[ count ] != compData[ count ] )
					return data[ count ] - compData[ count ];
			return 0;
		}
		return result;
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
	size_t serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) override;
	bool serializeToVectorData( std_vector< uint8_t > *result_data_vector ) const override;
};

#endif // DATATYPEOBJECT_H_H_HEAD__FILE__
