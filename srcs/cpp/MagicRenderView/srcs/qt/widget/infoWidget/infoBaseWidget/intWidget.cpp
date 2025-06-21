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
	lineEdit = new QLineEdit( this );
	lineEdit->setValidator( new QIntValidator( this ) );
	mainLayout->addWidget( lineEdit );
	lineEdit->setPlaceholderText( "请输入整数" );
	connect( lineEdit, &QLineEdit::editingFinished, [this]( ) {
		bool result = false;
		auto varValue = lineEdit->text( ).toLongLong( &result );
		if( result )
			value->setVal( varValue );
		emit valueChanged( );
	} );
}
QString IntWidget::getText( ) const {
	return lineEdit->text( );
}
void IntWidget::setText( const QString &new_text ) const {
	bool result = false;
	auto varValue = new_text.toLongLong( &result );
	if( result != false ) {
		value->setVal( varValue );
		lineEdit->setText( QString::number( varValue ) );
	}
	auto varValueDouble = new_text.toDouble( &result );
	if( result != false ) {
		value->setVal( varValueDouble );
		lineEdit->setText( QString::number( varValueDouble ) );
	}
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
void IntWidget::setValue( const std_shared_ptr< ITypeObject > &value ) const {
	ITypeObject *element = value.get( );
	if( *element == nullptr )
		return;
	auto intTypeObject = qobject_cast< IntTypeObject * >( element );
	if( intTypeObject ) {
		auto val = intTypeObject->getVal( );
		this->value->setVal( val );
		lineEdit->setText( QString::number( val ) );
		return;
	}
	auto floatTypeObject = qobject_cast< FloatTypeObject * >( element );
	if( floatTypeObject ) {
		auto val = floatTypeObject->getVal( );
		this->value->setVal( val );
		lineEdit->setText( QString::number( val ) );
		return;
	}
	auto stringTypeObject = qobject_cast< StringTypeObject * >( element );
	if( stringTypeObject ) {
		bool isOk = false;
		auto converValue = stringTypeObject->getString( ).toLongLong( &isOk );
		if( isOk ) {
			this->value->setVal( converValue );
			lineEdit->setText( QString::number( converValue ) );
			return;
		}
		auto converDoubleValue = stringTypeObject->getString( ).toDouble( &isOk );
		if( isOk ) {
			this->value->setVal( converDoubleValue );
			lineEdit->setText( QString::number( converDoubleValue ) );
			return;
		}
	}
}
