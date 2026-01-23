#include "int64BinValidatorWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include "../../../validator/int64/int64BinValidator.h"
Int64BinValidatorWidget::Int64BinValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new Int64BinValidator( this );
	editorWidget = new QLineEdit( this );
	this->title = new QLabel( title, this );
	editorWidget->installEventFilter( this );
	auto mainLayout = new QHBoxLayout( this );
	mainLayout->addWidget( this->title );
	mainLayout->addWidget( editorWidget );
	connect( editorWidget, &QLineEdit::editingFinished, this, &Int64BinValidatorWidget::editingFinished_Slot );
	connect( editorWidget, &QLineEdit::textEdited, this, &Int64BinValidatorWidget::currentEditing_Slot );
	editorWidget->setValidator( validator );
}

QObject * Int64BinValidatorWidget::getBindEditorObjPtr( ) const {
	return editorWidget;
}
bool Int64BinValidatorWidget::getValidatorWidgetText( QString &result_text ) const {
	result_text = editorWidget->text( );
	return true;
}
bool Int64BinValidatorWidget::setValidatorWidgetText( QString &result_text ) {
	editorWidget->setText( result_text );
	return true;
}
