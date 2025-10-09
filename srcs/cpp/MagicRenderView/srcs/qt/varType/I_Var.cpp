#include "I_Var.h"

#include "I_Type.h"
I_Var::I_Var( I_Type *type_info, const QString &var_name ) : typeInfo( type_info ), varName( var_name ) {
	auto &create = type_info->getCreate( );
	if( create )
		p = create( );
	else
		p = nullptr;
	generateCode = ( size_t ) this;
}
I_Var::I_Var( I_Type *type_info, const size_t &generate_code, const QString &var_name ) : typeInfo( type_info ), generateCode( generate_code ), varName( var_name ) {
	auto &create = type_info->getCreate( );
	if( create )
		p = create( );
	else
		p = nullptr;
}
I_Var::I_Var( const I_Type &type_info, const QString &var_name ) : typeInfo( new I_Type( type_info.getTypeInfo( ), type_info.getMemorySize( ), type_info.getRelease( ), type_info.getCreate( ) ) ), varName( var_name ) {
	auto &create = type_info.getCreate( );
	if( create )
		p = create( );
	else
		p = nullptr;
	generateCode = ( size_t ) this;
}
I_Var::I_Var( const I_Type &type_info, const size_t &generate_code, const QString &var_name ) : typeInfo( new I_Type( type_info.getTypeInfo( ), type_info.getMemorySize( ), type_info.getRelease( ), type_info.getCreate( ) ) ), generateCode( generate_code ), varName( var_name ) {
	auto &create = type_info.getCreate( );
	if( create )
		p = create( );
	else
		p = nullptr;
}
I_Var::I_Var( const I_Var &other ) {
	generateCode = ( size_t ) this;
	auto &create = other.typeInfo->getCreate( );
	size_t memorySize = other.typeInfo->getMemorySize( );
	typeInfo = new I_Type( other.typeInfo->getTypeInfo( ), memorySize, other.typeInfo->getRelease( ), create );
	p = nullptr;
	if( create == nullptr || memorySize == 0 )
		return;
	p = create( );
	memcpy( p, other.p, memorySize );
}
I_Var & I_Var::operator=( const I_Var &other ) {
	if( this == &other )
		return *this;
	generateCode = ( size_t ) this;
	auto &create = other.typeInfo->getCreate( );
	size_t memorySize = other.typeInfo->getMemorySize( );
	typeInfo = new I_Type( other.typeInfo->getTypeInfo( ), memorySize, other.typeInfo->getRelease( ), create );
	if( create && memorySize != 0 ) {
		p = create( );
		memcpy( p, other.p, memorySize );
	} else
		p = nullptr;
	return *this;
}
I_Var::~I_Var( ) {
	if( p )
		typeInfo->getRelease( )( p );
	p = nullptr;
	delete typeInfo;
}
