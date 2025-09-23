#include "./stringType.h"

#include "floatType.h"
#include "intType.h"

#include "../I_Type.h"

#include "../../generate/varGenerate.h"
StringType::StringType( QObject *parent ) : BaseVarType( parent, std_shared_ptr< I_Type >( new I_Type( typeid( t_current_type ) ) ) ), var( new t_current_type( ) ) {
}
StringType operator+( StringType &i, const StringType &i2 ) {
	return StringType( );
}
StringType operator-( StringType &i, const StringType &i2 ) {
	return StringType( );
}
StringType operator*( StringType &i, const StringType &i2 ) {
	return StringType( );
}
StringType operator/( StringType &i, const StringType &i2 ) {
	return StringType( );
}
StringType & StringType::operator=( const StringType &i2 ) {
	return *this;
}
StringType operator+( StringType &i, const IntType &i2 ) {
	return StringType( );
}
StringType operator-( StringType &i, const IntType &i2 ) {
	return StringType( );
}
StringType operator*( StringType &i, const IntType &i2 ) {
	return StringType( );
}
StringType operator/( StringType &i, const IntType &i2 ) {
	return StringType( );
}
StringType & StringType::operator=( const IntType &i2 ) {
	return *this;
}
StringType operator+( StringType &i, const FloatType &i2 ) {
	return StringType( );
}
StringType operator-( StringType &i, const FloatType &i2 ) {
	return StringType( );
}
StringType operator*( StringType &i, const FloatType &i2 ) {
	return StringType( );
}
StringType operator/( StringType &i, const FloatType &i2 ) {
	return StringType( );
}
StringType & StringType::operator=( const FloatType &i2 ) {
	return *this;
}
