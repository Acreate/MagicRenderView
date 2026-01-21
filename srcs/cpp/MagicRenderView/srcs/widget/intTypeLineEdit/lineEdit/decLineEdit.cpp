#include "decLineEdit.h"
#include <validator/decValidator.h>

DecLineEdit::DecLineEdit( uint64_t max_value, bool is_un_sign, QWidget *parent ) : NumberVarLineEdit( parent ) {
	validator = new DecValidator( max_value, is_un_sign, this );
	setValidator( validator );
}
