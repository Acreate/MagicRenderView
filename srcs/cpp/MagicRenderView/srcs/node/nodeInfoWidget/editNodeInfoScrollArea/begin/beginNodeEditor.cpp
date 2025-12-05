#include "beginNodeEditor.h"
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

	return initNodeResult;
}
