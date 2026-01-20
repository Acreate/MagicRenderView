#include "octLineEdit.h"

#include "../../validator/octValidator.h"

OctLineEdit::OctLineEdit( uint64_t value, QWidget *parent ) : NumberVarLineEdit( value, parent ) {
	auto *validator = new OctValidator( value, this );
	setValidator( validator );
	qint64 maxLen = validator->getMaxLen( );
	setMaxLength( maxLen );
}
