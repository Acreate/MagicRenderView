#include "./intType.h"

#include "floatType.h"
#include "stringType.h"

#include "../I_Type.h"

#include "../../generate/varGenerate.h"
IntType::IntType( QObject *parent ) : BaseVarType( parent, std_shared_ptr< I_Type >( new I_Type( typeid( t_current_type ) ) ) ), var( new t_current_type( ) ) {
}
IntType operator+( IntType &i, const StringType &i2 ) {
	return IntType( );
}
IntType operator-( IntType &i, const StringType &i2 ) {
	return IntType( );
}
IntType operator*( IntType &i, const StringType &i2 ) {
	return IntType( );
}
IntType operator/( IntType &i, const StringType &i2 ) {
	return IntType( );
}
IntType & IntType::operator=( const StringType &i2 ) {
	return *this;
}
IntType operator+( IntType &i, const IntType &i2 ) {
	return IntType( );
}
IntType operator-( IntType &i, const IntType &i2 ) {
	return IntType( );
}
IntType operator*( IntType &i, const IntType &i2 ) {
	return IntType( );
}
IntType operator/( IntType &i, const IntType &i2 ) {
	return IntType( );
}
IntType & IntType::operator=( const IntType &i2 ) {
	return *this;
}
IntType operator+( IntType &i, const FloatType &i2 ) {
	return IntType( );
}
IntType operator-( IntType &i, const FloatType &i2 ) {
	return IntType( );
}
IntType operator*( IntType &i, const FloatType &i2 ) {
	return IntType( );
}
IntType operator/( IntType &i, const FloatType &i2 ) {
	return IntType( );
}
IntType & IntType::operator=( const FloatType &i2 ) {
	return *this;
}
