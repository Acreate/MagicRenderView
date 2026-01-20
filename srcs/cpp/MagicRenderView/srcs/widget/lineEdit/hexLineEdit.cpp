#include "hexLineEdit.h"

#include "../../validator/hexValidator.h"

HexLineEdit::HexLineEdit( uint64_t value, QWidget *parent ) : NumberVarLineEdit( value, parent ) {
	auto *validator = new HexValidator( value, this );
	setValidator( validator );
	qint64 maxLen = validator->getMaxLen( );
	setMaxLength( maxLen );
}
