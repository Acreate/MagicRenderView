#include "validatorWidget.h"
#include <qevent.h>
#include <QHBoxLayout>

#include <validator/validator.h>
void ValidatorWidget::editingFinished_Slot( ) {
	if( sender( ) != this->getBindEditorObjPtr( ) )
		return;
	QString decString;
	QString txt;
	if( validator == nullptr )
		return;
	if( this->getValidatorWidgetText( txt ) == false )
		return;
	if( validator->validatorStringToDecString( txt, decString ) == false )
		return;
	emit overEditorFinish_Signal( this, decString );
}
void ValidatorWidget::currentEditing_Slot( const QString &txt ) {
	if( validator == nullptr )
		return;
	QString decString;
	if( txt.isEmpty( ) )
		decString = "0";
	else if( validator->validatorStringToDecString( txt, decString ) == false )
		return;
	emit currentEditing_Signal( this, decString );
}

ValidatorWidget::ValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) {
	validatorWidgetFocus = false;
}
bool ValidatorWidget::decStringToValidatorString( const QString &normal_dec_text, QString &result_normal_validator_var_txt ) {
	if( validator == nullptr )
		return false;
	return validator->decStringToValidatorString( normal_dec_text, result_normal_validator_var_txt );
}
bool ValidatorWidget::validatorStringToDecString( const QString &normal_validator_var_txt, QString &result_normal_dec_text ) {
	if( validator == nullptr )
		return false;
	return validator->validatorStringToDecString( normal_validator_var_txt, result_normal_dec_text );
}
bool ValidatorWidget::setDecValue( const QString &normal_dec_text ) {
	if( validator == nullptr )
		return false;
	QString resultVar;
	if( validator->decStringToValidatorString( normal_dec_text, resultVar ) == false )
		return false;
	QString text;
	if( this->getValidatorWidgetText( text ) == false )
		return false;
	if( text == resultVar )
		return true;
	return this->setValidatorWidgetText( resultVar );
}
bool ValidatorWidget::getDecValue( QString &result_normal_dec_text ) {

	QString txt;
	if( this->getValidatorWidgetText( txt ) == false )
		return false;
	if( txt.isEmpty( ) ) {
		result_normal_dec_text = '0';
		return true;
	}
	return validator->validatorStringToDecString( txt, result_normal_dec_text );
}
bool ValidatorWidget::eventFilter( QObject *watched, QEvent *event ) {
	bool eventFilter = QWidget::eventFilter( watched, event );
	auto type = event->type( );
	switch( type ) {
		case QEvent::FocusIn :
			validatorWidgetFocus = true;
			emit currentEditingFocusIn_Signal( this );
			break;
		case QEvent::FocusOut :
			validatorWidgetFocus = false;
			emit currentEditingFocusOut_Signal( this );
			break;
	}
	return eventFilter;
}
