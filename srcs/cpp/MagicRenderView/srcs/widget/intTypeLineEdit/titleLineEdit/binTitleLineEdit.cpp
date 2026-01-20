#include "binTitleLineEdit.h"

#include "../lineEdit/binLineEdit.h"

BinTitleLineEdit::BinTitleLineEdit( const QString &titile_text, uint64_t max_var, QWidget *parent ) : NumberVarTitleLineEdit( titile_text, max_var, parent ) {
	setNumberVarLineEdit( new BinLineEdit( max_var, this ) );
}
