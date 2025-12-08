#include "jumpNodeEditor.h"

#include "../../../node/node.h"
#include "../../../nodeInfo/nodeBuilderTools.h"
JumpNodeEditor::JumpNodeEditor( NodeInfoWidget *parent ) : EditorNodeInfoScrollArea( parent ) { }
bool JumpNodeEditor::initNode( Node *init_node ) {
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;
	std::vector< std::vector< NodeRefLinkInfo * > > nodeRefLinkVector;
	auto resultBool = NodeBuilderTools::JumpNodeBuilderTools::analysisJumpNodeRef( init_node->getNodeRefLinkInfoPtr( ), nodeRefLinkVector );
	return true;
}
