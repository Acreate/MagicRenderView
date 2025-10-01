#include "I_Var.h"

#include "I_Type.h"
I_Var::I_Var( const std_shared_ptr< I_Type > &type_info, const QString &var_name ) : typeInfo( type_info ), varName( var_name ) {
	I_Type *element = type_info.get( );
	auto &create = element->getCreate( );
	if( create )
		create( p );
	else
		p = nullptr;
}
I_Var::I_Var( const I_Var &other ) {
	auto &create = other.typeInfo->getCreate( );
	size_t memorySize = other.typeInfo->getMemorySize( );
	I_Type *element = new I_Type( other.typeInfo->getTypeInfo( ), memorySize, other.typeInfo->getRelease( ), create );
	typeInfo = std_shared_ptr< I_Type >( element );
	p = nullptr;
	if( create == nullptr || memorySize == 0 )
		return;
	create( p );
	memcpy( p, other.p, memorySize );
}
I_Var & I_Var::operator=( const I_Var &other ) {
	if( this == &other )
		return *this;
	auto &create = other.typeInfo->getCreate( );
	size_t memorySize = other.typeInfo->getMemorySize( );
	I_Type *element = new I_Type( other.typeInfo->getTypeInfo( ), memorySize, other.typeInfo->getRelease( ), create );
	typeInfo = std_shared_ptr< I_Type >( element );
	if( create && memorySize != 0 ) {
		create( p );
		memcpy( p, other.p, memorySize );
	} else
		p = nullptr;
	return *this;
}
I_Var::~I_Var( ) {
	if( p )
		typeInfo->getRelease( )( p );
	p = nullptr;
}
