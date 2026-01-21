#include "binLineEdit.h"
#include <validator/binValidator.h>
BinLineEdit::BinLineEdit( uint64_t max_value, bool is_un_sign, QWidget *parent ) : NumberVarLineEdit( parent ) {
	validator = new BinValidator( max_value, is_un_sign, this );
	setValidator( validator );
}
