#include "stringValueValidator.h"

StringValueValidator::StringValueValidator( QObject *parent ) : Validator( UINT64_MAX, 0, 10, parent ) {
}
StringValueValidator::~StringValueValidator( ) {

}
union DoubleBitSizeType {
	double doubleVar;
	uint64_t uint64Var;
	int64_t int64Var;
};
bool StringValueValidator::decStringToValidatorString( const QString &normal_dec_text, QString &result_normal_validator_var_txt ) {
	bool isOK;
	DoubleBitSizeType unionType;
	unionType.uint64Var = normal_dec_text.toULongLong( &isOK );
	if( isOK ) {
		result_normal_validator_var_txt = QString::number( unionType.uint64Var );
		return true;
	}
	unionType.int64Var = normal_dec_text.toLongLong( &isOK );
	if( isOK ) {
		result_normal_validator_var_txt = QString::number( unionType.int64Var );
		return true;
	}
	unionType.doubleVar = normal_dec_text.toDouble( &isOK );
	if( isOK ) {
		result_normal_validator_var_txt = QString::number( unionType.doubleVar );
		return true;
	}
	return false;
}
QValidator::State StringValueValidator::validate( QString &in_put, int &in_pos ) const {
	return Acceptable; // 字符串没有禁止
}
bool StringValueValidator::validatorStringToDecString( const QString &normal_validator_var_txt, QString &result_normal_dec_text ) {
	bool isOK;
	DoubleBitSizeType unionType;
	unionType.uint64Var = normal_validator_var_txt.toULongLong( &isOK );
	if( isOK ) {
		result_normal_dec_text = QString::number( unionType.uint64Var );
		return true;
	}
	unionType.int64Var = normal_validator_var_txt.toLongLong( &isOK );
	if( isOK ) {
		result_normal_dec_text = QString::number( unionType.int64Var );
		return true;
	}
	unionType.doubleVar = normal_validator_var_txt.toDouble( &isOK );
	if( isOK ) {
		result_normal_dec_text = QString::number( unionType.doubleVar );
		return true;
	}
	return false;
}
void StringValueValidator::fixup( QString &result_change_text ) const {
	Validator::fixup( result_change_text ); // 或许可以修改一个禁止语句
}
