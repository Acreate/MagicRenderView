#include "stringValueValidatorWidget.h"

#include <qcoreevent.h>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <validator/string/stringValueValidator.h>
void StringValueValidatorWidget::textChanged_Slot( ) {
	if( getValidatorWidgetText( decTxt ) == false )
		return;
	emit currentEditing_Signal( this, decTxt );
	decTxt.clear( );
}
QObject * StringValueValidatorWidget::getBindEditorObjPtr( ) const {
	return this->textEditPtr;
}
bool StringValueValidatorWidget::getValidatorWidgetText( QString &result_text ) const {
	result_text = this->textEditPtr->toPlainText( );
	return true;
}
bool StringValueValidatorWidget::setValidatorWidgetText( const QString &result_text ) {
	this->textEditPtr->setPlainText( result_text );
	return true;
}
bool StringValueValidatorWidget::eventFilter( QObject *watched, QEvent *event ) {
	if( watched != this->textEditPtr )
		return false;
	auto type = event->type( );
	switch( type ) {
		case QEvent::FocusIn :
			emit this->currentEditingFocusIn_Signal( this );
			return true;
			break;
		case QEvent::FocusOut :

			decTxt = this->textEditPtr->toPlainText( );
			emit this->overEditorFinish_Signal( this, decTxt );
			decTxt.clear( );
			emit this->currentEditingFocusOut_Signal( this );
			return true;
			break;
	}
	return false;
}
StringValueValidatorWidget::StringValueValidatorWidget( const QString &title, const QString &default_text_value, QWidget *parent ) : ValidatorWidget( title, default_text_value, parent ) {
	validator = new StringValueValidator( this );
	this->title = new QLabel( title, this );
	this->textEditPtr = new QTextEdit( this );
	auto mainLayout = new QVBoxLayout( this );
	mainLayout->addWidget( this->title );
	mainLayout->addWidget( textEditPtr );
	this->textEditPtr->setPlaceholderText( default_text_value );
	this->textEditPtr->installEventFilter( this );
}
StringValueValidatorWidget::StringValueValidatorWidget( const QString &title, const QString &default_text_value, QWidget *parent, bool is_enable_editoring_signal ) : StringValueValidatorWidget( title, default_text_value, parent ) {
	if( is_enable_editoring_signal )
		connect( this->textEditPtr, &QTextEdit::textChanged, this, &StringValueValidatorWidget::textChanged_Slot );
}
bool StringValueValidatorWidget::decStringToValidatorString( const QString &normal_dec_text, QString &result_normal_validator_var_txt ) {
	if( validator == nullptr )
		return false;
	result_normal_validator_var_txt = normal_dec_text;
	return true;
}
bool StringValueValidatorWidget::getDecValue( QString &result_normal_dec_text ) {
	if( validator == nullptr )
		return false;
	result_normal_dec_text = this->textEditPtr->toPlainText( );
	return true;
}
bool StringValueValidatorWidget::setDecValue( const QString &normal_dec_text ) {
	if( validator == nullptr )
		return false;
	return this->setValidatorWidgetText( normal_dec_text );
}
bool StringValueValidatorWidget::validatorStringToDecString( const QString &normal_validator_var_txt, QString &result_normal_dec_text ) {
	if( validator == nullptr )
		return false;
	result_normal_dec_text = normal_validator_var_txt;
	return true;
}
