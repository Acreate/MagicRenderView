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
	bool isOK = false;
	qsizetype count = in_put.size( );
	if( count == 0 )
		return Acceptable;
	auto data = in_put.data( );
	qsizetype index = 0;
	for( ; index < count; ++index )
		if( data[ index ] == 'e' || data[ index ] == 'E' ) {
			isOK = true;
			++index;
			if( index == count )
				return Acceptable; // 如果末尾是 e，则返回字符串成立
			if( data[ index ] != '-' )
				return Invalid;
			++index;
			if( index == count )
				return Acceptable; // 如果末尾是 e，则返回字符串成立
			for( ; index < count; ++index )
				if( data[ index ] < '0' || data[ index ] > '9' )
					return Invalid; // 如果存在一次 e，则判断后续是否为非数字，如果非数字，则字符串不合格
			break;
		}
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
