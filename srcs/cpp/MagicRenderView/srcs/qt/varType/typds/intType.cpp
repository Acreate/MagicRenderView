#include "./intType.h"

#include "floatType.h"
#include "stringType.h"

#include "../I_Type.h"

#include "../../generate/varGenerate.h"
IntType::IntType( QObject *parent ) : BaseVarType( parent, std_shared_ptr< I_Type >( new I_Type( typeid( t_current_type ) ) ) ), var( new t_current_type( ) ) {
}
IntType operator+(const IntType &i, const StringType &i2 ) {
	IntType result;
	bool isOk = false;
	double toDouble = i2.var->toDouble( &isOk );
	if( !isOk )
		if( toDouble = i2.var->toLongLong( &isOk ), !isOk )
			if( toDouble = i2.var->toULongLong( &isOk ), !isOk )
				return result;
	*result.var = *i.var + toDouble;
	return result;
}
IntType operator-( const IntType &i, const StringType &i2 ) {
	IntType result;
	bool isOk = false;
	double toDouble = i2.var->toDouble( &isOk );
	if( !isOk )
		if( toDouble = i2.var->toLongLong( &isOk ), !isOk )
			if( toDouble = i2.var->toULongLong( &isOk ), !isOk )
				return result;
	*result.var = *i.var - toDouble;
	return result;
}
IntType operator*( const IntType &i, const StringType &i2 ) {
	IntType result;
	bool isOk = false;
	double toDouble = i2.var->toDouble( &isOk );
	if( !isOk )
		if( toDouble = i2.var->toLongLong( &isOk ), !isOk )
			if( toDouble = i2.var->toULongLong( &isOk ), !isOk )
				return result;
	*result.var = *i.var * toDouble;
	return result;
}
IntType operator/( const IntType &i, const StringType &i2 ) {
	IntType result;
	bool isOk = false;
	double toDouble = i2.var->toDouble( &isOk );
	if( !isOk )
		if( toDouble = i2.var->toLongLong( &isOk ), !isOk )
			if( toDouble = i2.var->toULongLong( &isOk ), !isOk )
				return result;
	if( toDouble != 0 )
		*result.var = *i.var / toDouble;
	return result;
}
IntType & IntType::operator=( const StringType &i2 ) {
	bool isOk = false;
	double toDouble = i2.var->toDouble( &isOk );
	if( !isOk )
		if( toDouble = i2.var->toLongLong( &isOk ), !isOk )
			if( toDouble = i2.var->toULongLong( &isOk ), !isOk )
				return *this;
	*this->var = toDouble;
	return *this;
}
IntType operator+( const IntType &i, const IntType &i2 ) {
	IntType result;
	*result.var = *i.var + *i2.var;
	return result;
}
IntType operator-( const IntType &i, const IntType &i2 ) {
	IntType result;
	*result.var = *i.var - *i2.var;
	return result;
}
IntType operator*( const IntType &i, const IntType &i2 ) {
	IntType result;
	*result.var = *i.var * *i2.var;
	return result;
}
IntType operator/( const IntType &i, const IntType &i2 ) {
	IntType result;
	if( *i2.var != 0 )
		*result.var = *i.var / *i2.var;
	return result;
}
IntType & IntType::operator=( const IntType &i2 ) {
	*this->var = *i2.var;
	return *this;
}
IntType operator+( const IntType &i, const FloatType &i2 ) {
	IntType result;
	*result.var = *i.var + *i2.var;
	return result;
}
IntType operator-( const IntType &i, const FloatType &i2 ) {
	IntType result;
	*result.var = *i.var - *i2.var;
	return result;
}
IntType operator*( const IntType &i, const FloatType &i2 ) {
	IntType result;
	*result.var = *i.var * *i2.var;
	return result;
}
IntType operator/( const IntType &i, const FloatType &i2 ) {
	IntType result;
	if( *i2.var != 0 )
		*result.var = *i.var / *i2.var;
	return result;
}
IntType & IntType::operator=( const FloatType &i2 ) {
	*this->var = *i2.var;
	return *this;
}
