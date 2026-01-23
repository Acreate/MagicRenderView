#include "unSignedValidator.h"
UnSignedValidator::UnSignedValidator( uint64_t max_value, uint64_t min_value, uint64_t bin_system, QObject *parent ) : Validator( max_value, min_value, bin_system, parent ) { }
UnSignedValidator::~UnSignedValidator( ) {
}

QValidator::State UnSignedValidator::validate( QString &in_put, int &in_pos ) const {
	bool isOK = in_put.isEmpty( );
	if( isOK )
		return Acceptable;
	qint64 length = in_put.length( );
	qulonglong converLongLong;
	if( length > maxLen )
		return Invalid;
	// 不带符号
	converLongLong = in_put.toULongLong( &isOK, binSystem );
	if( isOK == true ) {
		if( converLongLong < minValue )
			return Invalid;
		if( converLongLong > maxValue )
			return Invalid;
		return Acceptable;
	}
	return Invalid;
}
bool UnSignedValidator::decStringToValidatorString( const QString &normal_dec_text, QString &result_normal_validator_var_txt ) {
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
bool UnSignedValidator::validatorStringToDecString( const QString &normal_validator_var_txt, QString &result_normal_dec_text ) {
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
