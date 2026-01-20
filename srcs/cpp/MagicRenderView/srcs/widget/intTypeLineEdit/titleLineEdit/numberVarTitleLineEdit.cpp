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
void NumberVarTitleLineEdit::setVarToLineEdit( const uint64_t &var ) {
	if( numberVarLineEdit )
		numberVarLineEdit->setVarToLineEdit( var );
}
void NumberVarTitleLineEdit::setVarToLineEdit( const int64_t &var ) {
	if( numberVarLineEdit )
		numberVarLineEdit->setVarToLineEdit( var );
}
QString NumberVarTitleLineEdit::getNumberValue( ) const {
	if( numberVarLineEdit )
		numberVarLineEdit->text( );
	return { };
}
bool NumberVarTitleLineEdit::toInt64( const QString &conver_text, int64_t &result_value ) const {
	if( numberVarLineEdit )
		return numberVarLineEdit->toInt64( conver_text, result_value );
	return false;
}
bool NumberVarTitleLineEdit::toUInt64( const QString &conver_text, uint64_t &result_value ) const {
	if( numberVarLineEdit )
		return numberVarLineEdit->toUInt64( conver_text, result_value );
	return false;
}
