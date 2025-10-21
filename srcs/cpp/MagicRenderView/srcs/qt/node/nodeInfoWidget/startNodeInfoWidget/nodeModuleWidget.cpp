#include "nodeModuleWidget.h"

#include "../../director/nodeItemInfo.h"
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
bool NodeModuleWidget::findNodeItemInfoAtIndex( const NodeItemInfo *node_item_info, size_t &result_index ) const {
	return findNodeItemInfoAtIndex( node_item_info->getNodeItem( ), result_index );
}
bool NodeModuleWidget::findNodeItemInfoAtIndex( const NodeItem *node_item, size_t &result_index ) const {
	if( runList == nullptr )
		return false;
	size_t count = runList->size( );
	if( count == 0 )
		return false;
	auto runListArrayPtr = runList->data( );
	result_index = 0;
	size_t subVectorCount;
	NodeItemInfo *const*subVectorPtr;
	size_t subVectorIndex;
	for( ; result_index < count; ++result_index ) {
		subVectorCount = runListArrayPtr[ result_index ].size( );
		if( subVectorCount == 0 )
			continue;
		subVectorPtr = runListArrayPtr[ result_index ].data( );
		subVectorIndex = 0;
		for( ; subVectorIndex < subVectorCount; ++subVectorIndex )
			if( subVectorPtr[ subVectorIndex ]->getNodeItem( ) == node_item )
				return true;
	}
	return false;
}
