#include "baseVarType.h"
#include "I_Type.h"
#include "../generate/varGenerate.h"

#include "../tools/tools.h"

#include "typds/nullptrType.h"

BaseVarType::BaseVarType( ) : BaseVarType( nullptr ) {
}
BaseVarType::BaseVarType( QObject *parent ) : QObject( parent ) {
	this->baseVarTypeInitTypeInfo = [this]( ) {
		const type_info &typeInfo = typeid( *this );
		I_Type *px = new I_Type( typeInfo );
		objTypeInfo.reset( px );
		varTypeInfo.reset( new I_Type( typeid( nullptr ) ) );
		return px;
	};
	this->initTypeInfo = [this] {
		return baseVarTypeInitTypeInfo( );
	};
}
bool BaseVarType::setVar( const I_Type *target_data_type_info, const void *target_data_ptr ) {
	return VarGenerate::conver( this->getVarTypeInfoPtr( ), this->getVarPtr( ), target_data_type_info, target_data_ptr );
}
bool BaseVarType::getVar( const I_Type *target_data_type_info, void *target_data_ptr ) {
	return VarGenerate::conver( target_data_type_info, target_data_ptr, this->getVarTypeInfoPtr( ), this->getVarPtr( ) );
}

void * BaseVarType::getVarPtr( const I_Type &type_info ) const {
	if( I_Type( type_info ) == *this->varTypeInfo.get( ) )
		return getVarPtr( );
	return nullptr;
}
BaseVarType::~BaseVarType( ) {
	emit releaseObj( this );
	if( deleteCall )
		deleteCall( );
}

I_Type * BaseVarType::getVarTypeInfoPtr( ) const {
	return varTypeInfo.get( );
}
I_Type * BaseVarType::getThisTypeInfoPtr( ) const {
	return objTypeInfo.get( );
}
