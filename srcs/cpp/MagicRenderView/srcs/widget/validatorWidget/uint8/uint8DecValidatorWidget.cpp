#include "uint8DecValidatorWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include <validator/uint8/uint8DecValidator.h>

Uint8DecValidatorWidget::Uint8DecValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new Uint8DecValidator( this );
	editorWidget = new QLineEdit( this );
	this->title = new QLabel( title, this );
	editorWidget->installEventFilter( this );
	auto mainLayout = new QHBoxLayout( this );
	mainLayout->addWidget( this->title );
	mainLayout->addWidget( editorWidget );
	connect( editorWidget, &QLineEdit::editingFinished, this, &Uint8DecValidatorWidget::editingFinished_Slot );
	connect( editorWidget, &QLineEdit::textEdited, this, &Uint8DecValidatorWidget::currentEditing_Slot );
	editorWidget->setValidator( validator );
}

QObject * Uint8DecValidatorWidget::getBindEditorObjPtr( ) const {
	return editorWidget;
}
bool Uint8DecValidatorWidget::getValidatorWidgetText( QString &result_text ) const {
	result_text = editorWidget->text( );
	return true;
}
bool Uint8DecValidatorWidget::setValidatorWidgetText( QString &result_text ) {
	editorWidget->setText( result_text );
	return true;
}
Uint8DecValidatorWidget::~Uint8DecValidatorWidget( ) {
}
void Uint8DecValidatorWidget::currentEditing_Slot( const QString &txt ) {
	ValidatorWidget::currentEditing_Slot( txt );
}
bool Uint8DecValidatorWidget::decStringToValidatorString( const QString &normal_dec_text, QString &result_normal_validator_var_txt ) {
	return ValidatorWidget::decStringToValidatorString( normal_dec_text, result_normal_validator_var_txt );
}
void Uint8DecValidatorWidget::editingFinished_Slot( ) {
	ValidatorWidget::editingFinished_Slot( );
}
bool Uint8DecValidatorWidget::eventFilter( QObject *watched, QEvent *event ) {
	return ValidatorWidget::eventFilter( watched, event );
}
bool Uint8DecValidatorWidget::getDecValue( QString &result_normal_dec_text ) {
	return ValidatorWidget::getDecValue( result_normal_dec_text );
}
bool Uint8DecValidatorWidget::isValidatorWidgetFocus( ) const {
	return ValidatorWidget::isValidatorWidgetFocus( );
}
bool Uint8DecValidatorWidget::setDecValue( const QString &normal_dec_text ) {
	return ValidatorWidget::setDecValue( normal_dec_text );
}
bool Uint8DecValidatorWidget::validatorStringToDecString( const QString &normal_validator_var_txt, QString &result_normal_dec_text ) {
	return ValidatorWidget::validatorStringToDecString( normal_validator_var_txt, result_normal_dec_text );
}
