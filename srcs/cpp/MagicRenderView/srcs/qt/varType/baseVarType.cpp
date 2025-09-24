#include "./baseVarType.h"
#include "I_Type.h"

#include "../generate/varGenerate.h"

#include "typds/floatType.h"
#include "typds/intType.h"
#include "typds/stringType.h"

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
	emit releaseObj( this );
}

const I_Type & BaseVarType::getTypeInfo( ) const {
	return *typeInfo.get( );
}

BaseVarType * operator+( const BaseVarType &left_type_var_ref, const BaseVarType *right_type_var_ref ) {
	I_Type parent = left_type_var_ref.getTypeInfo( );
	BaseVarType *result = VarGenerate::createVarType( parent );
	if( result == nullptr )
		return nullptr;
	if( VarGenerate::conver( result, &parent, left_type_var_ref.getVarPtr( ) ) == false ) {
		delete result;
		return nullptr;
	}
	if( VarGenerate::add( result, right_type_var_ref ) == false ) {
		delete result;
		return nullptr;
	}
	return result;
}
BaseVarType * operator-( const BaseVarType &left_type_var_ref, const BaseVarType *right_type_var_ref ) {
	I_Type parent = left_type_var_ref.getTypeInfo( );
	BaseVarType *result = VarGenerate::createVarType( parent );
	if( result == nullptr )
		return nullptr;
	if( VarGenerate::conver( result, &parent, left_type_var_ref.getVarPtr( ) ) == false ) {
		delete result;
		return nullptr;
	}
	if( VarGenerate::sub( result, right_type_var_ref ) == false ) {
		delete result;
		return nullptr;
	}
	return result;
}
BaseVarType * operator*( const BaseVarType &left_type_var_ref, const BaseVarType *right_type_var_ref ) {
	I_Type parent = left_type_var_ref.getTypeInfo( );
	BaseVarType *result = VarGenerate::createVarType( parent );
	if( result == nullptr )
		return nullptr;
	if( VarGenerate::conver( result, &parent, left_type_var_ref.getVarPtr( ) ) == false ) {
		delete result;
		return nullptr;
	}
	if( VarGenerate::mul( result, right_type_var_ref ) == false ) {
		delete result;
		return nullptr;
	}
	return result;
}
BaseVarType * operator/( const BaseVarType &left_type_var_ref, const BaseVarType *right_type_var_ref ) {
	I_Type parent = left_type_var_ref.getTypeInfo( );
	BaseVarType *result = VarGenerate::createVarType( parent );
	if( result == nullptr )
		return nullptr;
	if( VarGenerate::conver( result, &parent, left_type_var_ref.getVarPtr( ) ) == false ) {
		delete result;
		return nullptr;
	}
	if( VarGenerate::dev( result, right_type_var_ref ) == false ) {
		delete result;
		return nullptr;
	}
	return result;
}

BaseVarType * BaseVarType::operator=( const StringType *right_type_var_ref ) {
	VarGenerate::conver( &this->getTypeInfo( ), this->getVarPtr( ), &right_type_var_ref->getTypeInfo( ), right_type_var_ref->getVarPtr( ) );
	return this;
}
BaseVarType * BaseVarType::operator=( const IntType *right_type_var_ref ) {
	VarGenerate::conver( &this->getTypeInfo( ), this->getVarPtr( ), &right_type_var_ref->getTypeInfo( ), right_type_var_ref->getVarPtr( ) );
	return this;
}
BaseVarType * BaseVarType::operator=( const FloatType *right_type_var_ref ) {
	VarGenerate::conver( &this->getTypeInfo( ), this->getVarPtr( ), &right_type_var_ref->getTypeInfo( ), right_type_var_ref->getVarPtr( ) );
	return this;
}
