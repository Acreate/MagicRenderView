#include "validator.h"

Validator::Validator( uint64_t max_value, uint64_t bin_system, QObject *parent ) : QValidator( parent ), maxValue( max_value ), binSystem( bin_system ) {
	maxLen = tr( "%1" ).arg( maxValue, 0, binSystem ).length( );
}
Validator::~Validator( ) {
}
QValidator::State Validator::validate( QString &in_put, int &in_pos ) const {
	if( in_put.isEmpty( ) )
		return Acceptable;
	if( in_put.length( ) > maxLen )
		return Invalid;
	bool isOK;
	ulong uLong = in_put.toULong( &isOK, binSystem );
	if( isOK == false || uLong > maxValue )
		return Invalid;
	return Acceptable;
}
bool Validator::decStringToValidatorString( const QString &normal_dec_text, QString &result_normal_validator_var_txt ) {
	bool isOK;
	qulonglong uLongLong;
	qlonglong longLong;
	double doubleVar;
	uLongLong = normal_dec_text.toULongLong( &isOK );
	if( isOK ) {
		result_normal_validator_var_txt = QString( "%1" ).arg( uLongLong, 0, binSystem );
		return true;
	}
	longLong = normal_dec_text.toLongLong( &isOK );
	if( isOK ) {
		result_normal_validator_var_txt = QString( "%1" ).arg( longLong, 0, binSystem );
		return true;
	}
	doubleVar = normal_dec_text.toDouble( &isOK );
	if( isOK ) {
		result_normal_validator_var_txt = QString( "%1" ).arg( doubleVar, 0, binSystem );
		return true;
	}

	return false;
}
bool Validator::validatorStringToDecString( const QString &normal_validator_var_txt, QString &result_normal_dec_text ) {
	bool isOK;
	ulong uLong = normal_validator_var_txt.toULong( &isOK, binSystem );
	if( isOK == false )
		return false;
	result_normal_dec_text = QString::number( uLong );
	return true;
}
