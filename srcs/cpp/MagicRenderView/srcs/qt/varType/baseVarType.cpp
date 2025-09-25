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

bool BaseVarType::setVar( const BaseVarType *target_data ) {
	return VarGenerate::conver( this, target_data );
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

#define run_var_opt_ret_ref( fun_name_ ) \
	I_Type *thisVarTypeInfo = this->varTypeInfo.get( ); \
	I_Type *rightVarTypeInfo = set_string_var.varTypeInfo.get( ); \
	void *thisVarPtr = this->getVarPtr( ); \
	void *rightVarPtr = set_string_var.getVarPtr( ); \
	VarGenerate::fun_name_( thisVarTypeInfo, thisVarPtr, rightVarTypeInfo, rightVarPtr )
#define run_var_opt_ret_bool( fun_name_ ) \
	I_Type *thisVarTypeInfo = this->varTypeInfo.get( ); \
	I_Type *rightVarTypeInfo = set_string_var.varTypeInfo.get( ); \
	void *thisVarPtr = this->getVarPtr( ); \
	void *rightVarPtr = set_string_var.getVarPtr( ); \
	bool result_c = false; \
	VarGenerate::fun_name_( thisVarTypeInfo, thisVarPtr, rightVarTypeInfo, rightVarPtr,&result_c );\
	return result_c
#define run_var_opt_type_ret_ref( fun_name_ , type_)\
	I_Type *thisVarTypeInfo = this->varTypeInfo.get( ); \
	I_Type rightVarTypeInfo = typeid( type_ ); \
	void *thisVarPtr = this->getVarPtr( ); \
	const void *rightVarPtr = &set_string_var; \
	VarGenerate::fun_name_( thisVarTypeInfo, thisVarPtr, &rightVarTypeInfo, rightVarPtr ); \
	return *this
#define run_var_opt_type_ret_bool( fun_name_, type ) \
	I_Type *thisVarTypeInfo = this->varTypeInfo.get( ); \
	I_Type rightVarTypeInfo = typeid( type ); \
	void *thisVarPtr = this->getVarPtr( ); \
	const void *rightVarPtr = &set_string_var; \
	bool isResult = false; \
	VarGenerate::fun_name_( thisVarTypeInfo, thisVarPtr, &rightVarTypeInfo, rightVarPtr, &isResult ); \
	return isResult
BaseVarType & BaseVarType::operator=( const BaseVarType &set_string_var ) {
	if( this == &set_string_var )
		return *this;
	run_var_opt_ret_ref( conver );
	return *this;
}

bool BaseVarType::operator==( const BaseVarType &set_string_var ) const {
	if( this == &set_string_var )
		return true;
	run_var_opt_ret_bool( equThanTarget );
}
bool BaseVarType::operator>( const BaseVarType &set_string_var ) const {
	run_var_opt_ret_bool( greaterThanTarget );
}
bool BaseVarType::operator<( const BaseVarType &set_string_var ) const {
	run_var_opt_ret_bool( lessThanTarget );
}
bool BaseVarType::operator>=( const BaseVarType &set_string_var ) const {
	run_var_opt_ret_bool( greaterOrEquThanTarget );
}
bool BaseVarType::operator<=( const BaseVarType &set_string_var ) const {
	run_var_opt_ret_bool( lessOrEquThanTarget );
}

BaseVarType & BaseVarType::operator+=( const BaseVarType &set_string_var ) {
	run_var_opt_ret_ref( add );
	return *this;
}
BaseVarType & BaseVarType::operator-=( const BaseVarType &set_string_var ) {
	run_var_opt_ret_ref( sub );
	return *this;
}
BaseVarType & BaseVarType::operator*=( const BaseVarType &set_string_var ) {
	run_var_opt_ret_ref( mul );
	return *this;
}
BaseVarType & BaseVarType::operator/=( const BaseVarType &set_string_var ) {
	run_var_opt_ret_ref( div );
	return *this;
}

#define run_var_opt_ref_other_type_ret_ref( other_type )\
	BaseVarType & BaseVarType::operator=( const other_type &set_string_var ) {\
		run_var_opt_type_ret_ref( conver, other_type );\
	}\
	BaseVarType & BaseVarType::operator+=( const other_type &set_string_var ) {\
		run_var_opt_type_ret_ref( add, other_type );\
	}\
	BaseVarType & BaseVarType::operator-=( const other_type &set_string_var ) {\
		run_var_opt_type_ret_ref( sub, other_type );\
	}\
	BaseVarType & BaseVarType::operator*=( const other_type &set_string_var ) {\
		run_var_opt_type_ret_ref( mul, other_type );\
	}\
	BaseVarType & BaseVarType::operator/=( const other_type &set_string_var ) {\
		run_var_opt_type_ret_ref( div, other_type );\
	}\
	bool BaseVarType::operator==( const other_type &set_string_var ) const {\
		run_var_opt_type_ret_bool( equThanTarget, other_type );\
	}\
	bool BaseVarType::operator>( const other_type &set_string_var ) const {\
		run_var_opt_type_ret_bool( equThanTarget, other_type );\
	}\
	bool BaseVarType::operator<( const other_type &set_string_var ) const {\
		run_var_opt_type_ret_bool( equThanTarget, other_type );\
	}\
	bool BaseVarType::operator>=( const other_type &set_string_var ) const {\
		run_var_opt_type_ret_bool( equThanTarget, other_type );\
	}\
	bool BaseVarType::operator<=( const other_type &set_string_var ) const {\
		run_var_opt_type_ret_bool( equThanTarget, other_type );\
	}
run_var_opt_ref_other_type_ret_ref( QString );
run_var_opt_ref_other_type_ret_ref( std::string );
run_var_opt_ref_other_type_ret_ref( std::wstring );
run_var_opt_ref_other_type_ret_ref( std::int8_t );
run_var_opt_ref_other_type_ret_ref( std::int16_t );
run_var_opt_ref_other_type_ret_ref( std::int32_t );
run_var_opt_ref_other_type_ret_ref( std::int64_t );
run_var_opt_ref_other_type_ret_ref( std::uint8_t );
run_var_opt_ref_other_type_ret_ref( std::uint16_t );
run_var_opt_ref_other_type_ret_ref( std::uint32_t );
run_var_opt_ref_other_type_ret_ref( std::uint64_t );
run_var_opt_ref_other_type_ret_ref( bool );
run_var_opt_ref_other_type_ret_ref( std::float_t );
run_var_opt_ref_other_type_ret_ref( std::double_t );
