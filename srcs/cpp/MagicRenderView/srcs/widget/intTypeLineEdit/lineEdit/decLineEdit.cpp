#include "decLineEdit.h"
#include <validator/decValidator.h>

DecLineEdit::DecLineEdit( uint64_t value, QWidget *parent ) : NumberVarLineEdit( value, parent ) {
	auto *validator = new DecValidator( value, this );
	base = 10;
	setValidator( validator );
	qint64 maxLen = validator->getMaxLen( );
	setMaxLength( maxLen );
}
bool DecLineEdit::toInt64( const QString &conver_text, int64_t &result_value ) const {

	bool isOk;
	result_value = conver_text.toLongLong( &isOk, base );
	return isOk;
}
bool DecLineEdit::toUInt64( const QString &conver_text, uint64_t &result_value ) const {

	bool isOk;
	result_value = conver_text.toLongLong( &isOk, base );
	return isOk;
}
