#include "boolValueValidatorWidget.h"

#include <QHBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>

void BoolValueValidatorWidget::currentIndexChanged_Slot( int index ) {
	auto currentIndexTxt = boolComboBox->itemText( index );
	if( currentIndexTxt == trueText || currentIndexTxt == falseText ) {
		emit overEditorFinish_Signal( this, currentIndexTxt );
		emit currentEditing_Signal( this, currentIndexTxt );
	}
}
void BoolValueValidatorWidget::currentTextChanged_Slot( const QString &new_text ) {
	if( new_text == trueText || new_text == falseText ) {
		emit overEditorFinish_Signal( this, new_text );
		emit currentEditing_Signal( this, new_text );
	}
}
QObject * BoolValueValidatorWidget::getBindEditorObjPtr( ) const {
	return boolComboBox;
}
bool BoolValueValidatorWidget::getValidatorWidgetText( QString &result_text ) const {
	if( boolComboBox->currentIndex( ) == 0 ) {
		result_text = falseText;
		return true;
	}
	result_text = trueText;
	return true;
}
bool BoolValueValidatorWidget::setValidatorWidgetText( const QString &result_text ) {
	if( trueText == result_text ) {
		boolComboBox->setCurrentIndex( 1 );
		return true;
	}
	if( falseText == result_text ) {
		boolComboBox->setCurrentIndex( 0 );
		return true;
	}
	return false;
}
BoolValueValidatorWidget::BoolValueValidatorWidget( const QString &title, bool bool_value, QWidget *parent ) : ValidatorWidget( title, 0, parent ) {
	auto mainLayout = new QHBoxLayout( this );
	this->title = new QLabel( title, this );
	boolComboBox = new QComboBox( this );
	trueText = tr( "真" );
	falseText = tr( "假" );
	boolComboBox->addItems( { falseText, trueText } );
	setBoolValue( bool_value );
	mainLayout->addWidget( this->title );
	mainLayout->addWidget( this->boolComboBox );
	connect( boolComboBox, &QComboBox::currentTextChanged, this, &BoolValueValidatorWidget::currentTextChanged_Slot );
	connect( boolComboBox, &QComboBox::currentIndexChanged, this, &BoolValueValidatorWidget::currentIndexChanged_Slot );
	boolComboBox->installEventFilter( this );

}
bool BoolValueValidatorWidget::setBoolValue( bool set_new_bool_var ) {
	if( set_new_bool_var )
		boolComboBox->setCurrentIndex( 1 );
	else
		boolComboBox->setCurrentIndex( 0 );
	return true;
}
bool BoolValueValidatorWidget::getBoolValue( bool &result_get_new_bool_var ) {
	if( boolComboBox->currentIndex( ) == 0 ) {
		result_get_new_bool_var = false;
		return true;
	}
	result_get_new_bool_var = true;
	return true;
}
bool BoolValueValidatorWidget::eventFilter( QObject *watched, QEvent *event ) {
	bool eventFilter = ValidatorWidget::eventFilter( watched, event );

	return eventFilter;
}
