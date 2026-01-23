#include "uInt64HexValidatorWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include "../../../validator/uint64/uInt64HexValidator.h"
UInt64HexValidatorWidget::UInt64HexValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new UInt64HexValidator( this );
	editorWidget = new QLineEdit( this );
	this->title = new QLabel( title, this );
	editorWidget->installEventFilter( this );
	auto mainLayout = new QHBoxLayout( this );
	mainLayout->addWidget( this->title );
	mainLayout->addWidget( editorWidget );
	connect( editorWidget, &QLineEdit::editingFinished, this, &UInt64HexValidatorWidget::editingFinished_Slot );
	connect( editorWidget, &QLineEdit::textEdited, this, &UInt64HexValidatorWidget::currentEditing_Slot );
	editorWidget->setValidator( validator );
}

QObject * UInt64HexValidatorWidget::getBindEditorObjPtr( ) const {
	return editorWidget;
}
bool UInt64HexValidatorWidget::getValidatorWidgetText( QString &result_text ) const {
	result_text = editorWidget->text( );
	return true;
}
bool UInt64HexValidatorWidget::setValidatorWidgetText( QString &result_text ) {
	//if( validator == nullptr )
	//	return false;
	//int index = result_text.length( );
	//if( validator->validate( result_text, index ) == QValidator::Invalid )
	//	return false;
	editorWidget->setText( result_text );
	return true;
}
