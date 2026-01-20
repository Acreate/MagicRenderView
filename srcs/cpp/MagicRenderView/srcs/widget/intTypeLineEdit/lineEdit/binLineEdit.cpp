#include "binLineEdit.h"
#include <validator/binValidator.h>
BinLineEdit::BinLineEdit( uint64_t value, QWidget *parent ) : NumberVarLineEdit( value, parent ) {
	BinValidator *binValidator = new BinValidator( value, this );
	base = 2;
	setValidator( binValidator );
	qint64 maxLen = binValidator->getMaxLen( );
	setMaxLength( maxLen );
}
bool BinLineEdit::toInt64( const QString &conver_text, int64_t &result_value ) const {

	bool isOk;
	result_value = conver_text.toLongLong( &isOk, base );
	return isOk;
}
bool BinLineEdit::toUInt64( const QString &conver_text, uint64_t &result_value ) const {

	bool isOk;
	result_value = conver_text.toLongLong( &isOk, base );
	return isOk;
}
