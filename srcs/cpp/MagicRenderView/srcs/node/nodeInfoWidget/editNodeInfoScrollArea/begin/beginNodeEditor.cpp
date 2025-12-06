#include "beginNodeEditor.h"

#include "../../../node/node.h"

#include "../../../nodeInfo/nodeBuilderTools.h"
BeginNodeEditor::BeginNodeEditor( NodeInfoWidget *parent ) : EditorNodeInfoScrollArea( parent ) {
}

void * BeginNodeEditor::getVarPtr( ) const {
	return nullptr;
}
const std::type_info & BeginNodeEditor::getVarType( ) const {
	return typeid( void );
}
void BeginNodeEditor::clearVar( ) {
}
BeginNodeEditor::~BeginNodeEditor( ) {
}
bool BeginNodeEditor::initNode( Node *init_node ) {
	bool initNodeResult = EditorNodeInfoScrollArea::initNode( init_node );
	std::vector< NodeRefLinkInfo * > resultNodeRefLinkVector;
	NodeBuilderTools::analysisNodeRef( init_node->getNodeRefLinkInfoPtr( ), resultNodeRefLinkVector );
	return initNodeResult;
}
