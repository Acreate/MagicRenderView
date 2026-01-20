#include "hexLineEdit.h"

#include <validator/hexValidator.h>

HexLineEdit::HexLineEdit( uint64_t value, QWidget *parent ) : NumberVarLineEdit( value, parent ) {
	auto *validator = new HexValidator( value, this );
	base = 16;
	setValidator( validator );
	qint64 maxLen = validator->getMaxLen( );
	setMaxLength( maxLen );
}
bool HexLineEdit::toInt64( const QString &conver_text, int64_t &result_value ) const {

	bool isOk;
	result_value = conver_text.toLongLong( &isOk, base );
	return isOk;
}
bool HexLineEdit::toUInt64( const QString &conver_text, uint64_t &result_value ) const {

	bool isOk;
	result_value = conver_text.toLongLong( &isOk, base );
	return isOk;
}
