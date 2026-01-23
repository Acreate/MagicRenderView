#include "uInt64OctValidatorWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include "../../../validator/uint64/uInt64OctValidator.h"
UInt64OctValidatorWidget::UInt64OctValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new UInt64OctValidator( this );
	editorWidget = new QLineEdit( this );
	this->title = new QLabel( title, this );
	editorWidget->installEventFilter( this );
	auto mainLayout = new QHBoxLayout( this );
	mainLayout->addWidget( this->title );
	mainLayout->addWidget( editorWidget );
	connect( editorWidget, &QLineEdit::editingFinished, this, &UInt64OctValidatorWidget::editingFinished_Slot );
	connect( editorWidget, &QLineEdit::textEdited, this, &UInt64OctValidatorWidget::currentEditing_Slot );
	editorWidget->setValidator( validator );
}

QObject * UInt64OctValidatorWidget::getBindEditorObjPtr( ) const {
	return editorWidget;
}
bool UInt64OctValidatorWidget::getValidatorWidgetText( QString &result_text ) const {
	result_text = editorWidget->text( );
	return true;
}
bool UInt64OctValidatorWidget::setValidatorWidgetText( QString &result_text ) {
	editorWidget->setText( result_text );
	return true;
}
