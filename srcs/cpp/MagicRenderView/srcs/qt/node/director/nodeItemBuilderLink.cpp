#include "nodeItemBuilderLink.h"

#include "nodeItemInfo.h"
#include "nodePortLinkInfo.h"

#include "../../tools/tools.h"

#include "../item/nodeItem.h"

#include "../prot/inputProt/nodeInputPort.h"

NodeItemBuilderLink::NodeItemBuilderLink( NodeItemInfo *node_item_info ): nodeItemInfo( node_item_info ) { }
NodeItemBuilderLink::~NodeItemBuilderLink( ) {
	emit releaseThisSignal( this );
}

bool NodeItemBuilderLink::generateBuilderInfo( ) {

	return true;
}

bool NodeItemBuilderLink::next( ) {

	return true;
}
bool NodeItemBuilderLink::isRun( ) const {

	return true;
}
bool NodeItemBuilderLink::run( ) {

	return false;
}
bool NodeItemBuilderLink::getRunNodeItem( NodeItemInfo *&result_current_run_info ) {
	return false;
}