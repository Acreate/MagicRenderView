#include "baseVarType.h"
#include "I_Type.h"
#include "../generate/varGenerate.h"

I_Type * BaseVarType::initTypeInfo( ) {
	const type_info &typeInfo = typeid( *this );
	I_Type *px = new I_Type( typeInfo );
	objTypeInfo.reset( px );
	return px;
}
BaseVarType::BaseVarType( ) : BaseVarType( nullptr ) {
}
BaseVarType::BaseVarType( QObject *parent ) : BaseVarType( parent, std_shared_ptr< I_Type >( new I_Type( typeid( nullptr ) ) ) ) {
}

BaseVarType::BaseVarType( const BaseVarType &other ) : QObject { other.parent( ) } {
	varTypeInfo = other.varTypeInfo;
}
BaseVarType::BaseVarType( QObject *parent, const std_shared_ptr< I_Type > &var_type_info ) : QObject( parent ),
	varTypeInfo( var_type_info ) {
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
}

const I_Type & BaseVarType::getVarTypeInfo( ) const {
	return *varTypeInfo.get( );
}
const I_Type & BaseVarType::getThisTypeInfo( ) const {
	return *objTypeInfo.get( );
}

BaseVarType * operator+( const BaseVarType &left_type_var_ref, const BaseVarType *right_type_var_ref ) {
	I_Type parent = left_type_var_ref.getThisTypeInfo( );
	BaseVarType *result = VarGenerate::createVarType( parent );
	if( result == nullptr )
		return nullptr;
	
	I_Type dataType = result->getVarTypeInfo(  );
	if( VarGenerate::conver( result, &dataType, left_type_var_ref.getVarPtr( ) ) == false ) {
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
	I_Type parent = left_type_var_ref.getThisTypeInfo( );
	BaseVarType *result = VarGenerate::createVarType( parent );
	if( result == nullptr )
		return nullptr;
	I_Type dataType = result->getVarTypeInfo(  );
	if( VarGenerate::conver( result, &dataType, left_type_var_ref.getVarPtr( ) ) == false ) {
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
	I_Type parent = left_type_var_ref.getThisTypeInfo( );
	BaseVarType *result = VarGenerate::createVarType( parent );
	if( result == nullptr )
		return nullptr;
	I_Type dataType = result->getVarTypeInfo(  );
	if( VarGenerate::conver( result, &dataType, left_type_var_ref.getVarPtr( ) ) == false ) {
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
	I_Type parent = left_type_var_ref.getThisTypeInfo( );
	BaseVarType *result = VarGenerate::createVarType( parent );
	if( result == nullptr )
		return nullptr;
	I_Type dataType = result->getVarTypeInfo(  );
	if( VarGenerate::conver( result, &dataType, left_type_var_ref.getVarPtr( ) ) == false ) {
		delete result;
		return nullptr;
	}
	if( VarGenerate::dev( result, right_type_var_ref ) == false ) {
		delete result;
		return nullptr;
	}
	return result;
}
BaseVarType * BaseVarType::operator=( const BaseVarType &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto &rightTypeInfo = right_type_var_ref.getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto right = right_type_var_ref.getVarPtr( );
	VarGenerate::conver( &leftTypeInfo, left, &rightTypeInfo, right );
	return this;
}
BaseVarType * BaseVarType::operator=( const int8_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto rightTypeInfo = I_Type( typeid( int8_t ) );
	auto left = this->getVarPtr( );
	auto right = &right_type_var_ref;
	VarGenerate::conver( &leftTypeInfo, left, &rightTypeInfo, right );
	return this;
}
BaseVarType * BaseVarType::operator=( const int16_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto rightTypeInfo = I_Type( typeid( int16_t ) );
	auto left = this->getVarPtr( );
	auto right = &right_type_var_ref;
	VarGenerate::conver( &leftTypeInfo, left, &rightTypeInfo, right );
	return this;
}

BaseVarType * BaseVarType::operator=( const int32_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto rightTypeInfo = I_Type( typeid( int32_t ) );
	auto left = this->getVarPtr( );
	auto right = &right_type_var_ref;
	VarGenerate::conver( &leftTypeInfo, left, &rightTypeInfo, right );
	return this;
}
BaseVarType * BaseVarType::operator=( const int64_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto rightTypeInfo = I_Type( typeid( int64_t ) );
	auto left = this->getVarPtr( );
	auto right = &right_type_var_ref;
	VarGenerate::conver( &leftTypeInfo, left, &rightTypeInfo, right );
	return this;
}
BaseVarType * BaseVarType::operator=( const float &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto rightTypeInfo = I_Type( typeid( float ) );
	auto left = this->getVarPtr( );
	auto right = &right_type_var_ref;
	VarGenerate::conver( &leftTypeInfo, left, &rightTypeInfo, right );
	return this;
}
BaseVarType * BaseVarType::operator=( const double &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto rightTypeInfo = I_Type( typeid( double ) );
	auto left = this->getVarPtr( );
	auto right = &right_type_var_ref;
	VarGenerate::conver( &leftTypeInfo, left, &rightTypeInfo, right );
	return this;
}
BaseVarType * BaseVarType::operator=( const QString &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( QString ) );
	auto right = &right_type_var_ref;
	VarGenerate::conver( &leftTypeInfo, left, &rightTypeInfo, right );
	return this;
}
BaseVarType * BaseVarType::operator=( const uint8_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( uint8_t ) );
	auto right = &right_type_var_ref;
	VarGenerate::conver( &leftTypeInfo, left, &rightTypeInfo, right );
	return this;
}
BaseVarType * BaseVarType::operator=( const uint16_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( uint16_t ) );
	auto right = &right_type_var_ref;
	VarGenerate::conver( &leftTypeInfo, left, &rightTypeInfo, right );
	return this;
}
BaseVarType * BaseVarType::operator=( const uint32_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( uint32_t ) );
	auto right = &right_type_var_ref;
	VarGenerate::conver( &leftTypeInfo, left, &rightTypeInfo, right );
	return this;
}
BaseVarType * BaseVarType::operator=( const uint64_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( uint64_t ) );
	auto right = &right_type_var_ref;
	VarGenerate::conver( &leftTypeInfo, left, &rightTypeInfo, right );
	return this;
}
bool BaseVarType::operator==( const BaseVarType &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto &rightTypeInfo = right_type_var_ref.getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto right = right_type_var_ref.getVarPtr( );
	bool result = false;
	VarGenerate::equThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator>( const BaseVarType &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto &rightTypeInfo = right_type_var_ref.getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto right = right_type_var_ref.getVarPtr( );
	bool result = false;
	VarGenerate::greaterThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator<( const BaseVarType &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto &rightTypeInfo = right_type_var_ref.getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto right = right_type_var_ref.getVarPtr( );
	bool result = false;
	VarGenerate::lessThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator<=( const BaseVarType &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto &rightTypeInfo = right_type_var_ref.getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto right = right_type_var_ref.getVarPtr( );
	bool result = false;
	VarGenerate::lessOrEquThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator>=( const BaseVarType &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto &rightTypeInfo = right_type_var_ref.getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto right = right_type_var_ref.getVarPtr( );
	bool result = false;
	VarGenerate::greaterOrEquThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator==( const int8_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( int8_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::equThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator>( const int8_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( int8_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::greaterThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator<( const int8_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( int8_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::lessThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator<=( const int8_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( int8_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::lessOrEquThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator>=( const int8_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( int8_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::greaterOrEquThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator==( const int16_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( int16_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::equThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator>( const int16_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( int16_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::greaterThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator<( const int16_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( int16_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::lessThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator<=( const int16_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( int16_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::lessOrEquThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator>=( const int16_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( int16_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::greaterOrEquThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator==( const int32_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( int32_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::equThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator>( const int32_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( int32_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::greaterThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator<( const int32_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( int32_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::lessThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator<=( const int32_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( int32_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::lessOrEquThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator>=( const int32_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( int32_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::greaterOrEquThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator==( const int64_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( int64_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::equThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator>( const int64_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( int64_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::greaterThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator<( const int64_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( int64_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::lessThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator<=( const int64_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( int64_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::lessOrEquThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator>=( const int64_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( int64_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::greaterOrEquThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator==( const uint8_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( uint8_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::equThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator>( const uint8_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( uint8_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::greaterThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator<( const uint8_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( uint8_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::lessThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator<=( const uint8_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( uint8_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::lessOrEquThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator>=( const uint8_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( uint8_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::greaterOrEquThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator==( const uint16_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( uint16_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::equThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator>( const uint16_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( uint16_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::greaterThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator<( const uint16_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( uint16_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::lessThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator<=( const uint16_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( uint16_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::lessOrEquThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator>=( const uint16_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( uint16_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::greaterOrEquThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator==( const uint32_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( uint32_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::equThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator>( const uint32_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( uint32_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::greaterThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator<( const uint32_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( uint32_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::lessThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator<=( const uint32_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( uint32_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::lessOrEquThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator>=( const uint32_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( uint32_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::greaterOrEquThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator==( const uint64_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( uint64_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::equThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator>( const uint64_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( uint64_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::greaterThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator<( const uint64_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( uint64_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::lessThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator<=( const uint64_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( uint64_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::lessOrEquThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator>=( const uint64_t &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( uint64_t ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::greaterOrEquThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator==( const float &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( float ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::equThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator>( const float &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( float ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::greaterThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator<( const float &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( float ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::lessThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator<=( const float &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( float ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::lessOrEquThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator>=( const float &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( float ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::greaterOrEquThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator==( const double &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( double ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::equThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator>( const double &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( double ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::greaterThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator<( const double &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( double ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::lessThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator<=( const double &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( double ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::lessOrEquThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator>=( const double &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( double ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::greaterOrEquThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator==( const QString &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( QString ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::equThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator>( const QString &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( QString ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::greaterThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator<( const QString &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( QString ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::lessThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator<=( const QString &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( QString ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::lessOrEquThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
bool BaseVarType::operator>=( const QString &right_type_var_ref ) {
	auto &leftTypeInfo = this->getVarTypeInfo( );
	auto left = this->getVarPtr( );
	auto rightTypeInfo = I_Type( typeid( QString ) );
	auto right = &right_type_var_ref;
	bool result = false;
	VarGenerate::greaterOrEquThanTarget( &leftTypeInfo, left, &rightTypeInfo, right, &result );
	return result;
}
BaseVarType operator+( BaseVarType &left_type_var_ref, const int8_t &right_type_var_ref ) {
}
BaseVarType operator-( BaseVarType &left_type_var_ref, const int8_t &right_type_var_ref ) {
}
BaseVarType operator*( BaseVarType &left_type_var_ref, const int8_t &right_type_var_ref ) {
}
BaseVarType operator/( BaseVarType &left_type_var_ref, const int8_t &right_type_var_ref ) {
}
BaseVarType operator+( BaseVarType &left_type_var_ref, const int16_t &right_type_var_ref ) {
}
BaseVarType operator-( BaseVarType &left_type_var_ref, const int16_t &right_type_var_ref ) {
}
BaseVarType operator*( BaseVarType &left_type_var_ref, const int16_t &right_type_var_ref ) {
}
BaseVarType operator/( BaseVarType &left_type_var_ref, const int16_t &right_type_var_ref ) {
}
BaseVarType operator+( BaseVarType &left_type_var_ref, const int32_t &right_type_var_ref ) {
}
BaseVarType operator-( BaseVarType &left_type_var_ref, const int32_t &right_type_var_ref ) {
}
BaseVarType operator*( BaseVarType &left_type_var_ref, const int32_t &right_type_var_ref ) {
}
BaseVarType operator/( BaseVarType &left_type_var_ref, const int32_t &right_type_var_ref ) {
}
BaseVarType operator+( BaseVarType &left_type_var_ref, const int64_t &right_type_var_ref ) {
}
BaseVarType operator-( BaseVarType &left_type_var_ref, const int64_t &right_type_var_ref ) {
}
BaseVarType operator*( BaseVarType &left_type_var_ref, const int64_t &right_type_var_ref ) {
}
BaseVarType operator/( BaseVarType &left_type_var_ref, const int64_t &right_type_var_ref ) {
}
BaseVarType operator+( BaseVarType &left_type_var_ref, const uint8_t &right_type_var_ref ) {
}
BaseVarType operator-( BaseVarType &left_type_var_ref, const uint8_t &right_type_var_ref ) {
}
BaseVarType operator*( BaseVarType &left_type_var_ref, const uint8_t &right_type_var_ref ) {
}
BaseVarType operator/( BaseVarType &left_type_var_ref, const uint8_t &right_type_var_ref ) {
}
BaseVarType operator+( BaseVarType &left_type_var_ref, const uint16_t &right_type_var_ref ) {
}
BaseVarType operator-( BaseVarType &left_type_var_ref, const uint16_t &right_type_var_ref ) {
}
BaseVarType operator*( BaseVarType &left_type_var_ref, const uint16_t &right_type_var_ref ) {
}
BaseVarType operator/( BaseVarType &left_type_var_ref, const uint16_t &right_type_var_ref ) {
}
BaseVarType operator+( BaseVarType &left_type_var_ref, const uint32_t &right_type_var_ref ) {
}
BaseVarType operator-( BaseVarType &left_type_var_ref, const uint32_t &right_type_var_ref ) {
}
BaseVarType operator*( BaseVarType &left_type_var_ref, const uint32_t &right_type_var_ref ) {
}
BaseVarType operator/( BaseVarType &left_type_var_ref, const uint32_t &right_type_var_ref ) {
}
BaseVarType operator+( BaseVarType &left_type_var_ref, const uint64_t &right_type_var_ref ) {
}
BaseVarType operator-( BaseVarType &left_type_var_ref, const uint64_t &right_type_var_ref ) {
}
BaseVarType operator*( BaseVarType &left_type_var_ref, const uint64_t &right_type_var_ref ) {
}
BaseVarType operator/( BaseVarType &left_type_var_ref, const uint64_t &right_type_var_ref ) {
}
BaseVarType operator+( BaseVarType &left_type_var_ref, const float &right_type_var_ref ) {
}
BaseVarType operator-( BaseVarType &left_type_var_ref, const float &right_type_var_ref ) {
}
BaseVarType operator*( BaseVarType &left_type_var_ref, const float &right_type_var_ref ) {
}
BaseVarType operator/( BaseVarType &left_type_var_ref, const float &right_type_var_ref ) {
}
BaseVarType operator+( BaseVarType &left_type_var_ref, const double &right_type_var_ref ) {
}
BaseVarType operator-( BaseVarType &left_type_var_ref, const double &right_type_var_ref ) {
}
BaseVarType operator*( BaseVarType &left_type_var_ref, const double &right_type_var_ref ) {
}
BaseVarType operator/( BaseVarType &left_type_var_ref, const double &right_type_var_ref ) {
}
BaseVarType operator+( BaseVarType &left_type_var_ref, const QString &right_type_var_ref ) {
}
BaseVarType operator-( BaseVarType &left_type_var_ref, const QString &right_type_var_ref ) {
}
BaseVarType operator*( BaseVarType &left_type_var_ref, const QString &right_type_var_ref ) {
}
BaseVarType operator/( BaseVarType &left_type_var_ref, const QString &right_type_var_ref ) {
}
