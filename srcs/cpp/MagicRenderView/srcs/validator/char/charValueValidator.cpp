#include "charValueValidator.h"
CharValueValidator::CharValueValidator( QObject *parent ) : SignedValidator( UINT16_MAX, 0, 10, parent ) {
}
CharValueValidator::~CharValueValidator( ) {

}
bool CharValueValidator::decStringToValidatorString( const QString &normal_dec_text, QString &result_normal_validator_var_txt ) {
	bool isOK;
	auto uLongLong = normal_dec_text.toUShort( &isOK );
	if( isOK == false )
		return false;
	result_normal_validator_var_txt = QChar( uLongLong );
	return true;
}
QValidator::State CharValueValidator::validate( QString &in_put, int &in_pos ) const {
	if( in_put.length( ) < 2 )
		return Acceptable; // 只保留 0 ~ 1 个字符
	return Invalid;
}
bool CharValueValidator::validatorStringToDecString( const QString &normal_validator_var_txt, QString &result_normal_dec_text ) {
	if( normal_validator_var_txt.length( ) == 0 ) {
		result_normal_dec_text = '\0';
		return true;
	}
	QChar firstChar = normal_validator_var_txt.data( )[ 0 ];
	result_normal_dec_text = QString::number( firstChar.unicode( ) );
	return true;
}
