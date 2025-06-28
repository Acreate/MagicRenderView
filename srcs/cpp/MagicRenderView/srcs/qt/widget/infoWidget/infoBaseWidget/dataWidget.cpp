#include "./dataWidget.h"

#include <QLabel>
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
	dataTypeObject->setUiTypeName( title_msg );
	edit = new HexEditor( this );
	mainLayout->addWidget( edit );
}
QString DataWidget::getText( ) const {
	return edit->toPlainText( );
}

void DataWidget::setPlaceholderText( const QString &placeholder_text ) const {
	edit->setPlaceholderText( placeholder_text );
}
QString DataWidget::getPlaceholderText( ) const {
	return edit->placeholderText( );
}
std_shared_ptr< ITypeObject > DataWidget::getValue( ) const {
	dataTypeObject->setValue( edit->toUcharVector( false ) );
	return dataTypeObject;
}
std_shared_ptr< DataTypeObject > DataWidget::getValue( bool mod_is_suffix_data_var ) const {
	dataTypeObject->setValue( edit->toUcharVector( mod_is_suffix_data_var ) );
	return dataTypeObject;
}
bool DataWidget::setValue( const std_shared_ptr< ITypeObject > &value ) const {
	ITypeObject *element = value.get( );
	if( *element == nullptr )
		return false;
	auto stringTypeObject = qobject_cast< StringTypeObject * >( element );
	if( stringTypeObject ) {
		bool hex = edit->setHex( element->toString( ).toUtf8( ).toHex( ) );
		if( hex ) {
			synValue( );
			emit valueChanged( );
		}
		return hex;
	}
	auto intTypeObject = qobject_cast< IntTypeObject * >( element );
	if( intTypeObject ) {
		bool hex = edit->setHex( intTypeObject->getVal( ) );
		if( hex ) {
			synValue( );
			emit valueChanged( );
		}
		return hex;
	}
	auto floatTypeObject = qobject_cast< FloatTypeObject * >( element );
	if( floatTypeObject ) {
		bool hex = edit->setHex( floatTypeObject->getVal( ) );
		if( hex ) {
			synValue( );
			emit valueChanged( );
		}
		return hex;
	}
	auto dataTypeObject = qobject_cast< DataTypeObject * >( element );
	if( dataTypeObject ) {
		bool hex = edit->setHex( dataTypeObject->getCharArray( ) );
		if( hex ) {
			synValue( );
			emit valueChanged( );
		}
		return hex;
	}
	return false;
}
bool DataWidget::setString( const QString &hex_text ) {
	bool string = edit->setString( hex_text );
	if( string ) {
		synValue( );
		emit valueChanged( );
	}
	return string;
}
bool DataWidget::setHex( const QByteArray &hex_text ) {
	bool hex = edit->setHex( hex_text );
	if( hex ) {
		synValue( );
		emit valueChanged( );
	}
	return hex;
}
bool DataWidget::setHex( const std_vector< uchar > &data_vector ) {
	bool hex = edit->setHex( data_vector );
	if( hex ) {
		synValue( );
		emit valueChanged( );
	}
	return hex;
}
bool DataWidget::setHex( const std_vector< char > &data_vector ) {
	bool hex = edit->setHex( data_vector );
	if( hex ) {
		synValue( );
		emit valueChanged( );
	}
	return hex;
}
bool DataWidget::setHex( const int64_t &number_value ) {
	bool hex = edit->setHex( number_value );
	if( hex ) {
		synValue( );
		emit valueChanged( );
	}
	return hex;
}
bool DataWidget::setHex( const double &number_value ) {
	bool hex = edit->setHex( number_value );
	if( hex ) {
		synValue( );
		emit valueChanged( );
	}
	return hex;
}
