#include "octLineEdit.h"

#include <validator/octValidator.h>

OctLineEdit::OctLineEdit( uint64_t value, QWidget *parent ) : NumberVarLineEdit( value, parent ) {
	auto *validator = new OctValidator( value, this );
	base = 8;
	setValidator( validator );
	qint64 maxLen = validator->getMaxLen( );
	setMaxLength( maxLen );
}
bool OctLineEdit::toInt64( const QString &conver_text, int64_t &result_value ) const {
	bool isOk;
	result_value = conver_text.toLongLong( &isOk, base );
	return isOk;
}
bool OctLineEdit::toUInt64( const QString &conver_text, uint64_t &result_value ) const {
	bool isOk;
	result_value = conver_text.toULongLong( &isOk, base );
	return isOk;
}
