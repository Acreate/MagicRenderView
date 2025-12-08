#include "generateNodeEditor.h"
GenerateNodeEditor::GenerateNodeEditor( NodeInfoWidget *parent ) : EditorNodeInfoScrollArea( parent ) { }
void * GenerateNodeEditor::getVarPtr( ) const {
	return nullptr;
}
const std::type_info & GenerateNodeEditor::getVarType( ) const {
	return typeid( nullptr );
}
void GenerateNodeEditor::clearVar( ) {
}
