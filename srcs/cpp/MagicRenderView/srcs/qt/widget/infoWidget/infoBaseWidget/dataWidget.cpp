#include "./dataWidget.h"

#include <QTextEdit>
#include <QVBoxLayout>

#include <qt/stack/varStack/IVarStack.h>
#include <qt/stack/varStack/base/baseVarStackEx.h>
#include <qt/type/baseType/dataTypeObject.h>

#include <qt/type/baseType/floatTypeObject.h>
#include <qt/type/baseType/intTypeObject.h>
#include <qt/type/baseType/stringTypeObject.h>

#include "subWidget/hexEditor.h"
DataWidget::DataWidget( const std_function< std_shared_ptr< IInfoWidgetStack >( ) > &get_stack_function, QWidget *parent, const QString &title_msg ): IInfoWidget( get_stack_function, parent, title_msg ) {
	dataTypeObject = IVarStack::getInstance< BaseVarStackEx >( )->generateTVar< DataTypeObject >( );

	edit = new HexEditor( this );
	mainLayout->addWidget( edit );
}
QString DataWidget::getText( ) const {
	return edit->toPlainText( );
}
bool DataWidget::setText( const QString &new_text ) const {
	return edit->setString( new_text );
}

void DataWidget::setPlaceholderText( const QString &placeholder_text ) const {
	edit->setPlaceholderText( placeholder_text );
}
QString DataWidget::getPlaceholderText( ) const {
	return edit->placeholderText( );
}
std_shared_ptr< ITypeObject > DataWidget::getValue( ) const {
	return dataTypeObject;
}
bool DataWidget::setValue( const std_shared_ptr< ITypeObject > &value ) const {
	ITypeObject *element = value.get( );
	if( *element == nullptr )
		return false;
	auto stringTypeObject = qobject_cast< StringTypeObject * >( element );
	if( stringTypeObject )
		return edit->setHex( element->toString( ).toUtf8( ).toHex( ) );
	auto intTypeObject = qobject_cast< IntTypeObject * >( element );
	if( intTypeObject )
		return edit->setHex( intTypeObject->getVal( ) );
	auto floatTypeObject = qobject_cast< FloatTypeObject * >( element );
	if( floatTypeObject )
		return edit->setHex( floatTypeObject->getVal( ) );
	auto dataTypeObject = qobject_cast< DataTypeObject * >( element );
	if( dataTypeObject )
		return edit->setHex( dataTypeObject->getCharArray( ) );
	return false;
}
