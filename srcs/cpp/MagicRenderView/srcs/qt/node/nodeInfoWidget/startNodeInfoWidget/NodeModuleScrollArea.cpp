#include "NodeModuleScrollArea.h"

#include "nodeModuleWidget.h"
NodeModuleScrollArea::NodeModuleScrollArea( const std_vector< std_vector< NodeItemInfo * > > *run_list, QWidget *parent ) : QScrollArea( parent ) {
	nodeModuleWidget = new NodeModuleWidget( this );
	setWidget( nodeModuleWidget );
	setWidgetResizable( true );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
}
const std_vector< std_vector< NodeItemInfo * > > * NodeModuleScrollArea::getRunList( ) const {
	return nodeModuleWidget->getRunList( );
}
void NodeModuleScrollArea::setRunList( const std_vector< std_vector< NodeItemInfo * > > *run_list ) {
	nodeModuleWidget->setRunList( run_list );
}
void NodeModuleScrollArea::clear( ) {
	nodeModuleWidget->clear( );
}
