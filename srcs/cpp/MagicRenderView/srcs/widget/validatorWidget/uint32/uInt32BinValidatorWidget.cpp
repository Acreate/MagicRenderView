#include "uInt32BinValidatorWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <validator/uint32/uInt32BinValidator.h>

#include "../../../validator/uint64/uInt64BinValidator.h"
UInt32BinValidatorWidget::UInt32BinValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new UInt32BinValidator( this );
	editorWidget = new QLineEdit( this );
	this->title = new QLabel( title, this );
	editorWidget->installEventFilter( this );
	auto mainLayout = new QHBoxLayout( this );
	mainLayout->addWidget( this->title );
	mainLayout->addWidget( editorWidget );
	connect( editorWidget, &QLineEdit::editingFinished, this, &UInt32BinValidatorWidget::editingFinished_Slot );
	connect( editorWidget, &QLineEdit::textEdited, this, &UInt32BinValidatorWidget::currentEditing_Slot );
	editorWidget->setValidator( validator );
}

QObject * UInt32BinValidatorWidget::getBindEditorObjPtr( ) const {
	return editorWidget;
}
bool UInt32BinValidatorWidget::getValidatorWidgetText( QString &result_text ) const {
	result_text = editorWidget->text( );
	return true;
}
bool UInt32BinValidatorWidget::setValidatorWidgetText( QString &result_text ) {
	//if( validator == nullptr )
	//	return false;
	//int index = result_text.length( );
	//if( validator->validate( result_text, index ) == QValidator::Invalid )
	//	return false;
	editorWidget->setText( result_text );
	return true;
}
