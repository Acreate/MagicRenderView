#include "nodeInputLineText.h"

#include <QLabel>
#include <QLineEdit>
#include <qboxlayout.h>

#include "qt/stack/varStack/IVarStack.h"
#include "qt/stack/varStack/base/baseVarStackEx.h"
#include "qt/stack/varStack/base/baseVarStack.h"
#include "qt/type/baseType/stringTypeObject.h"

NodeInputLineText::NodeInputLineText( const QString &node_component_name, QWidget *parent, Qt::WindowFlags f ): INodeComponent( node_component_name, parent, f ) {
	var = IVarStack::getInstance< BaseVarStack >( )->generateTVar< StringTypeObject >( );
	mainLayout = new QHBoxLayout( this );
	titile = new QLabel( this );
	titile->setText( node_component_name );
	setObjectName( node_component_name );
	mainLayout->addWidget( titile );
}
bool NodeInputLineText::resetOrg( ) {
	var = IVarStack::getInstance< BaseVarStack >( )->generateTVar< StringTypeObject >( );
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
void NodeInputLineText::setNodeComponentName( const QString &node_component_name ) {
	INodeComponent::setNodeComponentName( node_component_name );
	titile->setText( node_component_name );
	setObjectName( node_component_name );
}
INodeComponent * NodeInputLineText::getPosNodeComponent( const QPoint &pos ) const {
	return nullptr;
}
bool NodeInputLineText::tryLetChangeVar( const ITypeObject *object_ptr ) const {
	if( qobject_cast< const StringTypeObject * >( object_ptr ) )
		return true;
	return false;
}
bool NodeInputLineText::tryLetChangeVar( const INodeComponent *component_object_ptr ) const {
	Channel_Type componentChannel = component_object_ptr->getComponentChannel( );
	if( componentChannel == Channel_Type::Normal_Default || componentChannel == channelType )
		return false;
	return tryLetChangeVar( component_object_ptr->getVarObjectPtr( ) );
}

void NodeInputLineText::paintEvent( QPaintEvent *event ) {
	//	INodeComponent::paintEvent( event );
}
