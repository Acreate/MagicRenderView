#include "charBinValidatorWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include "../../../validator/char/charBinValidator.h"

CharBinValidatorWidget::CharBinValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {
	validator = new CharBinValidator( this );
	editorWidget = new QLineEdit( this );
	this->title = new QLabel( title, this );
	editorWidget->installEventFilter( this );
	auto mainLayout = new QHBoxLayout( this );
	mainLayout->addWidget( this->title );
	mainLayout->addWidget( editorWidget );
	connect( editorWidget, &QLineEdit::editingFinished, this, &CharBinValidatorWidget::editingFinished_Slot );
	connect( editorWidget, &QLineEdit::textEdited, this, &CharBinValidatorWidget::currentEditing_Slot );
	editorWidget->setValidator( validator );
}

QObject * CharBinValidatorWidget::getBindEditorObjPtr( ) const {
	return editorWidget;
}
bool CharBinValidatorWidget::getValidatorWidgetText( QString &result_text ) const {
	result_text = editorWidget->text( );
	return true;
}
bool CharBinValidatorWidget::setValidatorWidgetText( QString &result_text ) {
	//if( validator == nullptr )
	//	return false;
	//int index = result_text.length( );
	//if( validator->validate( result_text, index ) == QValidator::Invalid )
	//	return false;
	editorWidget->setText( result_text );
	return true;
}
