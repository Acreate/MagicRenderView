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
	//if( validator == nullptr )
	//	return false;
	//int index = result_text.length( );
	//if( validator->validate( result_text, index ) == QValidator::Invalid )
	//	return false;
	editorWidget->setText( result_text );
	return true;
}
Uint8DecValidatorWidget::~Uint8DecValidatorWidget( ) {
}
