#include "uint8HexValidatorWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include <validator/uint8/uint8HexValidator.h>
Uint8HexValidatorWidget::Uint8HexValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new Uint8HexValidator( this );
	editorWidget = new QLineEdit( this );
	this->title = new QLabel( title, this );
	editorWidget->installEventFilter( this );
	auto mainLayout = new QHBoxLayout( this );
	mainLayout->addWidget( this->title );
	mainLayout->addWidget( editorWidget );
	connect( editorWidget, &QLineEdit::editingFinished, this, &Uint8HexValidatorWidget::editingFinished_Slot );
	connect( editorWidget, &QLineEdit::textEdited, this, &Uint8HexValidatorWidget::currentEditing_Slot );
	editorWidget->setValidator( validator );
}

QObject * Uint8HexValidatorWidget::getBindEditorObjPtr( ) const {
	return editorWidget;
}
bool Uint8HexValidatorWidget::getValidatorWidgetText( QString &result_text ) const {
	result_text = editorWidget->text( );
	return true;
}
bool Uint8HexValidatorWidget::setValidatorWidgetText( QString &result_text ) {
	//if( validator == nullptr )
	//	return false;
	//int index = result_text.length( );
	//if( validator->validate( result_text, index ) == QValidator::Invalid )
	//	return false;
	editorWidget->setText( result_text );
	return true;
}
