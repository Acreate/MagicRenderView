#include "beginNodeEditor.h"
BeginNodeEditor::BeginNodeEditor( NodeInfoWidget *parent ) : EditorNodeInfoScrollArea( parent ) {
}
void BeginNodeEditor::setBeginNodeVector( const std::vector<Node *> &begin_vector_node ) {
	beginVectorNode = begin_vector_node;
}
void BeginNodeEditor::setEndNodeVector( const std::vector<Node *> &end_vector_node ) {
	endVectorNode = end_vector_node;
}
void BeginNodeEditor::setProcessNodeVector( const std::vector<Node *> &process_vector_node ) {
	processVectorNode = process_vector_node;
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

	return initNodeResult;
}
