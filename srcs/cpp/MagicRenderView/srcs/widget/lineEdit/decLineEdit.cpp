#include "decLineEdit.h"

#include "../../validator/decValidator.h"

DecLineEdit::DecLineEdit( uint64_t value, QWidget *parent ) : NumberVarLineEdit( value, parent ) {
	auto *validator = new DecValidator( value, this );
	setValidator( validator );
	qint64 maxLen = validator->getMaxLen( );
	setMaxLength( maxLen );
}
