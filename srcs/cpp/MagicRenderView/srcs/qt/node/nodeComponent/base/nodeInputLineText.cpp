#include "nodeInputLineText.h"

#include <QLabel>
#include <QLineEdit>
#include <qboxlayout.h>

#include "qt/type/baseType/stringTypeObject.h"
void NodeInputLineText::setTitle( const QString &new_title ) {
	titile->setText( new_title );
}

NodeInputLineText::NodeInputLineText( QWidget *parent, Qt::WindowFlags f ): INodeComponent( parent, f ) {
	var.reset( new StringTypeObject );
	mainLayout = new QHBoxLayout( this );
	titile = new QLabel( this );
	titile->setText( "输入" );

	mainLayout->addWidget( titile );
}
bool NodeInputLineText::resetOrg( ) {
	var.reset( new StringTypeObject );
	bool cond = var->isNullptr( ) != true;
	return cond;
}
bool NodeInputLineText::setText( const QString &text ) {
	if( var->isNullptr( ) )
		if( resetOrg( ) == false )
			return false;
	var->setString( text );
	bool cond = var->isNullptr( ) == false;
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
	return cond;
}
bool NodeInputLineText::setVar( const ITypeObject &new_var ) const {
	auto qobjectCast = qobject_cast< const StringTypeObject * >( &new_var );
	if( qobjectCast == nullptr )
		return false;
	*var = *qobjectCast;
	bool cond = var->isNullptr( ) == false;
	return cond;
}
void NodeInputLineText::permissionChannel( bool &input_type, bool &output_type, bool &all ) {
	output_type = input_type = true;
	all = false;
}
bool NodeInputLineText::setComponentChannel( const Channel_Type &channel_type ) {
	if( channelType == channel_type )
		return true;
	auto temp = channelType;
	channelType = channel_type;
	emit changeChannel( this, temp, channelType );
	return true;
}
void NodeInputLineText::paintEvent( QPaintEvent *event ) {
	//	INodeComponent::paintEvent( event );
}
