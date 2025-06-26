#include "nodeInfo.h"

#include <QVBoxLayout>

#include <alias/type_alias.h>

#include <qt/node/nodeComponent/INodeComponent.h>
#include <qt/node/nodeWidget/INodeWidget.h>

#include <qt/stack/infoWidgetStack/IInfoWidgetStack.h>
#include <qt/stack/infoWidgetStack/base/baseInfoWidgetStack.h>

#include "infoWidget/IInfoWidget.h"

NodeInfo::NodeInfo( QWidget *parent, Qt::WindowFlags f ): QWidget( parent, f ) {
	mainLayout = new QVBoxLayout( this );
	mainLayout->setContentsMargins( 0, 0, 0, 0 );
	mainLayout->setSpacing( 0 );
	currentNodeWidget = nullptr;
}
void NodeInfo::setNodeWidget( INodeWidget *node_widget ) {
	if( currentNodeWidget == node_widget )
		return;
	clearInfoPanel( );
	currentNodeWidget = node_widget;
	if( node_widget == nullptr )
		return;

	auto nodeComponents = currentNodeWidget->getNodeComponents( );
	size_t count = nodeComponents.size( );
	if( count == 0 )
		return;

	auto infoWidgetGen = IInfoWidgetStack::getInstance< BaseInfoWidgetStack >( );
	auto data = nodeComponents.data( );
	for( size_t index = 0; index < count; ++index ) {
		auto nodeComponent = data[ index ];
		if( nodeComponent->getComponentChannel( ) != INodeComponent::Channel_Type::Input_Read )
			continue;
		auto typeObject = nodeComponent->getVarObject( );
		auto generateInfoWidget = infoWidgetGen->generateInfoWidget( typeObject );
		if( generateInfoWidget == nullptr ) {
			generateInfoWidget = infoWidgetGen->generateInfoWidget( "null" );
			generateInfoWidget->setTitle( "错误节点" );
			generateInfoWidget->setToolTip( "无法找到匹配的信息显示节点，请检查异常 : " + nodeComponent->getNodeComponentName( ) );
		} else {
			generateInfoWidget->setValue( typeObject );
			generateInfoWidget->setTitle( nodeComponent->getNodeComponentName( ) );
		}
		mainLayout->addWidget( generateInfoWidget );
	}
	mainLayout->addSpacerItem( new QSpacerItem( 0, 100, QSizePolicy::Ignored, QSizePolicy::Expanding ) );
}
void NodeInfo::clearInfoPanel( ) {
	int count = mainLayout->count( );
	int index = 0;
	std_vector< QWidget * > removeWidget;
	for( ; index < count; ++index ) {
		auto layoutItem = mainLayout->itemAt( index );
		if( layoutItem->isEmpty( ) )
			continue;
		auto widget = layoutItem->widget( );
		if( widget )
			removeWidget.emplace_back( widget );
	}
	for( auto item : removeWidget ) {
		mainLayout->removeWidget( item );
		delete item;
	}
}
