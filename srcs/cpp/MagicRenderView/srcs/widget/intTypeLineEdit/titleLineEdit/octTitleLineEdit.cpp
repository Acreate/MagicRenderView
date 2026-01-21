#include "octTitleLineEdit.h"

#include "../lineEdit/octLineEdit.h"
OctTitleLineEdit::OctTitleLineEdit( const QString &titile_text, uint64_t max_var, bool is_un_sign, QWidget *parent ) : NumberVarTitleLineEdit( titile_text, max_var, parent ) {
	setNumberVarLineEdit( new OctLineEdit( max_var, is_un_sign, this ) );
}
