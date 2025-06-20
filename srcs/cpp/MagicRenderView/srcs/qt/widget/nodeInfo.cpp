#include "nodeInfo.h"

#include <QVBoxLayout>

#include <alias/type_alias.h>
NodeInfo::NodeInfo( QWidget *parent, Qt::WindowFlags f ): QWidget( parent, f ) {
	mainLayout = new QVBoxLayout( this );
	currentNodeWidget = nullptr;
}
void NodeInfo::setNodeWidget( INodeWidget *node_widget ) {
	if( currentNodeWidget == node_widget )
		return;
	clearInfoPanel( );
	currentNodeWidget = node_widget;
	if( node_widget == nullptr ) 
		return;
	
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
