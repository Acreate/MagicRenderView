#include "signedValidator.h"
SignedValidator::SignedValidator( uint64_t max_value, uint64_t min_value, uint64_t bin_system, QObject *parent ) : Validator( max_value, min_value, bin_system, parent ) { }
SignedValidator::~SignedValidator( ) {
}

QValidator::State SignedValidator::validate( QString &in_put, int &in_pos ) const {
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
bool SignedValidator::decStringToValidatorString( const QString &normal_dec_text, QString &result_normal_validator_var_txt ) {
	bool isOK;
	Type64Bit type64BitVar;
	if( normal_dec_text.isEmpty( ) ) {
		result_normal_validator_var_txt = '0';
		return true;
	}
	type64BitVar.int64TypeVar = normal_dec_text.toLongLong( &isOK );
	if( isOK ) {
		result_normal_validator_var_txt = QString( "%1" ).arg( type64BitVar.int64TypeVar, 0, binSystem );
		return true;
	}
	type64BitVar.uint64TypeVar = normal_dec_text.toULongLong( &isOK );
	if( isOK ) {
		result_normal_validator_var_txt = QString( "%1" ).arg( type64BitVar.uint64TypeVar, 0, binSystem );
		return true;
	}
	type64BitVar.doubleTypeVar = normal_dec_text.toDouble( &isOK );
	if( isOK ) {
		result_normal_validator_var_txt = QString( "%1" ).arg( type64BitVar.doubleTypeVar, 0, binSystem );
		return true;
	}

	return false;
}
bool SignedValidator::validatorStringToDecString( const QString &normal_validator_var_txt, QString &result_normal_dec_text ) {
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
