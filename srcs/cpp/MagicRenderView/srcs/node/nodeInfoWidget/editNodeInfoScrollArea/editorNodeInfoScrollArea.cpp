#include "editorNodeInfoScrollArea.h"

#include "../mainInfoWidget/nodeInfoWidget.h"

EditorNodeInfoScrollArea::EditorNodeInfoScrollArea( NodeInfoWidget *parent ) : QScrollArea( parent ), parent( parent ) {
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setWidgetResizable( true );
}
bool EditorNodeInfoScrollArea::initNode( Node *init_node ) {
	currentNode = init_node;
	return currentNode != nullptr;
}
