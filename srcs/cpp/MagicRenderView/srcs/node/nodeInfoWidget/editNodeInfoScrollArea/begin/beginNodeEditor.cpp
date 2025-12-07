#include "beginNodeEditor.h"

#include "../../../node/node.h"

#include "../../../nodeInfo/nodeBuilderTools.h"
#include "../../../nodeInfo/nodeRefLinkInfo.h"
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
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;

	beginNodeRefLinkInfo = init_node->getNodeRefLinkInfoPtr( );
	if( init_node->getNodeType( ) == NodeEnum::NodeType::End )
		if( NodeBuilderTools::findRefBeginNode( beginNodeRefLinkInfo, beginNodeRefLinkInfo ) == false )
			return false;
	std::vector< NodeRefLinkInfo * > resultNodeRefLinkVector;
	if( NodeBuilderTools::analysisNodeRef( beginNodeRefLinkInfo, resultNodeRefLinkVector ) == false )
		return false;
	size_t count = resultNodeRefLinkVector.size( );
	auto nodeRefLinkInfoArrayPtr = resultNodeRefLinkVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		switch( nodeRefLinkInfoArrayPtr[ index ]->getCurrentNode( )->getNodeType( ) ) {
			case NodeEnum::NodeType::Begin :
				beginNodeRefLinkVector.emplace_back( nodeRefLinkInfoArrayPtr[ index ] );
				break;
			case NodeEnum::NodeType::End :
				endNodeRefLinkVector.emplace_back( nodeRefLinkInfoArrayPtr[ index ] );
				break;
			default :
				processNodeRefLinkVector.emplace_back( nodeRefLinkInfoArrayPtr[ index ] );
				break;
		}
	if( NodeBuilderTools::sortProcessNodeRefArray( processNodeRefLinkVector.data( ), processNodeRefLinkVector.size( ) ) == false )
		return false; // 缺少依赖
	
	return true;
}
