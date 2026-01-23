#include "int64OctValidatorWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include "../../../validator/int64/int64OctValidator.h"
#include "../../../validator/uint64/uInt64BinValidator.h"
Int64OctValidatorWidget::Int64OctValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new Int64OctValidator( this );
	editorWidget = new QLineEdit( this );
	this->title = new QLabel( title, this );
	editorWidget->installEventFilter( this );
	auto mainLayout = new QHBoxLayout( this );
	mainLayout->addWidget( this->title );
	mainLayout->addWidget( editorWidget );
	connect( editorWidget, &QLineEdit::editingFinished, this, &Int64OctValidatorWidget::editingFinished_Slot );
	connect( editorWidget, &QLineEdit::textEdited, this, &Int64OctValidatorWidget::currentEditing_Slot );
	editorWidget->setValidator( validator );
}

QObject * Int64OctValidatorWidget::getBindEditorObjPtr( ) const {
	return editorWidget;
}
bool Int64OctValidatorWidget::getValidatorWidgetText( QString &result_text ) const {
	result_text = editorWidget->text( );
	return true;
}
bool Int64OctValidatorWidget::setValidatorWidgetText( QString &result_text ) {
	editorWidget->setText( result_text );
	return true;
}
