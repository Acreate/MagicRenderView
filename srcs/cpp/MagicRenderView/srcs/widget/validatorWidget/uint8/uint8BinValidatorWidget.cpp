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
bool Uint8BinValidatorWidget::setValidatorWidgetText( const QString &result_text ) {
	//if( validator == nullptr )
	//	return false;
	//int index = result_text.length( );
	//if( validator->validate( result_text, index ) == QValidator::Invalid )
	//	return false;
	editorWidget->setText( result_text );
	return true;
}
