#include "numberVarTitleLineEdit.h"
#include <QLabel>
#include <QVBoxLayout>

#include "../lineEdit/numberVarLineEdit.h"
void NumberVarTitleLineEdit::textChanged_Slots( NumberVarLineEdit *sender_obj, const QString &text ) {
	emit text_changed_signal( this, sender_obj, text );
}
NumberVarTitleLineEdit::NumberVarTitleLineEdit( const QString &titile_text, uint64_t max_var, QWidget *parent ) : QWidget( parent ) {
	numberVarLineEdit = nullptr;
	titile = new QLabel( titile_text, this );
	mainLayout = new QVBoxLayout( this );
	mainLayout->addWidget( titile );
}
void NumberVarTitleLineEdit::setNumberVarLineEdit( NumberVarLineEdit *number_var_line_edit ) {
	if( numberVarLineEdit )
		delete numberVarLineEdit;
	numberVarLineEdit = number_var_line_edit;
	mainLayout->addWidget( numberVarLineEdit );
	connect( numberVarLineEdit, &NumberVarLineEdit::text_changed_signal, this, &NumberVarTitleLineEdit::textChanged_Slots );
}
void NumberVarTitleLineEdit::setTitleText( const QString &new_title_text ) {
	titile->setText( new_title_text );
}
QString NumberVarTitleLineEdit::getTitleText( ) {
	return titile->text( );
}
