#include "binTitleLineEdit.h"

#include "../lineEdit/binLineEdit.h"

BinTitleLineEdit::BinTitleLineEdit( const QString &titile_text, uint64_t max_var, bool is_un_sign, QWidget *parent ) : NumberVarTitleLineEdit( titile_text, max_var, parent ) {
	setNumberVarLineEdit( new BinLineEdit( max_var, is_un_sign, this ) );
}
