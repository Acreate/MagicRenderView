#include "./floatWidget.h"

#include <QLineEdit>
#include <QDoubleValidator>
#include <QLabel>
#include <QVBoxLayout>

#include "../../../stack/varStack/IVarStack.h"
#include "../../../stack/varStack/base/baseVarStackEx.h"
#include <qt/type/baseType/floatTypeObject.h>

#include "../../../type/baseType/intTypeObject.h"
#include "../../../type/baseType/stringTypeObject.h"
FloatWidget::FloatWidget( const std_function< std_shared_ptr< IInfoWidgetStack >( ) > &get_stack_function, QWidget *parent, const QString &title_msg ): IInfoWidget( get_stack_function, parent, title_msg ) {
	value = IVarStack::getInstance< BaseVarStackEx >( )->generateTVar< FloatTypeObject >( );
	value->setUiTypeName( title_msg );
	lineEdit = new QLineEdit( this );
	lineEdit->setValidator( new QDoubleValidator( this ) );
	mainLayout->addWidget( lineEdit );
	lineEdit->setPlaceholderText( "请输入浮点数" );
	connect( lineEdit, &QLineEdit::editingFinished, [this]( ) {
		bool result = false;
		auto varValue = lineEdit->text( ).toLongLong( &result );
		if( result )
			value->setVal( varValue );
		emit valueChanged( );
	} );
}
double FloatWidget::getFloat( ) const {
	return lineEdit->text( ).toDouble(  );
}
void FloatWidget::setFloat( const double &new_value ) {
	value->setVal( new_value );
	lineEdit->setText( QString::number( new_value ) );
}

void FloatWidget::setPlaceholderText( const QString &placeholder_text ) const {
	lineEdit->setPlaceholderText( placeholder_text );
}
QString FloatWidget::getPlaceholderText( ) const {
	return lineEdit->placeholderText( );
}
std_shared_ptr< ITypeObject > FloatWidget::getValue( ) const {
	return value;
}
bool FloatWidget::setValue( const std_shared_ptr< ITypeObject > &value ) const {
	ITypeObject *element = value.get( );

	if( *element == nullptr )
		return false;
	auto intTypeObject = qobject_cast< IntTypeObject * >( element );
	if( intTypeObject ) {
		auto val = intTypeObject->getVal( );
		this->value->setVal( intTypeObject->getVal( ) );
		lineEdit->setText( QString::number( val ) );
		return true;
	}
	auto floatTypeObject = qobject_cast< FloatTypeObject * >( element );
	if( floatTypeObject ) {
		auto val = floatTypeObject->getVal( );
		this->value->setVal( val );
		lineEdit->setText( QString::number( val ) );
		return true;
	}
	auto stringTypeObject = qobject_cast< StringTypeObject * >( element );
	if( stringTypeObject ) {
		bool isOk = false;
		double converValue = stringTypeObject->getString( ).toDouble( &isOk );
		if( isOk ) {
			this->value->setVal( converValue );
			lineEdit->setText( QString::number( converValue ) );
		}
		return true;
	}
	return false;
}
