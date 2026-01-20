#include "decTitleLineEdit.h"

#include "../lineEdit/decLineEdit.h"
DecTitleLineEdit::DecTitleLineEdit( const QString &titile_text, uint64_t max_var, QWidget *parent ) : NumberVarTitleLineEdit( titile_text, max_var, parent ) {
	setNumberVarLineEdit( new DecLineEdit( max_var, this ) );
}
