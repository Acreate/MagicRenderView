#include "numberVarLineEdit.h"

#include <validator/validator.h>

#include "../../../app/application.h"
#include "../../../director/printerDirector.h"
#include "../../../srack/srackInfo.h"

NumberVarLineEdit::NumberVarLineEdit( QWidget *parent ) : QLineEdit( parent ), validator( nullptr ) {
	connect( this, &QLineEdit::textChanged, this, &NumberVarLineEdit::changedText_Slot );
}
NumberVarLineEdit::~NumberVarLineEdit( ) {
	setValidator( nullptr );
	delete validator;
}
bool NumberVarLineEdit::toInt64( const QString &conver_text, int64_t &result_value ) const {
	if( validator == nullptr )
		return false;
	result_value = validator->getInt64Var( );
	return true;
}
bool NumberVarLineEdit::toUInt64( const QString &conver_text, uint64_t &result_value ) const {
	if( validator == nullptr )
		return false;
	result_value = validator->getUInt64Var( );
	return true;
}
void NumberVarLineEdit::setVarToLineEdit( const uint64_t &var ) {
	if( validator == nullptr )
		return;
	QString newText;
	if( validator->varToString( var, newText ) == false )
		return;
	uint64_t orgValue;
	QString converText = text( );
	if( validator->toUInt64( converText, orgValue ) == false )
		return;
	Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "%1(%2,%3)(%4,%5)" ).arg( metaObject( )->className( ) ).arg( converText ).arg( orgValue ).arg( newText ).arg( var ), Create_SrackInfo( ) );
	setText( newText );
}
void NumberVarLineEdit::setVarToLineEdit( const int64_t &var ) {
	if( validator == nullptr )
		return;
	QString newText;
	if( validator->varToString( var, newText ) == false )
		return;
	setText( newText );
}

int NumberVarLineEdit::getBase( ) const {
	if( validator )
		return validator->getBinSystem( );
	return 0;
}
void NumberVarLineEdit::changedText_Slot( const QString &text ) {
	emit text_changed_signal( this, text );
}
