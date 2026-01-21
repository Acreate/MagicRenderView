#include "hexTitleLineEdit.h"

#include "../lineEdit/hexLineEdit.h"

HexTitleLineEdit::HexTitleLineEdit( const QString &titile_text, uint64_t max_var, bool is_un_sign, QWidget *parent ) : NumberVarTitleLineEdit( titile_text, max_var, parent ) {
	setNumberVarLineEdit( new HexLineEdit( max_var, is_un_sign, this ) );
}
