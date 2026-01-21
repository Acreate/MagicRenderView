#include "validator.h"

#include "../app/application.h"
#include "../director/printerDirector.h"
#include "../srack/srackInfo.h"

bool Validator::normalInput( QString &input, int &pos ) const {
	uint64_t abs;
	if( isUnSign == false ) {
		abs = std::abs( value->int64Value );
		if( value->int64Value < 0 )
			input = tr( "-%1" ).arg( abs, maxLen, binSystem, '0' );
		else
			input = tr( "%1" ).arg( abs, maxLen, binSystem, '0' );

		return true;
	}
	input = tr( "%1" ).arg( value->uint64Value, maxLen, binSystem, '0' );

	return true;
}
bool Validator::normalInputLen( QString &input, int &pos ) const {
	auto len = input.size( );
	auto appendCount = maxLen;
	if( isUnSign == false && value->int64Value < 0 )
		appendCount += 1;
	if( len > appendCount ) {
		len = len - appendCount;
		input = input.mid( len, appendCount );
		if( pos > appendCount )
			pos = appendCount;
	}
	return true;
}
Validator::Validator( uint64_t max_value, uint64_t bin_system, bool is_un_sign, QObject *parent ) : QValidator( parent ), maxValue( max_value ), binSystem( bin_system ), isUnSign( is_un_sign ) {
	value = new Value;
	maxLen = tr( "%1" ).arg( max_value, 0, bin_system ).length( );
}
Validator::~Validator( ) {
	delete value;
}
bool Validator::toUInt64( const QString &conver_text, uint64_t &result_uint64_value ) const {
	bool result;
	result_uint64_value = conver_text.toULongLong( &result, binSystem );
	if( result == false )
		result_uint64_value = 0;
	if( result_uint64_value > maxValue )
		result_uint64_value = maxValue;
	return result;
}
bool Validator::toInt64( const QString &conver_text, int64_t &result_uint64_value ) const {
	bool result;
	result_uint64_value = conver_text.toLongLong( &result, binSystem );
	if( result == false )
		result_uint64_value = 0;
	auto absVar = std::abs( result_uint64_value );
	if( absVar > maxValue )
		absVar = maxValue;
	if( result_uint64_value < 0 )
		result_uint64_value = -absVar;
	return result;
}
bool Validator::varToString( const int64_t &var, QString &result_conver_string ) const {
	uint64_t abs;
	if( var < 0 ) {
		abs = std::abs( var );
		result_conver_string = tr( "-%1" ).arg( abs, 0, binSystem );
		return true;
	}
	result_conver_string = tr( "%1" ).arg( var, 0, binSystem );
	return true;
}
bool Validator::varToString( const uint64_t &var, QString &result_conver_string ) const {
	result_conver_string = tr( "%1" ).arg( var, 0, binSystem );
	return true;
}
bool Validator::checkCharSignValidator( QChar &check_char ) const {

	if( check_char >= '0' || check_char <= '9' )
		return false;
	if( check_char == '+' || check_char == '-' )
		return true;
	return false;
}
bool Validator::chenckAllInput( QChar *input, qsizetype check_len, qsizetype &result_index ) const {
	result_index = 0;
	if( isUnSign == false ) {
		if( checkCharSignValidator( input[ result_index ] ) == false )
			return false;
		for( result_index += 1; result_index < check_len; ++result_index )
			if( checkCharValidator( input[ result_index ] ) == false )
				return false;
	} else
		for( ; result_index < check_len; ++result_index )
			if( checkCharValidator( input[ result_index ] ) == false )
				return false;
	return true;
}
QValidator::State Validator::validate( QString &input, int &pos ) const {
	qsizetype buffIndex;
	QChar *data;
	qsizetype length = input.length( );
	data = input.data( );
	if( length > maxLen ) {
		if( isUnSign == false ) {
			if( checkCharSignValidator( data[ 0 ] ) == false )
				return Invalid;
		} else
			return Invalid;
	}
	if( chenckAllInput( data, length, buffIndex ) == true ) {
		// 输入正确，校验类型转换
		if( isUnSign ) {
			toUInt64( input, value->uint64Value );
			varToString( value->uint64Value, input );
		} else {
			toInt64( input, value->int64Value );
			varToString( value->int64Value, input );
		}
		return Acceptable;
	}
	return Invalid;
}
