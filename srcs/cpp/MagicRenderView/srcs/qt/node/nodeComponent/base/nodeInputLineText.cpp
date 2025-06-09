#include "nodeInputLineText.h"

#include <QLabel>
#include <QLineEdit>
#include <qboxlayout.h>

#include "qt/type/baseType/stringTypeObject.h"
void NodeInputLineText::setTitle( const QString &new_title ) {
	titile->setText( new_title );
}
void NodeInputLineText::setPlaceholderText( const QString &new_title ) {
	inputLine->setPlaceholderText( new_title );
}

NodeInputLineText::NodeInputLineText( QWidget *parent, Qt::WindowFlags f ): INodeComponent( parent, f ) {
	var.reset( new StringTypeObject );
	mainLayout = new QHBoxLayout( this );
	titile = new QLabel( this );
	titile->setText( "输入" );
	inputLine = new QLineEdit( this );
	inputLine->setPlaceholderText( "输入有效字符串" );

	mainLayout->addWidget( titile );
	mainLayout->addWidget( inputLine );

	connect( inputLine, &QLineEdit::editingFinished, [this]( ) {
		var->setString( inputLine->text( ) );
	} );
}
bool NodeInputLineText::resetOrg( ) {
	var.reset( new StringTypeObject );
	bool cond = var->isNullptr( ) != true;
	if( cond )
		inputLine->clear( );
	return cond;
}
bool NodeInputLineText::setText( const QString &text ) {
	if( var->isNullptr( ) )
		if( resetOrg( ) == false )
			return false;
	var->setString( text );
	bool cond = var->isNullptr( ) == false;
	if( cond )
		inputLine->setText( text );
	return cond;
}
QString NodeInputLineText::getText( ) const {
	return var->toString( );
}
const std_shared_ptr< ITypeObject > NodeInputLineText::getVarObject( ) const {
	return var;
}
const ITypeObject * NodeInputLineText::getVarObjectPtr( ) const {
	return var.get( );
}
bool NodeInputLineText::setVar( const std_shared_ptr< ITypeObject > &new_var ) const {
	auto qobjectCast = qobject_cast< const StringTypeObject * >( new_var.get( ) );
	if( qobjectCast == nullptr )
		return false;
	*var = *qobjectCast;
	bool cond = var->isNullptr( ) == false;
	if( cond )
		inputLine->setText( var->toString( ) );
	return cond;
}
bool NodeInputLineText::setVar( const ITypeObject &new_var ) const {
	auto qobjectCast = qobject_cast< const StringTypeObject * >( &new_var );
	if( qobjectCast == nullptr )
		return false;
	*var = *qobjectCast;
	bool cond = var->isNullptr( ) == false;
	if( cond )
		inputLine->setText( var->toString( ) );
	return cond;
}
