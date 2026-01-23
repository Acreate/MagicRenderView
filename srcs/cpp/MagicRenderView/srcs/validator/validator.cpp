#include "validator.h"

Validator::Validator( uint64_t max_value, uint64_t min_value, uint64_t bin_system, QObject *parent ) : QValidator( parent ), maxValue( max_value ), minValue( min_value ), binSystem( bin_system ) {
	auto maxValueLen = tr( "%1" ).arg( maxValue, 0, binSystem ).length( );
	auto minValueLen = tr( "%1" ).arg( minValue, 0, binSystem ).length( );
	if( maxValueLen > minValueLen )
		maxLen = maxValueLen;
	else
		maxLen = minValueLen;

}
Validator::~Validator( ) {
}
QValidator::State Validator::validate( QString &in_put, int &in_pos ) const {
	if( in_put.isEmpty( ) )
		return Acceptable;
	if( in_put.length( ) > maxLen )
		return Invalid;
	bool isOK;
	auto uLong = in_put.toULongLong( &isOK, binSystem );
	if( isOK == true ) {
		if( uLong > maxValue )
			return Invalid;
		return Acceptable;
	}
	auto converLongLong = in_put.toLongLong( &isOK, binSystem );
	if( isOK == true ) {
		if( converLongLong < minValue )
			return Invalid;
		return Acceptable;
	}
	return Invalid;
}
bool Validator::decStringToValidatorString( const QString &normal_dec_text, QString &result_normal_validator_var_txt ) {
	bool isOK;
	qulonglong uLongLong;
	qlonglong longLong;
	double doubleVar;
	if( normal_dec_text.isEmpty( ) ) {
		result_normal_validator_var_txt = '0';
		return true;
	}
	uLongLong = normal_dec_text.toULongLong( &isOK );
	if( isOK ) {
		if( uLongLong > maxValue )
			uLongLong = maxValue;
		result_normal_validator_var_txt = QString( "%1" ).arg( uLongLong, 0, binSystem );
		return true;
	}
	longLong = normal_dec_text.toLongLong( &isOK );
	if( isOK ) {
		if( longLong > maxValue )
			longLong = maxValue;
		else if( longLong < minValue )
			longLong = minValue;
		result_normal_validator_var_txt = QString( "%1" ).arg( longLong, 0, binSystem );
		return true;
	}
	doubleVar = normal_dec_text.toDouble( &isOK );
	if( isOK ) {
		if( doubleVar > maxValue )
			doubleVar = maxValue;
		else if( doubleVar < minValue )
			doubleVar = minValue;
		result_normal_validator_var_txt = QString( "%1" ).arg( doubleVar, 0, binSystem );
		return true;
	}

	return false;
}
bool Validator::validatorStringToDecString( const QString &normal_validator_var_txt, QString &result_normal_dec_text ) {
	bool isOK;
	qulonglong uLongLong;
	qlonglong longLong;
	double doubleVar;
	if( normal_validator_var_txt.isEmpty( ) == true ) {
		result_normal_dec_text = QString::number( 0 );
		return true;
	}
	uLongLong = normal_validator_var_txt.toULongLong( &isOK, binSystem );
	if( isOK ) {
		if( uLongLong > maxValue )
			uLongLong = maxValue;
		result_normal_dec_text = QString::number( uLongLong );
		return true;
	}
	longLong = normal_validator_var_txt.toLongLong( &isOK, binSystem );
	if( isOK ) {
		if( longLong > maxValue )
			longLong = maxValue;
		else if( longLong < minValue )
			longLong = minValue;
		result_normal_dec_text = QString::number( longLong );
		return true;
	}
	doubleVar = normal_validator_var_txt.toDouble( &isOK );
	if( isOK ) {
		if( doubleVar > maxValue )
			doubleVar = maxValue;
		else if( doubleVar < minValue )
			doubleVar = minValue;
		result_normal_dec_text = QString::number( doubleVar );
		return true;
	}
	return false;
}
