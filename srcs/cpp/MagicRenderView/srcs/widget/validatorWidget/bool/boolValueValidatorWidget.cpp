#include "boolValueValidatorWidget.h"

#include <QHBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>

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
bool BoolValueValidatorWidget::setValidatorWidgetText( QString &result_text ) {
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
