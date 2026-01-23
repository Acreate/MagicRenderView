#include "charOctValidatorWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include "../../../validator/char/charOctValidator.h"
#include "../../../validator/uint64/uInt64BinValidator.h"
CharOctValidatorWidget::CharOctValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new CharOctValidator( this );
	editorWidget = new QLineEdit( this );
	this->title = new QLabel( title, this );
	editorWidget->installEventFilter( this );
	auto mainLayout = new QHBoxLayout( this );
	mainLayout->addWidget( this->title );
	mainLayout->addWidget( editorWidget );
	connect( editorWidget, &QLineEdit::editingFinished, this, &CharOctValidatorWidget::editingFinished_Slot );
	connect( editorWidget, &QLineEdit::textEdited, this, &CharOctValidatorWidget::currentEditing_Slot );
	editorWidget->setValidator( validator );
}

QObject * CharOctValidatorWidget::getBindEditorObjPtr( ) const {
	return editorWidget;
}
bool CharOctValidatorWidget::getValidatorWidgetText( QString &result_text ) const {
	result_text = editorWidget->text( );
	return true;
}
bool CharOctValidatorWidget::setValidatorWidgetText( QString &result_text ) {
	//if( validator == nullptr )
	//	return false;
	//int index = result_text.length( );
	//if( validator->validate( result_text, index ) == QValidator::Invalid )
	//	return false;
	editorWidget->setText( result_text );
	return true;
}
