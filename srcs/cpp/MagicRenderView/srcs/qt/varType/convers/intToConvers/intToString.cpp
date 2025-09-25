#include "./intToString.h"

#include <QList>
#include <QString>
#include <cstdint>

#include "../../I_Type.h"
bool IntToString::fillTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	auto leftTypeVar = isType< QString >( left_type_info, left );
	if( leftTypeVar == nullptr )
		return false;
	auto call = [leftTypeVar] ( auto *var ) {
		*leftTypeVar = QString::number( *var );
		return true;
	};
	bool isOk = typeCall< int8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;

	isOk = typeCall< double >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< float >( right_type_info, right, call );
	if( isOk )
		return true;
	return false;
}
bool IntToString::addTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	auto leftTypeVar = isType< QString >( left_type_info, left );
	if( leftTypeVar == nullptr )
		return false;
	auto call = [leftTypeVar] ( auto *var ) {
		*leftTypeVar += QString::number( *var );
		return true;
	};
	bool isOk = typeCall< int8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;

	isOk = typeCall< double >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< float >( right_type_info, right, call );
	if( isOk )
		return true;
	return false;
}
bool IntToString::subTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	auto leftTypeVar = isType< QString >( left_type_info, left );
	if( leftTypeVar == nullptr )
		return false;

	auto call = [leftTypeVar] ( auto *var ) {
		QString number = QString::number( *var );
		if( leftTypeVar->endsWith( number ) == false )
			return true;
		*leftTypeVar = leftTypeVar->mid( 0, leftTypeVar->size( ) - number.size( ) );
		return true;
	};
	bool isOk = typeCall< int8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;

	isOk = typeCall< double >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< float >( right_type_info, right, call );
	if( isOk )
		return true;
	return false;
}
bool IntToString::mulTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	auto leftTypeVar = isType< QString >( left_type_info, left );
	if( leftTypeVar == nullptr )
		return false;

	auto call = [leftTypeVar] ( auto *var ) {
		size_t count = *var, index = 0;
		QStringList buff;
		for( ; index < count; ++index )
			buff.append( *leftTypeVar );
		*leftTypeVar = buff.join( "" );
		return true;
	};
	bool isOk = typeCall< int8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;

	isOk = typeCall< double >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< float >( right_type_info, right, call );
	if( isOk )
		return true;
	return false;
}
bool IntToString::divTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right ) {

	auto leftTypeVar = isType< QString >( left_type_info, left );
	if( leftTypeVar == nullptr )
		return false;

	auto call = [leftTypeVar] ( auto *var ) {
		qsizetype count = leftTypeVar->size( );
		size_t var1 = count / *var;
		size_t index = 0;
		QStringList buff;
		for( ; index < count; ++index )
			buff.append( leftTypeVar->mid( index * var1, ( index + 1 ) * var1 ) );
		*leftTypeVar = buff.join( "" );
		return true;
	};
	bool isOk = typeCall< int8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;

	isOk = typeCall< double >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< float >( right_type_info, right, call );
	if( isOk )
		return true;
	return false;
}
bool IntToString::equThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {

	auto leftTypeVar = isType< QString >( left_type_info, left );
	if( leftTypeVar == nullptr )
		return false;

	double doubleVar = leftTypeVar->toDouble( result_bool );
	if( *result_bool == false )
		return false;
	auto call = [doubleVar, result_bool] ( auto *var ) {
		*result_bool = doubleVar == *var;
		return true;
	};
	bool isOk = typeCall< int8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< double >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< float >( right_type_info, right, call );
	if( isOk )
		return true;

	return false;
}
bool IntToString::greaterOrEquThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {

	auto leftTypeVar = isType< QString >( left_type_info, left );
	if( leftTypeVar == nullptr )
		return false;

	double doubleVar = leftTypeVar->toDouble( result_bool );
	if( *result_bool == false )
		return false;
	auto call = [doubleVar, result_bool] ( auto *var ) {
		*result_bool = doubleVar >= *var;
		return true;
	};
	bool isOk = typeCall< int8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;

	isOk = typeCall< double >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< float >( right_type_info, right, call );
	if( isOk )
		return true;
	return false;
}
bool IntToString::greaterThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {

	auto leftTypeVar = isType< QString >( left_type_info, left );
	if( leftTypeVar == nullptr )
		return false;

	double doubleVar = leftTypeVar->toDouble( result_bool );
	if( *result_bool == false )
		return false;
	auto call = [doubleVar, result_bool] ( auto *var ) {
		*result_bool = doubleVar > *var;
		return true;
	};
	bool isOk = typeCall< int8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;

	isOk = typeCall< double >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< float >( right_type_info, right, call );
	if( isOk )
		return true;
	return false;
}
bool IntToString::lessOrEquThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {

	auto leftTypeVar = isType< QString >( left_type_info, left );
	if( leftTypeVar == nullptr )
		return false;

	double doubleVar = leftTypeVar->toDouble( result_bool );
	if( *result_bool == false )
		return false;
	auto call = [doubleVar, result_bool] ( auto *var ) {
		*result_bool = doubleVar <= *var;
		return true;
	};
	bool isOk = typeCall< int8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;

	isOk = typeCall< double >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< float >( right_type_info, right, call );
	if( isOk )
		return true;
	return false;
}
bool IntToString::lessThanTarget( const I_Type *left_type_info, void *left, const I_Type *right_type_info, const void *right, bool *result_bool ) {

	auto leftTypeVar = isType< QString >( left_type_info, left );
	if( leftTypeVar == nullptr )
		return false;

	double doubleVar = leftTypeVar->toDouble( result_bool );
	if( *result_bool == false )
		return false;
	auto call = [doubleVar, result_bool] ( auto *var ) {
		*result_bool = doubleVar < *var;
		return true;
	};
	bool isOk = typeCall< int8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< int64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint8_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint16_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint32_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< uint64_t >( right_type_info, right, call );
	if( isOk )
		return true;

	isOk = typeCall< double >( right_type_info, right, call );
	if( isOk )
		return true;
	isOk = typeCall< float >( right_type_info, right, call );
	if( isOk )
		return true;
	return false;
}
