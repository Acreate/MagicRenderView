#include "octLineEdit.h"

#include <validator/octValidator.h>

OctLineEdit::OctLineEdit( uint64_t max_value, bool is_un_sign, QWidget *parent ) : NumberVarLineEdit( parent ) {
	validator = new OctValidator( max_value, is_un_sign, this );
	setValidator( validator );
}
