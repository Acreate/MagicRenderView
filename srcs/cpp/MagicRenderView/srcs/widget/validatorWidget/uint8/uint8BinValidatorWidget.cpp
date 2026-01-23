#include "uint8BinValidatorWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <validator/uint8/uint8BinValidator.h>
Uint8BinValidatorWidget::Uint8BinValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new Uint8BinValidator( this );
	editorWidget = new QLineEdit( this );
	this->title = new QLabel( title, this );
	editorWidget->installEventFilter( this );
	auto mainLayout = new QHBoxLayout( this );
	mainLayout->addWidget( this->title );
	mainLayout->addWidget( editorWidget );
	connect( editorWidget, &QLineEdit::editingFinished, this, &Uint8BinValidatorWidget::editingFinished_Slot );
	connect( editorWidget, &QLineEdit::textEdited, this, &Uint8BinValidatorWidget::currentEditing_Slot );
	editorWidget->setValidator( validator );
}
QObject * Uint8BinValidatorWidget::getBindEditorObjPtr( ) const {
	return editorWidget;
}
bool Uint8BinValidatorWidget::getValidatorWidgetText( QString &result_text ) const {
	result_text = editorWidget->text( );
	return true;
}
bool Uint8BinValidatorWidget::setValidatorWidgetText( QString &result_text ) {
	editorWidget->setText( result_text );
	return true;
}
Uint8BinValidatorWidget::~Uint8BinValidatorWidget( ) {
}
void Uint8BinValidatorWidget::currentEditing_Slot( const QString &txt ) {
	ValidatorWidget::currentEditing_Slot( txt );
}
bool Uint8BinValidatorWidget::decStringToValidatorString( const QString &normal_dec_text, QString &result_normal_validator_var_txt ) {
	return ValidatorWidget::decStringToValidatorString( normal_dec_text, result_normal_validator_var_txt );
}
void Uint8BinValidatorWidget::editingFinished_Slot( ) {
	ValidatorWidget::editingFinished_Slot( );
}
bool Uint8BinValidatorWidget::eventFilter( QObject *watched, QEvent *event ) {
	return ValidatorWidget::eventFilter( watched, event );
}
bool Uint8BinValidatorWidget::getDecValue( QString &result_normal_dec_text ) {
	return ValidatorWidget::getDecValue( result_normal_dec_text );
}
bool Uint8BinValidatorWidget::isValidatorWidgetFocus( ) const {
	return ValidatorWidget::isValidatorWidgetFocus( );
}
bool Uint8BinValidatorWidget::setDecValue( const QString &normal_dec_text ) {
	return ValidatorWidget::setDecValue( normal_dec_text );
}
bool Uint8BinValidatorWidget::validatorStringToDecString( const QString &normal_validator_var_txt, QString &result_normal_dec_text ) {
	return ValidatorWidget::validatorStringToDecString( normal_validator_var_txt, result_normal_dec_text );
}
