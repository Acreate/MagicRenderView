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

BaseVarType * operator+( const BaseVarType &left_type_var_ref, const BaseVarType *right_type_var_ref ) {
	I_Type *varTypeInfo = left_type_var_ref.getThisTypeInfoPtr( );
	auto result = VarGenerate::createVarType( *varTypeInfo, varTypeInfo );
	if( result == nullptr )
		return nullptr;

	I_Type *dataType = result->getVarTypeInfoPtr( );
	if( VarGenerate::conver( result, dataType, left_type_var_ref.getVarPtr( ) ) == false ) {
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
	I_Type *varTypeInfo = left_type_var_ref.getThisTypeInfoPtr( );
	auto result = VarGenerate::createVarType( *varTypeInfo, varTypeInfo );
	if( result == nullptr )
		return nullptr;
	I_Type *dataType = result->getVarTypeInfoPtr( );
	if( VarGenerate::conver( result, dataType, left_type_var_ref.getVarPtr( ) ) == false ) {
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
	I_Type *varTypeInfo = left_type_var_ref.getThisTypeInfoPtr( );
	auto result = VarGenerate::createVarType( *varTypeInfo, varTypeInfo );
	if( result == nullptr )
		return nullptr;
	I_Type *dataType = result->getVarTypeInfoPtr( );
	if( VarGenerate::conver( result, dataType, left_type_var_ref.getVarPtr( ) ) == false ) {
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
	I_Type *varTypeInfo = left_type_var_ref.getThisTypeInfoPtr( );
	auto result = VarGenerate::createVarType( *varTypeInfo, varTypeInfo );
	if( result == nullptr )
		return nullptr;
	I_Type *dataType = result->getVarTypeInfoPtr( );
	if( VarGenerate::conver( result, dataType, left_type_var_ref.getVarPtr( ) ) == false ) {
		delete result;
		return nullptr;
	}
	if( VarGenerate::div( result, right_type_var_ref ) == false ) {
		delete result;
		return nullptr;
	}
	return result;
}

BaseVarType * BaseVarType::operator=( const BaseVarType &right_type_var_ref ) {
	auto *leftTypeInfo = this->getVarTypeInfoPtr( );
	auto *rightTypeInfo = right_type_var_ref.getVarTypeInfoPtr( );
	auto left = this->getVarPtr( );
	auto right = right_type_var_ref.getVarPtr( );
	VarGenerate::conver( leftTypeInfo, left, rightTypeInfo, right );
	return this;
}
#define conver_fill_type( type_info_, right_var_ref )\
	auto *leftTypeInfo = this->getVarTypeInfoPtr( ); \
	auto left = this->getVarPtr( ); \
	auto rightTypeInfo = I_Type( typeid( type_info_ ) ); \
	auto right = &right_var_ref; \
	VarGenerate::conver( leftTypeInfo, left, &rightTypeInfo, right )

BaseVarType * BaseVarType::operator=( const int8_t &right_type_var_ref ) {
	conver_fill_type( int8_t, right_type_var_ref );
	return this;
}
BaseVarType * BaseVarType::operator=( const int16_t &right_type_var_ref ) {
	conver_fill_type( int16_t, right_type_var_ref );
	return this;
}

BaseVarType * BaseVarType::operator=( const int32_t &right_type_var_ref ) {
	conver_fill_type( int32_t, right_type_var_ref );
	return this;
}
BaseVarType * BaseVarType::operator=( const int64_t &right_type_var_ref ) {
	conver_fill_type( int64_t, right_type_var_ref );
	return this;
}
BaseVarType * BaseVarType::operator=( const float &right_type_var_ref ) {
	conver_fill_type( float, right_type_var_ref );
	return this;
}
BaseVarType * BaseVarType::operator=( const double &right_type_var_ref ) {
	conver_fill_type( double, right_type_var_ref );
	return this;
}
BaseVarType * BaseVarType::operator=( const QString &right_type_var_ref ) {
	conver_fill_type( QString, right_type_var_ref );
	return this;
}
BaseVarType * BaseVarType::operator=( const uint8_t &right_type_var_ref ) {
	conver_fill_type( uint8_t, right_type_var_ref );
	return this;
}
BaseVarType * BaseVarType::operator=( const uint16_t &right_type_var_ref ) {
	conver_fill_type( uint16_t, right_type_var_ref );
	return this;
}
BaseVarType * BaseVarType::operator=( const uint32_t &right_type_var_ref ) {
	conver_fill_type( uint32_t, right_type_var_ref );
	return this;
}
BaseVarType * BaseVarType::operator=( const uint64_t &right_type_var_ref ) {
	conver_fill_type( uint64_t, right_type_var_ref );
	return this;
}
#define comp_BaseVarType_type( comp_function_name_ ) \
	auto leftTypeInfo = this->getVarTypeInfoPtr( ); \
	auto rightTypeInfo = right_type_var_ref.getVarTypeInfoPtr( ); \
	auto left = this->getVarPtr( ); \
	auto right = right_type_var_ref.getVarPtr( ); \
	bool result = false; \
	VarGenerate::comp_function_name_( leftTypeInfo, left, rightTypeInfo, right, &result ); \
	return result
bool BaseVarType::operator==( const BaseVarType &right_type_var_ref ) {
	comp_BaseVarType_type( equThanTarget );
}
bool BaseVarType::operator>( const BaseVarType &right_type_var_ref ) {
	comp_BaseVarType_type( greaterThanTarget );
}
bool BaseVarType::operator<( const BaseVarType &right_type_var_ref ) {
	comp_BaseVarType_type( lessThanTarget );
}
bool BaseVarType::operator<=( const BaseVarType &right_type_var_ref ) {
	comp_BaseVarType_type( lessOrEquThanTarget );
}
bool BaseVarType::operator>=( const BaseVarType &right_type_var_ref ) {
	comp_BaseVarType_type( greaterOrEquThanTarget );
}

#define comp_any_type( type_info_, com_function_name_) \
	auto leftTypeInfo = this->getVarTypeInfoPtr( ); \
	auto left = this->getVarPtr( ); \
	auto rightTypeInfo = I_Type( typeid( type_info_ ) ); \
	auto right = &right_type_var_ref; \
	bool result = false; \
	VarGenerate::com_function_name_( leftTypeInfo, left, &rightTypeInfo, right, &result ); \
	return result
bool BaseVarType::operator==( const int8_t &right_type_var_ref ) {
	comp_any_type( int8_t, equThanTarget );
}
bool BaseVarType::operator>( const int8_t &right_type_var_ref ) {
	comp_any_type( int8_t, greaterThanTarget );
}
bool BaseVarType::operator<( const int8_t &right_type_var_ref ) {
	comp_any_type( int8_t, lessThanTarget );
}
bool BaseVarType::operator<=( const int8_t &right_type_var_ref ) {
	comp_any_type( int8_t, lessOrEquThanTarget );
}
bool BaseVarType::operator>=( const int8_t &right_type_var_ref ) {
	comp_any_type( int8_t, greaterOrEquThanTarget );
}
bool BaseVarType::operator==( const int16_t &right_type_var_ref ) {
	comp_any_type( int16_t, equThanTarget );
}
bool BaseVarType::operator>( const int16_t &right_type_var_ref ) {
	comp_any_type( int16_t, greaterThanTarget );
}
bool BaseVarType::operator<( const int16_t &right_type_var_ref ) {
	comp_any_type( int16_t, lessThanTarget );
}
bool BaseVarType::operator<=( const int16_t &right_type_var_ref ) {
	comp_any_type( int16_t, lessOrEquThanTarget );
}
bool BaseVarType::operator>=( const int16_t &right_type_var_ref ) {
	comp_any_type( int16_t, greaterOrEquThanTarget );
}
bool BaseVarType::operator==( const int32_t &right_type_var_ref ) {
	comp_any_type( int32_t, equThanTarget );
}
bool BaseVarType::operator>( const int32_t &right_type_var_ref ) {
	comp_any_type( int32_t, greaterThanTarget );
}
bool BaseVarType::operator<( const int32_t &right_type_var_ref ) {
	comp_any_type( int32_t, lessThanTarget );
}
bool BaseVarType::operator<=( const int32_t &right_type_var_ref ) {
	comp_any_type( int32_t, lessOrEquThanTarget );
}
bool BaseVarType::operator>=( const int32_t &right_type_var_ref ) {
	comp_any_type( int32_t, greaterOrEquThanTarget );
}
bool BaseVarType::operator==( const int64_t &right_type_var_ref ) {
	comp_any_type( int64_t, equThanTarget );
}
bool BaseVarType::operator>( const int64_t &right_type_var_ref ) {
	comp_any_type( int64_t, greaterThanTarget );
}
bool BaseVarType::operator<( const int64_t &right_type_var_ref ) {
	comp_any_type( int64_t, lessThanTarget );
}
bool BaseVarType::operator<=( const int64_t &right_type_var_ref ) {
	comp_any_type( int64_t, lessOrEquThanTarget );
}
bool BaseVarType::operator>=( const int64_t &right_type_var_ref ) {
	comp_any_type( int64_t, greaterOrEquThanTarget );
}
bool BaseVarType::operator==( const uint8_t &right_type_var_ref ) {
	comp_any_type( uint8_t, equThanTarget );
}
bool BaseVarType::operator>( const uint8_t &right_type_var_ref ) {
	comp_any_type( uint8_t, greaterThanTarget );
}
bool BaseVarType::operator<( const uint8_t &right_type_var_ref ) {
	comp_any_type( uint8_t, lessThanTarget );
}
bool BaseVarType::operator<=( const uint8_t &right_type_var_ref ) {
	comp_any_type( uint8_t, lessOrEquThanTarget );
}
bool BaseVarType::operator>=( const uint8_t &right_type_var_ref ) {
	comp_any_type( uint8_t, greaterOrEquThanTarget );
}
bool BaseVarType::operator==( const uint16_t &right_type_var_ref ) {
	comp_any_type( uint16_t, equThanTarget );
}
bool BaseVarType::operator>( const uint16_t &right_type_var_ref ) {
	comp_any_type( uint16_t, greaterThanTarget );
}
bool BaseVarType::operator<( const uint16_t &right_type_var_ref ) {
	comp_any_type( uint16_t, lessThanTarget );
}
bool BaseVarType::operator<=( const uint16_t &right_type_var_ref ) {
	comp_any_type( uint16_t, lessOrEquThanTarget );
}
bool BaseVarType::operator>=( const uint16_t &right_type_var_ref ) {
	comp_any_type( uint16_t, greaterOrEquThanTarget );
}
bool BaseVarType::operator==( const uint32_t &right_type_var_ref ) {
	comp_any_type( uint32_t, equThanTarget );
}
bool BaseVarType::operator>( const uint32_t &right_type_var_ref ) {
	comp_any_type( uint32_t, greaterThanTarget );
}
bool BaseVarType::operator<( const uint32_t &right_type_var_ref ) {
	comp_any_type( uint32_t, lessThanTarget );
}
bool BaseVarType::operator<=( const uint32_t &right_type_var_ref ) {
	comp_any_type( uint32_t, lessOrEquThanTarget );
}
bool BaseVarType::operator>=( const uint32_t &right_type_var_ref ) {
	comp_any_type( uint32_t, greaterOrEquThanTarget );
}
bool BaseVarType::operator==( const uint64_t &right_type_var_ref ) {
	comp_any_type( uint64_t, equThanTarget );
}
bool BaseVarType::operator>( const uint64_t &right_type_var_ref ) {
	comp_any_type( uint64_t, greaterThanTarget );
}
bool BaseVarType::operator<( const uint64_t &right_type_var_ref ) {
	comp_any_type( uint64_t, lessThanTarget );
}
bool BaseVarType::operator<=( const uint64_t &right_type_var_ref ) {
	comp_any_type( uint64_t, lessOrEquThanTarget );
}
bool BaseVarType::operator>=( const uint64_t &right_type_var_ref ) {
	comp_any_type( uint64_t, greaterOrEquThanTarget );
}
bool BaseVarType::operator==( const float &right_type_var_ref ) {
	comp_any_type( float, equThanTarget );
}
bool BaseVarType::operator>( const float &right_type_var_ref ) {
	comp_any_type( float, greaterThanTarget );
}
bool BaseVarType::operator<( const float &right_type_var_ref ) {
	comp_any_type( float, lessThanTarget );
}
bool BaseVarType::operator<=( const float &right_type_var_ref ) {
	comp_any_type( float, lessOrEquThanTarget );
}
bool BaseVarType::operator>=( const float &right_type_var_ref ) {
	comp_any_type( float, greaterOrEquThanTarget );
}
bool BaseVarType::operator==( const double &right_type_var_ref ) {
	comp_any_type( double, equThanTarget );
}
bool BaseVarType::operator>( const double &right_type_var_ref ) {
	comp_any_type( double, greaterThanTarget );
}
bool BaseVarType::operator<( const double &right_type_var_ref ) {
	comp_any_type( double, lessThanTarget );
}
bool BaseVarType::operator<=( const double &right_type_var_ref ) {
	comp_any_type( double, lessOrEquThanTarget );
}
bool BaseVarType::operator>=( const double &right_type_var_ref ) {
	comp_any_type( double, greaterOrEquThanTarget );
}
bool BaseVarType::operator==( const QString &right_type_var_ref ) {
	comp_any_type( QString, equThanTarget );
}
bool BaseVarType::operator>( const QString &right_type_var_ref ) {
	comp_any_type( QString, greaterThanTarget );
}
bool BaseVarType::operator<( const QString &right_type_var_ref ) {
	comp_any_type( QString, lessThanTarget );
}
bool BaseVarType::operator<=( const QString &right_type_var_ref ) {
	comp_any_type( QString, lessOrEquThanTarget );
}
bool BaseVarType::operator>=( const QString &right_type_var_ref ) {
	comp_any_type( QString, greaterOrEquThanTarget );
}

#define Imp_Operator_Calcu( function_name_ , type_info_) \
	I_Type *varTypeInfo = left_type_var_ref.getThisTypeInfoPtr( ); \
	auto varType = VarGenerate::createVarType( *varTypeInfo, varTypeInfo ); \
	if( varType == nullptr ) \
		return VarGenerate::createVarType< NullptrType >( varTypeInfo ); \
	if( VarGenerate::conver( varType, &left_type_var_ref ) ) { \
		I_Type rightTypeInfo( typeid( type_info_ ) ); \
		VarGenerate::function_name_( varType, &rightTypeInfo, &right_type_var_ref ); \
	} \
	return varType

BaseVarType * operator+( const BaseVarType &left_type_var_ref, const int8_t &right_type_var_ref ) {
	Imp_Operator_Calcu( add, int8_t );
}
BaseVarType * operator-( const BaseVarType &left_type_var_ref, const int8_t &right_type_var_ref ) {
	Imp_Operator_Calcu( sub, int8_t );
}
BaseVarType * operator*( const BaseVarType &left_type_var_ref, const int8_t &right_type_var_ref ) {
	Imp_Operator_Calcu( mul, int8_t );
}
BaseVarType * operator/( const BaseVarType &left_type_var_ref, const int8_t &right_type_var_ref ) {
	Imp_Operator_Calcu( div, int8_t );
}
BaseVarType * operator+( const BaseVarType &left_type_var_ref, const int16_t &right_type_var_ref ) {
	Imp_Operator_Calcu( add, int16_t );
}
BaseVarType * operator-( const BaseVarType &left_type_var_ref, const int16_t &right_type_var_ref ) {
	Imp_Operator_Calcu( sub, int16_t );
}
BaseVarType * operator*( const BaseVarType &left_type_var_ref, const int16_t &right_type_var_ref ) {
	Imp_Operator_Calcu( mul, int16_t );
}
BaseVarType * operator/( const BaseVarType &left_type_var_ref, const int16_t &right_type_var_ref ) {
	Imp_Operator_Calcu( div, int16_t );
}
BaseVarType * operator+( const BaseVarType &left_type_var_ref, const int32_t &right_type_var_ref ) {
	Imp_Operator_Calcu( add, int32_t );
}
BaseVarType * operator-( const BaseVarType &left_type_var_ref, const int32_t &right_type_var_ref ) {
	Imp_Operator_Calcu( sub, int32_t );
}
BaseVarType * operator*( const BaseVarType &left_type_var_ref, const int32_t &right_type_var_ref ) {
	Imp_Operator_Calcu( mul, int32_t );
}
BaseVarType * operator/( const BaseVarType &left_type_var_ref, const int32_t &right_type_var_ref ) {
	Imp_Operator_Calcu( div, int32_t );
}
BaseVarType * operator+( const BaseVarType &left_type_var_ref, const int64_t &right_type_var_ref ) {
	Imp_Operator_Calcu( add, int64_t );
}
BaseVarType * operator-( const BaseVarType &left_type_var_ref, const int64_t &right_type_var_ref ) {
	Imp_Operator_Calcu( sub, int64_t );
}
BaseVarType * operator*( const BaseVarType &left_type_var_ref, const int64_t &right_type_var_ref ) {
	Imp_Operator_Calcu( mul, int64_t );
}
BaseVarType * operator/( const BaseVarType &left_type_var_ref, const int64_t &right_type_var_ref ) {
	Imp_Operator_Calcu( div, int64_t );
}
BaseVarType * operator+( const BaseVarType &left_type_var_ref, const uint8_t &right_type_var_ref ) {
	Imp_Operator_Calcu( add, uint8_t );
}
BaseVarType * operator-( const BaseVarType &left_type_var_ref, const uint8_t &right_type_var_ref ) {
	Imp_Operator_Calcu( sub, uint8_t );
}
BaseVarType * operator*( const BaseVarType &left_type_var_ref, const uint8_t &right_type_var_ref ) {
	Imp_Operator_Calcu( mul, uint8_t );
}
BaseVarType * operator/( const BaseVarType &left_type_var_ref, const uint8_t &right_type_var_ref ) {
	Imp_Operator_Calcu( div, uint8_t );
}
BaseVarType * operator+( const BaseVarType &left_type_var_ref, const uint16_t &right_type_var_ref ) {
	Imp_Operator_Calcu( add, uint16_t );
}
BaseVarType * operator-( const BaseVarType &left_type_var_ref, const uint16_t &right_type_var_ref ) {
	Imp_Operator_Calcu( sub, uint16_t );
}
BaseVarType * operator*( const BaseVarType &left_type_var_ref, const uint16_t &right_type_var_ref ) {
	Imp_Operator_Calcu( mul, uint16_t );
}
BaseVarType * operator/( const BaseVarType &left_type_var_ref, const uint16_t &right_type_var_ref ) {
	Imp_Operator_Calcu( div, uint16_t );
}
BaseVarType * operator+( const BaseVarType &left_type_var_ref, const uint32_t &right_type_var_ref ) {
	Imp_Operator_Calcu( add, uint32_t );
}
BaseVarType * operator-( const BaseVarType &left_type_var_ref, const uint32_t &right_type_var_ref ) {
	Imp_Operator_Calcu( sub, uint32_t );
}
BaseVarType * operator*( const BaseVarType &left_type_var_ref, const uint32_t &right_type_var_ref ) {
	Imp_Operator_Calcu( mul, uint32_t );
}
BaseVarType * operator/( const BaseVarType &left_type_var_ref, const uint32_t &right_type_var_ref ) {
	Imp_Operator_Calcu( div, uint32_t );
}
BaseVarType * operator+( const BaseVarType &left_type_var_ref, const uint64_t &right_type_var_ref ) {
	Imp_Operator_Calcu( add, uint64_t );
}
BaseVarType * operator-( const BaseVarType &left_type_var_ref, const uint64_t &right_type_var_ref ) {
	Imp_Operator_Calcu( sub, uint64_t );
}
BaseVarType * operator*( const BaseVarType &left_type_var_ref, const uint64_t &right_type_var_ref ) {
	Imp_Operator_Calcu( mul, uint64_t );
}
BaseVarType * operator/( const BaseVarType &left_type_var_ref, const uint64_t &right_type_var_ref ) {
	Imp_Operator_Calcu( div, uint64_t );
}
BaseVarType * operator+( const BaseVarType &left_type_var_ref, const float &right_type_var_ref ) {
	Imp_Operator_Calcu( add, float );
}
BaseVarType * operator-( const BaseVarType &left_type_var_ref, const float &right_type_var_ref ) {
	Imp_Operator_Calcu( sub, float );
}
BaseVarType * operator*( const BaseVarType &left_type_var_ref, const float &right_type_var_ref ) {
	Imp_Operator_Calcu( mul, float );
}
BaseVarType * operator/( const BaseVarType &left_type_var_ref, const float &right_type_var_ref ) {
	Imp_Operator_Calcu( div, float );
}
BaseVarType * operator+( const BaseVarType &left_type_var_ref, const double &right_type_var_ref ) {
	Imp_Operator_Calcu( add, double );
}
BaseVarType * operator-( const BaseVarType &left_type_var_ref, const double &right_type_var_ref ) {
	Imp_Operator_Calcu( sub, double );
}
BaseVarType * operator*( const BaseVarType &left_type_var_ref, const double &right_type_var_ref ) {
	Imp_Operator_Calcu( mul, double );
}
BaseVarType * operator/( const BaseVarType &left_type_var_ref, const double &right_type_var_ref ) {
	Imp_Operator_Calcu( div, double );
}
BaseVarType * operator+( const BaseVarType &left_type_var_ref, const QString &right_type_var_ref ) {
	Imp_Operator_Calcu( add, QString );
}
BaseVarType * operator-( const BaseVarType &left_type_var_ref, const QString &right_type_var_ref ) {
	Imp_Operator_Calcu( sub, QString );
}
BaseVarType * operator*( const BaseVarType &left_type_var_ref, const QString &right_type_var_ref ) {
	Imp_Operator_Calcu( mul, QString );
}
BaseVarType * operator/( const BaseVarType &left_type_var_ref, const QString &right_type_var_ref ) {
	Imp_Operator_Calcu( div, QString );
}
