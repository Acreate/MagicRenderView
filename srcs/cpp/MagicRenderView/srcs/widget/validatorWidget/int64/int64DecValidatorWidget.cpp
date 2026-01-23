#include "int64DecValidatorWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include "../../../validator/int64/int64DecValidator.h"
Int64DecValidatorWidget::Int64DecValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new Int64DecValidator( this );
	editorWidget = new QLineEdit( this );
	this->title = new QLabel( title, this );
	editorWidget->installEventFilter( this );
	auto mainLayout = new QHBoxLayout( this );
	mainLayout->addWidget( this->title );
	mainLayout->addWidget( editorWidget );
	connect( editorWidget, &QLineEdit::editingFinished, this, &Int64DecValidatorWidget::editingFinished_Slot );
	connect( editorWidget, &QLineEdit::textEdited, this, &Int64DecValidatorWidget::currentEditing_Slot );
	editorWidget->setValidator( validator );
}

QObject * Int64DecValidatorWidget::getBindEditorObjPtr( ) const {
	return editorWidget;
}
bool Int64DecValidatorWidget::getValidatorWidgetText( QString &result_text ) const {
	result_text = editorWidget->text( );
	return true;
}
bool Int64DecValidatorWidget::setValidatorWidgetText( QString &result_text ) {
	editorWidget->setText( result_text );
	return true;
}
