#include "./baseVarType.h"
#include "I_Type.h"

#include "../generate/varGenerate.h"

BaseVarType::BaseVarType( ) : BaseVarType( nullptr ) {
}
BaseVarType::BaseVarType( QObject *parent ) : BaseVarType( parent, std_shared_ptr< I_Type >( new I_Type( typeid( nullptr ) ) ) ) {
}

BaseVarType::BaseVarType( const BaseVarType &other ) : QObject { other.parent( ) } {
	typeInfo = other.typeInfo;
}
BaseVarType::BaseVarType( QObject *parent, const std_shared_ptr< I_Type > &type_info ) : QObject( parent ),
	typeInfo( type_info ) { }
BaseVarType & BaseVarType::operator=( const BaseVarType &other ) {
	if( this == &other )
		return *this;
	setParent( other.parent( ) );
	typeInfo = other.typeInfo;
	return *this;
}
bool BaseVarType::setVar( const BaseVarType *target_data ) {
	return VarGenerate::conver( this, target_data );
}

void * BaseVarType::getVarPtr( const I_Type &type_info ) const {
	if( I_Type( type_info ) == *this->typeInfo.get( ) )
		return getVarPtr( );
	return nullptr;
}
BaseVarType::~BaseVarType( ) {

}

const I_Type & BaseVarType::getTypeInfo( ) const {
	return *typeInfo.get( );
}
