#include "charValueValidator.h"
CharValueValidator::CharValueValidator( QObject *parent ) : SignedValidator( UINT64_MAX, 0, 10, parent ) {
}
CharValueValidator::~CharValueValidator( ) {

}

union Type64Bin {
	uint64_t uint64;
	int64_t int64;
	double doubleValue;
};

bool CharValueValidator::decStringToValidatorString( const QString &normal_dec_text, QString &result_normal_validator_var_txt ) {
	bool isOK;
	Type64Bin converVar;
	short code;
	converVar.uint64 = normal_dec_text.toULongLong( &isOK );
	if( isOK == true ) {
		code = converVar.uint64;
		result_normal_validator_var_txt = QChar( code );
	}
	converVar.int64 = normal_dec_text.toLongLong( &isOK );
	if( isOK == true ) {
		code = converVar.int64;
		result_normal_validator_var_txt = QChar( code );
	}
	converVar.doubleValue = normal_dec_text.toDouble( &isOK );
	if( isOK == true ) {
		code = converVar.doubleValue;
		result_normal_validator_var_txt = QChar( code );
	}

	return false;
}
QValidator::State CharValueValidator::validate( QString &in_put, int &in_pos ) const {
	return Acceptable; // 不进行鉴定
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
