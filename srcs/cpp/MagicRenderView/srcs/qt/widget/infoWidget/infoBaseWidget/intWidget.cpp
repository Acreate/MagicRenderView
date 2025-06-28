#include "./intWidget.h"

#include <QLineEdit>
#include <QVBoxLayout>
#include <QIntValidator>
#include <QLabel>

#include <qt/stack/varStack/IVarStack.h>
#include <qt/stack/varStack/base/baseVarStackEx.h>
#include <qt/type/baseType/intTypeObject.h>

#include "../../../type/baseType/floatTypeObject.h"
#include "../../../type/baseType/stringTypeObject.h"

IntWidget::IntWidget( const std_function< std_shared_ptr< IInfoWidgetStack >( ) > &get_stack_function, QWidget *parent, const QString &title_msg ): IInfoWidget( get_stack_function, parent, title_msg ) {
	value = IVarStack::getInstance< BaseVarStackEx >( )->generateTVar< IntTypeObject >( );
	value->setUiTypeName( title_msg );
	lineEdit = new QLineEdit( this );
	lineEdit->setValidator( new QIntValidator( this ) );
	mainLayout->addWidget( lineEdit );
	lineEdit->setPlaceholderText( "请输入整数" );
	connect( lineEdit, &QLineEdit::editingFinished, [this]( ) {
		bool result = false;
		auto varValue = lineEdit->text( ).toLongLong( &result );
		if( result )
			value->setVal( varValue );

		synValue( );
		emit valueChanged( );
	} );
}
int64_t IntWidget::getInt( ) const {
	auto text = lineEdit->text( );
	return text.toLongLong( );
}
void IntWidget::setInt( const int64_t &new_value ) {
	lineEdit->setText( QString::number( new_value ) );
	value->setVal( new_value );
	synValue( );
	emit valueChanged( );
}

void IntWidget::setPlaceholderText( const QString &placeholder_text ) const {
	lineEdit->setPlaceholderText( placeholder_text );
}
QString IntWidget::getPlaceholderText( ) const {
	return lineEdit->placeholderText( );
}
std_shared_ptr< ITypeObject > IntWidget::getValue( ) const {
	return value;
}
bool IntWidget::setValue( const std_shared_ptr< ITypeObject > &value ) const {
	ITypeObject *element = value.get( );
	if( *element == nullptr )
		return false;
	auto intTypeObject = qobject_cast< IntTypeObject * >( element );
	if( intTypeObject ) {
		auto val = intTypeObject->getVal( );
		this->value->setVal( val );
		lineEdit->setText( QString::number( val ) );
		synValue( );
		emit valueChanged( );
		return true;
	}
	auto floatTypeObject = qobject_cast< FloatTypeObject * >( element );
	if( floatTypeObject ) {
		auto val = floatTypeObject->getVal( );
		this->value->setVal( val );
		lineEdit->setText( QString::number( val ) );

		synValue( );
		emit valueChanged( );
		return true;
	}
	auto stringTypeObject = qobject_cast< StringTypeObject * >( element );
	if( stringTypeObject ) {
		bool isOk = false;
		auto converValue = stringTypeObject->getString( ).toLongLong( &isOk );
		if( isOk ) {
			this->value->setVal( converValue );
			lineEdit->setText( QString::number( converValue ) );
			synValue( );
			emit valueChanged( );
			return true;
		}
		auto converDoubleValue = stringTypeObject->getString( ).toDouble( &isOk );
		if( isOk ) {
			this->value->setVal( converDoubleValue );
			lineEdit->setText( QString::number( converDoubleValue ) );
			synValue( );
			emit valueChanged( );
			return true;
		}
	}
	return false;
}
