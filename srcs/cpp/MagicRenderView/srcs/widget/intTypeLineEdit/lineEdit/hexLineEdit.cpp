#include "hexLineEdit.h"

#include <validator/hexValidator.h>

HexLineEdit::HexLineEdit( uint64_t max_value, bool is_un_sign, QWidget *parent ) : NumberVarLineEdit( parent ) {
	validator = new HexValidator( max_value, is_un_sign, this );
	setValidator( validator );
}
