#include "./floatType.h"

#include "../I_Type.h"

#include "../../generate/varGenerate.h"
#include "intType.h"
#include "stringType.h"
#include <QDebug>

#include "../../tools/tools.h"
//FloatType operator+( const FloatType &i, const StringType &i2 ) {
//	FloatType result;
//	bool isOk = false;
//	double toDouble = i2.var->toDouble( &isOk );
//	if( !isOk )
//		if( toDouble = i2.var->toLongLong( &isOk ), !isOk )
//			if( toDouble = i2.var->toULongLong( &isOk ), !isOk )
//				return result;
//	*result.var = *i.var + toDouble;
//	return result;
//}
//FloatType operator-( const FloatType &i, const StringType &i2 ) {
//	FloatType result;
//	bool isOk = false;
//	double toDouble = i2.var->toDouble( &isOk );
//	if( !isOk )
//		if( toDouble = i2.var->toLongLong( &isOk ), !isOk )
//			if( toDouble = i2.var->toULongLong( &isOk ), !isOk )
//				return result;
//	*result.var = *i.var - toDouble;
//	return result;
//}
//FloatType operator*( const FloatType &i, const StringType &i2 ) {
//	FloatType result;
//	bool isOk = false;
//	double toDouble = i2.var->toDouble( &isOk );
//	if( !isOk )
//		if( toDouble = i2.var->toLongLong( &isOk ), !isOk )
//			if( toDouble = i2.var->toULongLong( &isOk ), !isOk )
//				return result;
//	*result.var = *i.var * toDouble;
//	return result;
//}
//FloatType operator/( const FloatType &i, const StringType &i2 ) {
//	FloatType result;
//	bool isOk = false;
//	double toDouble = i2.var->toDouble( &isOk );
//	if( !isOk )
//		if( toDouble = i2.var->toLongLong( &isOk ), !isOk )
//			if( toDouble = i2.var->toULongLong( &isOk ), !isOk )
//				return result;
//
//	if( toDouble != 0 )
//		*result.var = *i.var / toDouble;
//	return result;
//}
FloatType::FloatType( QObject *parent ) : BaseVarType( parent, std_shared_ptr< I_Type >( new I_Type( typeid( t_current_type ) ) ) ), var( new t_current_type( ) ) {
}
FloatType::FloatType( ) : FloatType( nullptr ) { }
FloatType::~FloatType( ) {
	delete var;
}
FloatType::FloatType( const FloatType &other ) : BaseVarType { other }, var { new t_current_type( *other.var ) } { }
//FloatType & FloatType::operator=( const StringType &i2 ) {
//	bool isOk = false;
//	double toDouble = i2.var->toDouble( &isOk );
//	if( !isOk )
//		if( toDouble = i2.var->toLongLong( &isOk ), !isOk )
//			if( toDouble = i2.var->toULongLong( &isOk ), !isOk )
//				return *this;
//	*this->var = toDouble;
//	return *this;
//}
//FloatType operator+( const FloatType &i, const IntType &i2 ) {
//	FloatType result;
//	*result.var = *i.var + *i2.var;
//	return result;
//}
//FloatType operator-( const FloatType &i, const IntType &i2 ) {
//	FloatType result;
//	*result.var = *i.var - *i2.var;
//	return result;
//}
//FloatType operator*( const FloatType &i, const IntType &i2 ) {
//	FloatType result;
//	*result.var = *i.var * *i2.var;
//	return result;
//}
//FloatType operator/( const FloatType &i, const IntType &i2 ) {
//	FloatType result;
//	if( *i2.var != 0 )
//		*result.var = *i.var / *i2.var;
//	return result;
//}
//FloatType & FloatType::operator=( const IntType &i2 ) {
//	*this->var = *i2.var;
//	return *this;
//}
//FloatType operator+( const FloatType &i, const FloatType &i2 ) {
//	FloatType result;
//	*result.var = *i.var + *i2.var;
//	return result;
//}
//FloatType operator-( const FloatType &i, const FloatType &i2 ) {
//	FloatType result;
//	*result.var = *i.var - *i2.var;
//	return result;
//}
//FloatType operator*( const FloatType &i, const FloatType &i2 ) {
//	FloatType result;
//	*result.var = *i.var * *i2.var;
//	return result;
//}
//FloatType operator/( const FloatType &i, const FloatType &i2 ) {
//	FloatType result;
//	if( *i2.var != 0 )
//		*result.var = *i.var + *i2.var;
//	return result;
//}
//FloatType & FloatType::operator=( const FloatType &i2 ) {
//	*this->var = *i2.var;
//	return *this;
//}
