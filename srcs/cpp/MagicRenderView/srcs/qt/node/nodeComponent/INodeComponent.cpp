﻿#include "INodeComponent.h"

#include <QPainter>

#include "../nodeWidget/INodeWidget.h"
size_t INodeComponent::getNodeWidgetAtNodeCompoentID( ) const {
	if( parentNodeWidget )
		return parentNodeWidget->getChildNodeCompoentID( this );
	return 0;
}
void INodeComponent::setNewSize( const QSize &new_size ) {
	setFixedSize( new_size );
	emit changeSize( new_size );
}
INodeComponent * INodeComponent::getPosNodeComponent( const QPoint &pos ) const {
	auto childrenList = children( );
	INodeComponent *nodeComponent;
	QRect geometry;
	for( auto child : childrenList ) {
		nodeComponent = qobject_cast< INodeComponent * >( child );
		if( nodeComponent == nullptr )
			continue;
		geometry = nodeComponent->geometry( );
		if( geometry.contains( pos ) )
			return nodeComponent;
	}
	return nullptr;
}
bool INodeComponent::getComponentLinkPos( const INodeComponent *component, QPoint &resulut_pos ) const {
	if( component != this )
		return false;
	QRect thisRect = rect( );
	QPoint point = pos( );
	switch( channelType ) {
		case Channel_Type::Normal_Default :
			resulut_pos = thisRect.center( ) + point;
			break;
		case Channel_Type::Input_Read :
			resulut_pos.setX( thisRect.left( ) + point.x( ) );
			resulut_pos.setY( thisRect.center( ).y( ) + point.y( ) );
			break;
		case Channel_Type::Output_Write :
			resulut_pos.setX( thisRect.right( ) + point.x( ) );
			resulut_pos.setY( thisRect.center( ).y( ) + point.y( ) );
			break;
	}
	return true;
}
INodeComponent::~INodeComponent( ) {
	emit thisDelete( this );
}

void INodeComponent::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	/*QPainter painter( this );
	QPen pen;
	QBrush brush;
	pen.setWidth( 5 );
	pen.setColor( Qt::red );
	painter.setPen( pen );
	auto geometry = size( );
	painter.drawRect( QRect( 0, 0, geometry.width( ) - 1, geometry.height( ) - 1 ) );*/
}
