#include "charValueValidatorWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include "../../../validator/char/charValueValidator.h"
#include "../../../validator/uint64/uInt64BinValidator.h"
CharValueValidatorWidget::CharValueValidatorWidget( const QString &title, const QChar &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new CharValueValidator( this );
	editorWidget = new QLineEdit( this );
	this->title = new QLabel( title, this );
	editorWidget->installEventFilter( this );
	auto mainLayout = new QHBoxLayout( this );
	mainLayout->addWidget( this->title );
	mainLayout->addWidget( editorWidget );
	connect( editorWidget, &QLineEdit::editingFinished, this, &CharValueValidatorWidget::editingFinished_Slot );
	connect( editorWidget, &QLineEdit::textEdited, this, &CharValueValidatorWidget::currentEditing_Slot );
	editorWidget->setValidator( validator );
}

QObject * CharValueValidatorWidget::getBindEditorObjPtr( ) const {
	return editorWidget;
}
bool CharValueValidatorWidget::getValidatorWidgetText( QString &result_text ) const {
	result_text = editorWidget->text( );
	return true;
}
bool CharValueValidatorWidget::setValidatorWidgetText( const QString &result_text ) {
	//if( validator == nullptr )
	//	return false;
	//int index = result_text.length( );
	//if( validator->validate( result_text, index ) == QValidator::Invalid )
	//	return false;
	editorWidget->setText( result_text );
	return true;
}
CharValueValidatorWidget::~CharValueValidatorWidget( ) {
}
void CharValueValidatorWidget::currentEditing_Slot( const QString &txt ) {
	auto text = editorWidget->text( );
	emit currentEditing_Signal( this, text );
}
bool CharValueValidatorWidget::decStringToValidatorString( const QString &normal_dec_text, QString &result_normal_validator_var_txt ) {
	bool isOK;
	ushort uShort = normal_dec_text.toUShort( &isOK );
	if( isOK == false )
		return false;
	result_normal_validator_var_txt = QChar( uShort );
	return true;
}
void CharValueValidatorWidget::editingFinished_Slot( ) {
	ValidatorWidget::editingFinished_Slot( );
}
bool CharValueValidatorWidget::eventFilter( QObject *watched, QEvent *event ) {
	return ValidatorWidget::eventFilter( watched, event );
}
bool CharValueValidatorWidget::getDecValue( QString &result_normal_dec_text ) {
	result_normal_dec_text = editorWidget->text( );
	return true;
}
bool CharValueValidatorWidget::isValidatorWidgetFocus( ) const {
	return ValidatorWidget::isValidatorWidgetFocus( );
}
bool CharValueValidatorWidget::setDecValue( const QString &normal_dec_text ) {
	bool isOK;
	ushort uShort = normal_dec_text.toUShort( &isOK );
	if( isOK == false )
		return false;
	editorWidget->setText( QChar( uShort ) );
	return true;
}
bool CharValueValidatorWidget::validatorStringToDecString( const QString &normal_validator_var_txt, QString &result_normal_dec_text ) {

	qsizetype txtLen = normal_validator_var_txt.length( );
	if( txtLen == 0 ) {
		result_normal_dec_text = '0';
		return true;
	}
	result_normal_dec_text = QString::number( normal_validator_var_txt.data( )[ 0 ].unicode( ) );
	return true;
}
