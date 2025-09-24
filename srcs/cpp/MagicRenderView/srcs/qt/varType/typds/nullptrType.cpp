#include "./nullptrType.h"

#include "floatType.h"
#include "intType.h"
#include "stringType.h"
NullptrType::NullptrType( QObject *parent ) : BaseVarType( parent, std_shared_ptr< I_Type >( new I_Type( typeid( nullptr ) ) ) ) {

}
NullptrType::NullptrType( ) : NullptrType( nullptr ) { }
NullptrType::NullptrType( const NullptrType &other ) : BaseVarType { other } { }
NullptrType::~NullptrType( ) {
}

StringType operator+( const NullptrType &left_type_var_ref, const StringType &right_type_var_ref ) {
	return right_type_var_ref;
}
StringType operator-( const NullptrType &left_type_var_ref, const StringType &right_type_var_ref ) {
	return right_type_var_ref;
}
StringType operator*( const NullptrType &left_type_var_ref, const StringType &right_type_var_ref ) {
	return right_type_var_ref;
}
StringType operator/( const NullptrType &left_type_var_ref, const StringType &right_type_var_ref ) {
	return right_type_var_ref;
}
IntType operator+( const NullptrType &left_type_var_ref, const IntType &right_type_var_ref ) {
	return right_type_var_ref;
}
IntType operator-( const NullptrType &left_type_var_ref, const IntType &right_type_var_ref ) {
	return right_type_var_ref;
}
IntType operator*( const NullptrType &left_type_var_ref, const IntType &right_type_var_ref ) {
	return right_type_var_ref;
}
IntType operator/( const NullptrType &left_type_var_ref, const IntType &right_type_var_ref ) {
	return right_type_var_ref;
}
FloatType operator+( const NullptrType &left_type_var_ref, const FloatType &right_type_var_ref ) {
	return right_type_var_ref;
}
FloatType operator-( const NullptrType &left_type_var_ref, const FloatType &right_type_var_ref ) {
	return right_type_var_ref;
}
FloatType operator*( const NullptrType &left_type_var_ref, const FloatType &right_type_var_ref ) {
	return right_type_var_ref;
}
FloatType operator/( const NullptrType &left_type_var_ref, const FloatType &right_type_var_ref ) {
	return right_type_var_ref;
}
StringType operator+( const StringType &left_type_var_ref, const NullptrType &right_type_var_ref ) {
	return StringType( left_type_var_ref );
}
StringType operator-( const StringType &left_type_var_ref, const NullptrType &right_type_var_ref ) {
	return StringType( left_type_var_ref );
}
StringType operator*( const StringType &left_type_var_ref, const NullptrType &right_type_var_ref ) {
	return left_type_var_ref;
}
StringType operator/( const StringType &left_type_var_ref, const NullptrType &right_type_var_ref ) {
	return left_type_var_ref;
}
IntType operator+( const IntType &left_type_var_ref, const NullptrType &right_type_var_ref ) {
	return left_type_var_ref;
}
IntType operator-( const IntType &left_type_var_ref, const NullptrType &right_type_var_ref ) {
	return left_type_var_ref;
}
IntType operator*( const IntType &left_type_var_ref, const NullptrType &right_type_var_ref ) {
	return left_type_var_ref;
}
IntType operator/( const IntType &left_type_var_ref, const NullptrType &right_type_var_ref ) {
	return left_type_var_ref;
}
FloatType operator+( const FloatType &left_type_var_ref, const NullptrType &right_type_var_ref ) {
	return left_type_var_ref;
}
FloatType operator-( const FloatType &left_type_var_ref, const NullptrType &right_type_var_ref ) {
	return left_type_var_ref;
}
FloatType operator*( const FloatType &left_type_var_ref, const NullptrType &right_type_var_ref ) {
	return left_type_var_ref;
}
FloatType operator/( const FloatType &left_type_var_ref, const NullptrType &right_type_var_ref ) {
	return left_type_var_ref;
}
NullptrType & NullptrType::operator=( const StringType &right_type_var_ref ) {
	return *this;
}
NullptrType & NullptrType::operator=( const IntType &right_type_var_ref ) {
	return *this;
}
NullptrType & NullptrType::operator=( const FloatType &right_type_var_ref ) {
	return *this;
}
bool NullptrType::operator==( const StringType &right_type_var_ref ) const {
	if( &right_type_var_ref == nullptr )
		return true;
	return right_type_var_ref.var == nullptr;
}
bool NullptrType::operator==( const NullptrType &right_type_var_ref ) const {
	return true;
}
bool NullptrType::operator==( const FloatType &right_type_var_ref ) const {
	if( &right_type_var_ref == nullptr )
		return true;
	return right_type_var_ref.var == nullptr;
}
bool NullptrType::operator==( const IntType &right_type_var_ref ) const {
	if( &right_type_var_ref == nullptr )
		return true;
	return right_type_var_ref.var == nullptr;
}
bool NullptrType::operator==( const BaseVarType &right_type_var_ref ) const {
	if( &right_type_var_ref == nullptr )
		return true;
	return right_type_var_ref.getVarPtr( ) == nullptr;
}
