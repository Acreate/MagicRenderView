#include "./nodePanel.h"

#include <qboxlayout.h>

#include "qt/tools/tools.h"
void NodePanel::updateSize( ) {
	size_t leftHeight = 0, rightHeight = 0;
	QWidget *widget;
	int count = leftVectorBoxLayout->count( );
	int index = 0;
	for( ; index < count; ++index ) {
		widget = leftVectorBoxLayout->itemAt( index )->widget( );
		if( widget ) {
			widget->show( );
			leftHeight += widget->height( );
		}
	}

	count = rightVectorBoxLayout->count( );
	for( index = 0; index < count; ++index ) {
		widget = rightVectorBoxLayout->itemAt( index )->widget( );
		if( widget ) {
			widget->show( );
			rightHeight += widget->height( );
		}
	}
	leftHeight = leftHeight > rightHeight ? leftHeight : rightHeight;
	setNewSize( QSize( this->width( ), leftHeight ) );
}
void NodePanel::childComponentChangeChannel( INodeComponent *component, Channel_Type old_channel_type, Channel_Type new_channel_type ) {
	int count;
	switch( old_channel_type ) {
		case Channel_Type::Normal_Default :
			tools::debug::printError( component->objectName( ) + " => 无法正确调整通道" );
			break;
		case Channel_Type::Input_Read : // 转到输出
			leftVectorBoxLayout->removeWidget( component );
			component->setParent( rightWidget );
			count = rightVectorBoxLayout->count( );
			rightVectorBoxLayout->insertWidget( count - 1, component, 0, Qt::AlignRight | Qt::AlignTop );
			repaint( );
			break;
		case Channel_Type::Output_Write : // 转到输入
			rightVectorBoxLayout->removeWidget( component );
			component->setParent( leftWidget );
			count = leftVectorBoxLayout->count( );
			leftVectorBoxLayout->insertWidget( count - 1, component, 0, Qt::AlignLeft | Qt::AlignTop );
			repaint( );
			break;
	}
}

bool NodePanel::appendInput( INodeComponent *input_component ) {
	int count = leftVectorBoxLayout->count( );
	input_component->setParent( leftWidget );
	leftVectorBoxLayout->insertWidget( count - 1, input_component, 0, Qt::AlignLeft | Qt::AlignTop );
	input_component->setComponentChannel( Channel_Type::Input_Read );
	connect( input_component, &INodeComponent::changeChannel, this, &NodePanel::childComponentChangeChannel );
	repaint( );
	return true;
}
bool NodePanel::removeInputItem( INodeComponent *output_component ) {
	int count = leftVectorBoxLayout->count( );
	for( int index = 0; index < count; ++index )
		if( leftVectorBoxLayout->itemAt( index )->widget( ) == output_component ) {
			leftVectorBoxLayout->removeWidget( output_component );
			output_component->setParent( nullptr );
			disconnect( output_component, &INodeComponent::changeChannel, this, &NodePanel::changeChannel );
			repaint( );
			return true;
		}
	return false;
}
QWidget * NodePanel::removeInputItem( size_t index ) {
	int count = leftVectorBoxLayout->count( );
	if( count > index ) {
		auto widget = leftVectorBoxLayout->itemAt( index )->widget( );
		leftVectorBoxLayout->removeWidget( widget );
		auto nodeComponent = qobject_cast< INodeComponent * >( widget );
		if( nodeComponent )
			disconnect( nodeComponent, &INodeComponent::changeChannel, this, &NodePanel::changeChannel );
		repaint( );
		widget->setParent( nullptr );
		return widget;
	}
	return nullptr;
}
QWidget * NodePanel::getInputItem( size_t index ) const {
	int count = leftVectorBoxLayout->count( );
	if( count > index ) {
		auto widget = leftVectorBoxLayout->itemAt( index )->widget( );
		return widget;
	}
	return nullptr;
}
bool NodePanel::appendOutput( INodeComponent *output_component ) {
	int count = rightVectorBoxLayout->count( );
	output_component->setParent( rightWidget );
	rightVectorBoxLayout->insertWidget( count - 1, output_component, 0, Qt::AlignRight | Qt::AlignTop );
	output_component->setComponentChannel( Channel_Type::Output_Write );
	connect( output_component, &INodeComponent::changeChannel, this, &NodePanel::childComponentChangeChannel );
	repaint( );
	return true;
}
bool NodePanel::removeOutputItem( INodeComponent *output_component ) {
	int count = rightVectorBoxLayout->count( );
	for( int index = 0; index < count; ++index )
		if( rightVectorBoxLayout->itemAt( index )->widget( ) == output_component ) {
			rightVectorBoxLayout->removeWidget( output_component );
			output_component->setParent( nullptr );
			disconnect( output_component, &INodeComponent::changeChannel, this, &NodePanel::changeChannel );
			repaint( );
			return true;
		}
	return false;
}
QWidget * NodePanel::removeOutputItem( size_t index ) {
	int count = rightVectorBoxLayout->count( );
	if( count > index ) {
		auto widget = rightVectorBoxLayout->itemAt( index )->widget( );
		auto nodeComponent = qobject_cast< INodeComponent * >( widget );
		if( nodeComponent )
			disconnect( nodeComponent, &INodeComponent::changeChannel, this, &NodePanel::changeChannel );
		repaint( );
		widget->setParent( nullptr );
		return widget;
	}
	return nullptr;
}
QWidget * NodePanel::getOutputItem( size_t index ) const {
	int count = rightVectorBoxLayout->count( );
	if( count > index ) {
		auto widget = rightVectorBoxLayout->itemAt( index )->widget( );
		return widget;
	}
	return nullptr;
}

