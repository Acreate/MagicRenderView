#include "editorNodeInfoScrollArea.h"

#include "../mainInfoWidget/nodeInfoWidget.h"

EditorNodeInfoScrollArea::EditorNodeInfoScrollArea( NodeInfoWidget *parent ) : QScrollArea( parent ), parent( parent ) { }
bool EditorNodeInfoScrollArea::initNode( Node *init_node ) {
	currentNode = init_node;
	return currentNode != nullptr;
}
