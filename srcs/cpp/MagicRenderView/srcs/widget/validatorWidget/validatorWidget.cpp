#include "validatorWidget.h"

#include <qcoreevent.h>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include "../../validator/validator.h"
void ValidatorWidget::editingFinished_Slot( ) {
	if( sender( ) != lineEdit )
		return;
	if( validator == nullptr )
		return;
	QString decString;
	if( validator->validatorStringToDecString( lineEdit->text( ), decString ) == false )
		return;
	emit overEditorFinish_Signal( this, decString );
}
void ValidatorWidget::currentEditing_Slot( const QString &txt ) {
	if( validator == nullptr )
		return;
	QString decString;
	if( validator->validatorStringToDecString( lineEdit->text( ), decString ) == false )
		return;
	emit currentEditing_Signal( this, decString );
}
ValidatorWidget::ValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) {
	validatorWidgetFocus = false;
	lineEdit = new QLineEdit( 0, this );
	lineEdit->installEventFilter( this );
	titleLabel = new QLabel( title, this );
	auto mainLayout = new QHBoxLayout( this );
	mainLayout->addWidget( titleLabel );
	mainLayout->addWidget( lineEdit );

	connect( lineEdit, &QLineEdit::editingFinished, this, &ValidatorWidget::editingFinished_Slot );
	connect( lineEdit, &QLineEdit::textEdited, this, &ValidatorWidget::currentEditing_Slot );
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
	QString text = lineEdit->text( );
	if( text == resultVar )
		return true;
	lineEdit->setText( resultVar );
	return true;
}
bool ValidatorWidget::getDecValue( QString &result_normal_dec_text ) {
	if( validator == nullptr )
		return false;
	QString txt = lineEdit->text( );
	if( txt.isEmpty( ) ) {
		result_normal_dec_text = '0';
		return true;
	}
	if( validator->validatorStringToDecString( txt, result_normal_dec_text ) == false )
		return false;
	return true;
}
bool ValidatorWidget::eventFilter( QObject *watched, QEvent *event ) {
	bool eventFilter = QWidget::eventFilter( watched, event );
	auto type = event->type( );
	switch( type ) {
		case QEvent::FocusIn :
			validatorWidgetFocus = true;
			break;
		case QEvent::FocusOut :
			validatorWidgetFocus = false;
			break;
	}
	return eventFilter;
}
