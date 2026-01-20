#include "binLineEdit.h"

#include "../../validator/binValidator.h"
BinLineEdit::BinLineEdit( uint64_t value, QWidget *parent ) : NumberVarLineEdit( value, parent ) {
	BinValidator *binValidator = new BinValidator( value, this );
	setValidator( binValidator );
	qint64 maxLen = binValidator->getMaxLen( );
	setMaxLength( maxLen );
}
