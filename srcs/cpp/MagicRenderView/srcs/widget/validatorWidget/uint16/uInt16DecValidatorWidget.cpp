#include "uInt16DecValidatorWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <validator/uint16/uInt16DecValidator.h>

#include "../../../validator/uint64/uInt64BinValidator.h"
UInt16DecValidatorWidget::UInt16DecValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new UInt16DecValidator( this );
	editorWidget = new QLineEdit( this );
	this->title = new QLabel( title, this );
	editorWidget->installEventFilter( this );
	auto mainLayout = new QHBoxLayout( this );
	mainLayout->addWidget( this->title );
	mainLayout->addWidget( editorWidget );
	connect( editorWidget, &QLineEdit::editingFinished, this, &UInt16DecValidatorWidget::editingFinished_Slot );
	connect( editorWidget, &QLineEdit::textEdited, this, &UInt16DecValidatorWidget::currentEditing_Slot );
	editorWidget->setValidator( validator );
}

QObject * UInt16DecValidatorWidget::getBindEditorObjPtr( ) const {
	return editorWidget;
}
bool UInt16DecValidatorWidget::getValidatorWidgetText( QString &result_text ) const {
	result_text = editorWidget->text( );
	return true;
}
bool UInt16DecValidatorWidget::setValidatorWidgetText( const QString &result_text ) {
	//if( validator == nullptr )
	//	return false;
	//int index = result_text.length( );
	//if( validator->validate( result_text, index ) == QValidator::Invalid )
	//	return false;
	editorWidget->setText( result_text );
	return true;
}
