#include "numberVarLineEdit.h"

NumberVarLineEdit::NumberVarLineEdit( uint64_t value, QWidget *parent ) : QLineEdit( parent ) {
	setMaxLength( 0 );
	connect( this, &QLineEdit::textChanged, this, &NumberVarLineEdit::changedText_Slot );
}
void NumberVarLineEdit::setVarToLineEdit( const uint64_t &var ) {
	uint64_t org;
	QString newText;
	if( toUInt64( text( ), org ) )
		if( org == var )
			return;
	newText = tr( "%1" ).arg( var, maxLength( ), base, '0' );
	setText( newText );
}
void NumberVarLineEdit::setVarToLineEdit( const int64_t &var ) {
	int64_t org;
	QString newText;
	if( toInt64( text( ), org ) )
		if( org == var )
			return;
	newText = tr( "%1" ).arg( var, maxLength( ), base, '0' );
	setText( newText );
}
void NumberVarLineEdit::changedText_Slot( const QString &text ) {
	emit text_changed_signal( this, text );
}
