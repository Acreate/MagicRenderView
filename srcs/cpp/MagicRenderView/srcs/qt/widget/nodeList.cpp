#include "nodeList.h"

#include <QVBoxLayout>
NodeList::NodeList( QWidget *parent, Qt::WindowFlags f ): QWidget( parent, f ) {
	mainLayout = new QVBoxLayout( this );
}
void NodeList::clearInfoPanel( ) {
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
void NodeList::setCurrentNodeWidgets( const std_vector< INodeWidget * > &current_node_widgets ) { currentNodeWidgets = current_node_widgets; }
