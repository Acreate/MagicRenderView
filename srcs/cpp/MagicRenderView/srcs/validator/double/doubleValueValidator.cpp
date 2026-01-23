#include "doubleValueValidator.h"

DoubleValueValidator::DoubleValueValidator( QObject *parent ) : Validator( UINT64_MAX, 0, 10, parent ) {
}
DoubleValueValidator::~DoubleValueValidator( ) {

}
union DoubleBitSizeType {
	double doubleVar;
	uint64_t uint64Var;
	int64_t int64Var;
};
bool DoubleValueValidator::decStringToValidatorString( const QString &normal_dec_text, QString &result_normal_validator_var_txt ) {
	bool isOK;
	DoubleBitSizeType unionType;
	unionType.doubleVar = normal_dec_text.toDouble( &isOK );
	if( isOK ) {
		result_normal_validator_var_txt = QString::number( unionType.doubleVar );
		return true;
	}
	return false;
}
QValidator::State DoubleValueValidator::validate( QString &in_put, int &in_pos ) const {
	bool isOK;
	in_put.toDouble( &isOK );
	if( isOK == false )
		return Invalid;
	return Acceptable;
}
bool DoubleValueValidator::validatorStringToDecString( const QString &normal_validator_var_txt, QString &result_normal_dec_text ) {
	bool isOK;
	DoubleBitSizeType unionType;
	unionType.doubleVar = normal_validator_var_txt.toDouble( &isOK );
	if( isOK ) {
		qsizetype indexOf = normal_validator_var_txt.indexOf( '.' );
		result_normal_dec_text = normal_validator_var_txt.mid( 0, indexOf );
		unionType.doubleVar = normal_validator_var_txt.toDouble( &isOK );
		result_normal_dec_text = QString::number( unionType.doubleVar );
		return true;
	}
	return false;
}
