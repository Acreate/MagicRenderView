#include "nodeModuleWidget.h"
NodeModuleWidget::NodeModuleWidget( QWidget *parent ) : QWidget( parent ), runList( nullptr ), currentIndex( 0 ) { }
const std_vector< std_vector< NodeItemInfo * > > * NodeModuleWidget::getRunList( ) const { return runList; }
void NodeModuleWidget::setRunList( const std_vector< std_vector< NodeItemInfo * > > *run_list ) {
	runList = run_list;
	currentIndex = 0;
}
size_t NodeModuleWidget::getCurrentRunNodeItemInfoVector( std_vector< NodeItemInfo * > &result_list ) const {
	size_t runListCount = runList->size( );
	if( runListCount == 0 || runListCount == currentIndex )
		return 0;
	result_list = runList->data( )[ currentIndex ];
	return result_list.size( );
}
