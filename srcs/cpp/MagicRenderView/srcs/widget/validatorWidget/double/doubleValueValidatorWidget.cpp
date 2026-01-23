#include "doubleValueValidatorWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include "../../../validator/double/doubleValueValidator.h"
#include "../../../validator/uint64/uInt64BinValidator.h"
QObject * DoubleValueValidatorWidget::getBindEditorObjPtr( ) const {
	return editorWidget;
}
bool DoubleValueValidatorWidget::getValidatorWidgetText( QString &result_text ) const {
	result_text = editorWidget->text( );
	return true;
}
bool DoubleValueValidatorWidget::setValidatorWidgetText( QString &result_text ) {
	editorWidget->setText( result_text );
	return true;
}
DoubleValueValidatorWidget::DoubleValueValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new DoubleValueValidator( this );
	editorWidget = new QLineEdit( this );
	this->title = new QLabel( title, this );
	editorWidget->installEventFilter( this );
	auto mainLayout = new QHBoxLayout( this );
	mainLayout->addWidget( this->title );
	mainLayout->addWidget( editorWidget );
	connect( editorWidget, &QLineEdit::editingFinished, this, &DoubleValueValidatorWidget::editingFinished_Slot );
	connect( editorWidget, &QLineEdit::textEdited, this, &DoubleValueValidatorWidget::currentEditing_Slot );
	editorWidget->setValidator( validator );
}
