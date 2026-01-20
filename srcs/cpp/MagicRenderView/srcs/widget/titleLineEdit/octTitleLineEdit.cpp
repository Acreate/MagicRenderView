#include "octTitleLineEdit.h"

#include "../lineEdit/octLineEdit.h"
OctTitleLineEdit::OctTitleLineEdit( const QString &titile_text, uint64_t max_var, QWidget *parent ) : NumberVarTitleLineEdit( titile_text, max_var, parent ) {
	setNumberVarLineEdit( new OctLineEdit( max_var, this ) );
}
