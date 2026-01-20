#include "numberVarLineEdit.h"

NumberVarLineEdit::NumberVarLineEdit( uint64_t value, QWidget *parent ) : QLineEdit( parent ) {
	setMaxLength( 0 );
	connect( this, &QLineEdit::textChanged, this, &NumberVarLineEdit::changedText_Slot );
}
void NumberVarLineEdit::changedText_Slot( const QString &text ) {
	emit text_changed_signal( this, text );
}