NodePanel::NodePanel( const QString &node_component_name, QWidget *parent, Qt::WindowFlags f ): INodeComponent( node_component_name, parent, f ) {
	mainLayout = new QHBoxLayout( this );
	leftWidget = new QWidget( this );
	leftVectorBoxLayout = new QVBoxLayout( leftWidget );
	rightWidget = new QWidget( this );
	rightVectorBoxLayout = new QVBoxLayout( rightWidget );

	mainLayout->addWidget( leftWidget );
	mainLayout->addSpacerItem( new QSpacerItem( 100, 0, QSizePolicy::Expanding, QSizePolicy::Ignored ) );
	mainLayout->addWidget( rightWidget );

	mainLayout->setContentsMargins( 0, 0, 0, 0 );
	mainLayout->setSpacing( 0 );

	leftVectorBoxLayout->setContentsMargins( 0, 0, 0, 0 );
	leftVectorBoxLayout->setSpacing( 0 );
	leftVectorBoxLayout->addSpacerItem( new QSpacerItem( 0, 100, QSizePolicy::Ignored, QSizePolicy::Expanding ) );

	rightVectorBoxLayout->setContentsMargins( 0, 0, 0, 0 );
	rightVectorBoxLayout->setSpacing( 0 );
	rightVectorBoxLayout->addSpacerItem( new QSpacerItem( 0, 100, QSizePolicy::Ignored, QSizePolicy::Expanding ) );
}

INodeComponent * NodePanel::getPosNodeComponent( const QPoint &pos ) const {
	INodeComponent *nodeComponent;
	QRect geometry = leftWidget->geometry( );
	if( geometry.contains( pos ) ) {
		auto childrenList = leftWidget->children( );
		auto point = pos - leftWidget->pos( );
		for( auto child : childrenList ) {
			nodeComponent = qobject_cast< INodeComponent * >( child );
			if( nodeComponent == nullptr )
				continue;
			geometry = nodeComponent->geometry( );
			if( geometry.contains( point ) )
				return nodeComponent;
		}
	} else {
		auto childrenList = rightWidget->children( );
		auto point = pos - rightWidget->pos( );
		for( auto child : childrenList ) {
			nodeComponent = qobject_cast< INodeComponent * >( child );
			if( nodeComponent == nullptr )
				continue;
			geometry = nodeComponent->geometry( );
			if( geometry.contains( point ) )
				return nodeComponent;
		}
	}
	return INodeComponent::getPosNodeComponent( pos );;
}
bool NodePanel::getComponentLinkPos( const INodeComponent *component, QPoint &resulut_pos ) const {
	QObjectList childrenList = leftWidget->children( );
	for( auto child : childrenList )
		if( component == child && component->getComponentLinkPos( component, resulut_pos ) == true ) {
			resulut_pos = resulut_pos + leftWidget->pos( ) + pos( );
			return true;
		}
	childrenList = rightWidget->children( );
	for( auto child : childrenList )
		if( component == child && component->getComponentLinkPos( component, resulut_pos ) == true ) {
			resulut_pos = resulut_pos + rightWidget->pos( ) + pos( );
			return true;
		}
	return false;
}

void NodePanel::showEvent( QShowEvent *event ) {
	//INodeComponent::showEvent( event );
	QWidget::showEvent( event );
	updateSize( );
}
